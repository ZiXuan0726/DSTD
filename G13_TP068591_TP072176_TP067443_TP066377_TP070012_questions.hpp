#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Question {
    int discardID;
    string question;
    string answer;
    int score;
    string questionID;
};

struct QuestionNode {
    Question* data = new Question();
    QuestionNode* prev = nullptr;
    QuestionNode* next = nullptr;
};

class QuestionList {

public:
    QuestionNode* head;
    QuestionNode* tail;
    int size;

    QuestionList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    QuestionNode* createNewNode(string questionID, string question, string answer, int score) {
        QuestionNode* node = new QuestionNode();
        node->data->questionID = questionID;
        node->data->discardID = 0;
        node->data->question = question;
        node->data->answer = answer;
        node->data->score = score;
        node->prev = nullptr;
        node->next = nullptr;
        return node;
    }

    void insertFront(QuestionNode* newQ) {
        if (head == nullptr) {
            head = newQ;
            tail = newQ;
        }
        else {
            newQ->next = head;
            head->prev = newQ;
            head = newQ;
        }
        size++;
    }

    void insertBack(QuestionNode* newQ) {
        if (tail == nullptr) {
            head = newQ;
            tail = newQ;
        }
        else {
            newQ->prev = tail;
            tail->next = newQ;
            tail = newQ;
        }
        size++;
    }

    void deleteQuestionNode(QuestionNode* delNode) {
        if (delNode == head) {
            if (head == tail) {
                head = nullptr;
                tail = nullptr;
            }
            else {
                head = head->next;
                head->prev = nullptr;
            }
        }
        else if (delNode = tail) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else {
            QuestionNode* prevNode = delNode->prev;
            QuestionNode* nextNode = delNode->next;
            prevNode->next = nextNode;
            nextNode->prev = prevNode;
        }
        size--;
    }

    //for question deck use only, delete question from question list, add question to discard deck
    void discard(QuestionNode* nodeToDiscard, QuestionList* discardDeck) {
        deleteQuestionNode(nodeToDiscard);
        nodeToDiscard->data->discardID = discardDeck->size + 1;
        nodeToDiscard->data->score = nodeToDiscard->data->score * 0.8;
        nodeToDiscard->next = nullptr;
        nodeToDiscard->prev = nullptr;
        discardDeck->insertBack(nodeToDiscard);
    }

    //retrieve question from discarded deck via id
    QuestionNode* getDiscardedQs(int ID) {
        QuestionNode* current = head;
        for (int i = 1; i < ID; i++) {
            current = current->next;
        }

        return current;
    }

    //Format question
    void printFormatedQuestion(string question) {
        stringstream ss(question);
        string line;
        while (getline(ss, line, '|')) {
            cout << line << endl;
        }
    }

    //process line read from file and create new node
    QuestionNode* getNodeFromLine(const string& line) {
        bool inQuote = false;
        stringstream ss;
        string question, answer, score, questionID;
        int i = 0;
        for (char c : line) {
            if (c == '"' && (ss.str().empty() || ss.str().back() != '\\')) {
                inQuote = !inQuote;
            }
            else if (c == ',' && !inQuote) {
                if (i == 1) {
                    question = ss.str();
                }
                else if (i == 2) {
                    answer = ss.str();
                }
                else if (i == 4) {
                    score = ss.str();
                }
                else if (i == 0) {
                    questionID = ss.str();
                }
                ss.str("");
                ss.clear();
                i++;
            }
            else {
                ss << c;
            }
        }

        return createNewNode(questionID, question, answer, stoi(score));
    }

    //add all questions into linked list
    void getAllQs(const string& fileName) {
        string line, word;

        ifstream f(fileName);
        while (getline(f, line)) {
            QuestionNode* newQuestion = getNodeFromLine(line);
            insertBack(newQuestion);
        }
    }

    // shuffle linked list
    void shuffleQuestions() {
        if (size > 2) {
            srand(time(0));
            for (int k = 0; k < size * 2; k++) {
                QuestionNode* current = head;
                QuestionNode* swap = head;
                int steps = rand() % size;
                for (int i = 0; i <= steps; i++) {
                    if (current->next) {
                        current = current->next;
                    }
                }
                int swapStep = rand() % size;
                while (swapStep == steps) { swapStep = rand() % size; }
                for (int j = 0; j <= swapStep; j++) {
                    if (swap->next) {
                        swap = swap->next;
                    }
                }
                Question* tempData = current->data;
                current->data = swap->data;
                swap->data = tempData;
            }
        }
    }

    //for testing use
    void printList() {
        QuestionNode* current = head;
        while (current != nullptr) {
            cout << "Question " << current->data->discardID << ":" << endl;
            printFormatedQuestion(current->data->question);
            cout << ", Answer: " << current->data->answer << ", Score: " << current->data->score << endl << endl;
            current = current->next;
        }
    }

    void printDiscardedQs() {
        if (size == 0) { cout << "There is no question discarded currently, please draw a new question" << endl; }
        else {
            QuestionNode* current = head;
            cout << "Discarded Questions: " << endl;
            for (int i = 0; i < size; i++) {
                cout << "[" << i + 1 << "] ";
                printFormatedQuestion(current->data->question);
                cout << endl << endl;

                current = current->next;
            }
        }
        cout << "[" << size + 1 << "] DRAW NEW QUESTION" << endl;
    }

    QuestionNode* getQuestion(string questionID)
    {
        QuestionNode* current = head;
        while (current->data->questionID != questionID) {
            current = current->next;
        }
        return current;

    }

    void checkQuestion() {
        string id;
        string ans, op;
        bool decision = false;
        bool option = true;
        while (decision != true)
        {
            cout << "Do you want to read question details? (Y/N)" << endl;
            cin >> ans;
            if (ans == "Y" || ans == "y")
            {
                while (option == true) {
                    cout << endl << "Input id: " << endl;
                    cin >> id;
                    QuestionNode* temp = getQuestion(id);
                    printFormatedQuestion(temp->data->question);
                    cout << "Correct answer is: " << temp->data->answer << endl;
                    cout << string(106, '-') << endl;
                    cout << "Do you want to continue reading question? (Y/N)" << endl;
                    cin >> op;

                    if (op == "N" || op == "n")
                    {
                        cout << "Thank you for reading the question. Hope you learn something today!" << endl;
                        break;
                    }
                    else if (op != "Y" && op != "y")
                        cout << "Invalid input! Please try again!" << endl;
                }

                decision = true;
            }
            else if (ans == "N" || ans == "n")
            {
                break;
            }
            else {
                cout << "Invalid Input! Please enter again." << endl;
            }
        }

    }

};
