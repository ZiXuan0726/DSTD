#pragma once
#include <string>
#include <iostream>
#include <limits>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "G13_TP068591_TP072176_TP067443_TP066377_TP070012_questions.hpp"
using namespace std;


struct StudentNode
{

};

class Student {
public:

    Student* prev = nullptr;
    Student* next = nullptr;
    int studentID;
    string name;
    string q1Question;
    int q1Score;
    string q2Question;
    int q2Score;
    string q3Question;
    int q3Score;
    int totalScore = 0;


    Student(string name, int studentId) {
        this->name = name;
        this->studentID = studentId;
    }
    Student(int studentId, string name) {
        this->name = name;
        this->studentID = studentId;
        this->totalScore = 0;
    }
    Student(int studentId, string name, int totalScore) {
        this->name = name;
        this->studentID = studentId;
        this->totalScore = totalScore;
    }
    Student(int studentId, string name, string q1, int s1, string q2, int s2, string q3, int s3, int totalScore) {
        this->name = name;
        this->studentID = studentId;
        this->q1Question = q1;
        this->q1Score = s1;
        this->q2Question = q2;
        this->q2Score = s2;
        this->q3Question = q3;
        this->q3Score = s3;
        this->totalScore = totalScore;
    }
    void recordQs(int i, string questionID, int score) {

        if (i == 1) {
            this->q1Question = questionID;
            this->q1Score = score;
        }
        if (i == 2) {
            this->q2Question = questionID;
            this->q2Score = score;
        }
        if (i == 3) {
            this->q3Question = questionID;
            this->q3Score = score;
        }
    }

    void drawCard(int i, QuestionList* ql, QuestionList* discardDeck) {
        int choice = 0;
        int score = 0;
        string question;
        QuestionNode* drewQuestion = ql->tail;
        do {
            cout << endl << "Question: (marks: " << drewQuestion->data->score << ")" << endl;
            ql->printFormatedQuestion(drewQuestion->data->question);
            question = drewQuestion->data->questionID;
            cout << endl << "Do you wish to answer the question (1) or discard it (2)? (1/2): ";
            cin >> choice;

            //discard
            if (choice == 2) {
                score = 0;
                ql->discard(drewQuestion, discardDeck);
                cout << "Question discarded" << endl;
                recordQs(i, "N/A", 0);
            }
            //answer
            else if (choice == 1) {
                string ans;
                cout << "Please enter your answer: ";
                cin >> ans;
                //answer correct, add score, delete question from question deck
                if (ans == drewQuestion->data->answer) {
                    score = drewQuestion->data->score;
                    totalScore = totalScore + score;
                    cout << endl << "Correct answer! You earned: " << score << "points" << endl;
                    ql->deleteQuestionNode(drewQuestion);
                }
                //answer wrong, move question to answered question
                else {
                    score = 0;
                    cout << endl << "Incorrect answer! You earned 0 points." << endl;
                    ql->deleteQuestionNode(drewQuestion);
                }
                recordQs(i, question, score);
            }
            //input validation
            else {
                cout << endl << "Invalid option, please try again!" << endl << endl;
                cin.clear(); // Clear the error flag set by invalid input
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while ((choice != 1 && choice != 2) || cin.fail());
    }

    void selectDiscardedQuestion(int i, QuestionList* discardDeck, int choice) {
        int score = 0;
        string question;
        QuestionNode* selDiscardQuestion = discardDeck->getDiscardedQs(choice);
        question = selDiscardQuestion->data->questionID;
        string ans;
        cout << endl << "Question: (marks: " << selDiscardQuestion->data->score << ")" << endl;
        discardDeck->printFormatedQuestion(selDiscardQuestion->data->question);
        cout << "Please enter your answer: ";
        cin >> ans;

        //answer correct, add score, delete question from discarded deck
        if (ans == selDiscardQuestion->data->answer) {
            cout << endl << "Correct answer! You earned: " << selDiscardQuestion->data->score << "points" << endl;
            score = selDiscardQuestion->data->score;
            totalScore = totalScore + selDiscardQuestion->data->score;
            discardDeck->deleteQuestionNode(selDiscardQuestion);
        }
        //answer wrong, question moved to answered deck
        else {
            cout << endl << "Incorrect answer! You earn 0 points." << endl;
            score = 0;
            discardDeck->deleteQuestionNode(selDiscardQuestion);
        }
        recordQs(i, question, score);
    }

};

class StudentList {
public:
    int size = 0;
    Student* head;
    Student* tail;
    int id;
    string name;

    Student* createNewNode(string name) {
        Student* node = new Student(name, size + 1);

        return node;
    }

    StudentList()
    {
    }
    StudentList(int id, string name)
    {
        this->id = id;
        this->name = name;
    }

    void insertBack(Student* nextStu) {
        if (tail == nullptr) {
            head = nextStu;
            tail = nextStu;
        }
        else {
            nextStu->prev = tail;
            tail->next = nextStu;
            tail = nextStu;
        }
        size++;
    }

    void displayLeaderboard() {
        bool setw;
        int rank = 1;
        Student* current = head;
        while (current != nullptr) {
            cout << std::setw(11) << rank << "\t";
            cout << std::setw(11) << current->name << "\t";
            cout << std::setw(11) << current->q1Question << "(" << current->q1Score << ")\t";
            cout << std::setw(11) << current->q2Question << "(" << current->q2Score << ")\t";
            cout << std::setw(11) << current->q3Question << "(" << current->q3Score << ")\t";
            cout << std::setw(11) << current->totalScore << "\t";
            cout << endl << string(106, '-') << endl;

            current = current->next;
            rank++;

        }
    }

    void LeaderBoardshow()
    {
        cout << endl << "\t\t\tLeaderboard" << endl;
        cout << string(106, '-') << endl;
        cout << "||" << "Ranking\t";
        cout << "||" << "Student\t";
        cout << "||" << "Round 1\t";
        cout << "||" << "Round 2\t";
        cout << "||" << "Round 3\t";
        cout << "||" << "Overall Score\t";
        cout << endl << string(106, '-') << endl;

        displayLeaderboard();
    }

    void getAllStudents(const string& fileName) {
        string line, name;
        int id;
        ifstream f(fileName);
        while (getline(f, line)) {
            Student* studentname = getNodeFromLine(line);
            insertBack(studentname);
        }

    }

    Student* getStudent(int id)
    {
        Student* current = head;
        while (current->studentID != id)
        {
            if (current->studentID == id)
            {
                return current;
            }
            current = current->next;
        }
    }

    Student* getNodeFromLine(const string& line) {
        stringstream ss(line);
        string idStr, name;
        if (getline(ss, idStr, ',') && getline(ss, name)) {
            if (!name.empty() && name.back() == ',') {
                name.pop_back();
            }
            int id = stoi(idStr);
            Student* newStudent = new Student(id, name);
            return newStudent;
        }
        return nullptr;
    }

    //debug and testing use
    void printname()
    {
        string name;
        int id;
        Student* current = head;

        while (current != nullptr)
        {
            cout << "Name: " << current->name << endl;
            cout << "ID: " << current->studentID << endl;
            current = current->next;
        }
    }

    Student* getHead() {
        return head;
    }

    void InsertionSortLinkedList() {
        Student* sortedList = nullptr;
        Student* temp = head;
        while (temp != nullptr) {
            Student* next = temp->next;
            if (sortedList == nullptr || sortedList->totalScore < temp->totalScore) {
                temp->next = sortedList;
                sortedList = temp;
            }
            else {
                Student* cur = sortedList;
                while (cur->next != nullptr && cur->next->totalScore >= temp->totalScore) {
                    cur = cur->next;
                }
                temp->next = cur->next;
                cur->next = temp;
            }
            temp = next;
        }
        head = sortedList;

        // release the memory
        delete temp;
    }

    Student* searchStudentByName(const string& name) {
        Student* current = head;
        //keep looping until reach the end/null
        while (current != nullptr) {
            if (current->name == name) {
                //if student name is found, return current
                return current;
            }
            current = current->next;
        }
        //after reached the end of linkedlist and still not found, display student not found!
        cout << "Student not found!";
    }

    //student info
    void displayLeaderboardRow(Student* student, int rank) {
        if (student) {
            cout << endl << string(106, '-') << endl;
            cout << std::setw(11) << rank << "\t";
            cout << std::setw(11) << student->name << "\t";
            cout << std::setw(11) << student->q1Question << "(" << student->q1Score << ")\t";
            cout << std::setw(11) << student->q2Question << "(" << student->q2Score << ")\t";
            cout << std::setw(11) << student->q3Question << "(" << student->q3Score << ")\t";
            cout << std::setw(11) << student->totalScore << "\t";
            cout << endl << string(106, '-') << endl;
        }
        else {
            cout << "Student not found." << endl;
        }
    }

    int getRank(Student* head, const string& searchName) {
        int rank = 1;
        Student* current = head;
        while (current != nullptr) {
            if (current->name == searchName) {
                return rank;
            }
            current = current->next;
            rank++;
        }
        // If the student is not found, return -1 to indicate that
        return -1;
    }

};
