//#include "G13_TP068591_TP072176_TP067443_TP066377_TP070012_student.hpp"
//#include "G13_TP068591_TP072176_TP067443_TP066377_TP070012_questions.hpp"
//#include "G13_TP068591_TP072176_TP067443_TP066377_TP070012_Tree.hpp"
//
//int main() {
//    string name;
//    StudentList namelist;
//    QuestionList ql;
//    QuestionList discardDeck;
//    int choice;
//    Student* student = nullptr;
//    string cont;
//    
//    ql.getAllQs("G13_TP068591_TP072176_TP067443_TP066377_TP070012_questions.csv");
//    ql.shuffleQuestions();
//    namelist.getAllStudents("G13_TP068591_TP072176_TP067443_TP066377_TP070012_students.csv");
//
//    for (int roundNum = 1; roundNum <= 3; roundNum++) {
//
//        for (int j = 1; j <= namelist.size; j++)
//        {
//            cout << "Round: " << roundNum << endl << endl;
//            student = namelist.getStudent(j);
//
//            cout << endl << "Name: " << student->name << endl << endl;
//
//            do {
//                discardDeck.printDiscardedQs();
//                cout << "Enter your choice: ";
//                while (true) {
//                    cin >> choice;
//                    if (cin.fail()) {
//                        cin.clear();
//                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                        cout << "Wrong input, please enter a number: ";
//                    }
//                    else {
//                        break;
//                    }
//                }
//                if (choice == (discardDeck.size + 1)) { //draw card
//                    student->drawCard(roundNum, &ql, &discardDeck);
//                }
//                else if (choice <= discardDeck.size && choice > 0) { //discarded deck
//                    student->selectDiscardedQuestion(roundNum, &discardDeck, choice);
//                }
//                else { //input validation
//                    cout << endl << "Invalid option, please try again!" << endl << endl;
//                    cin.clear(); // Clear the error flag set by invalid input
//                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                }
//            } while (choice < 1 || choice > discardDeck.size + 1 || cin.fail());
//
//            cout << "Your current score: " << student->totalScore << endl;
//            cout << "Enter 'con' to continue: ";
//            while (true) {
//                cin >> cont;
//                if (cin.fail() || cont != "con") {
//                    cin.clear();
//                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                    cout << "Invalid, please try again: ";
//                }
//                else {
//                    break;
//                }
//            }
//
//            system("cls");
//        }
//
//        namelist.InsertionSortLinkedList();
//        namelist.LeaderBoardshow(); // Display the leaderboard
//
//    }
//
//    Tree* studentTree = new Tree();
//    studentTree->buildCompleteBinaryTree(namelist.getHead());
//    studentTree->preorder();
//    studentTree->displayStudentWithBFS();
//
//    while (true) {
//        string searchName;
//        cout << "Enter the name of student to search (or type '/exit' to quit): ";
//        getline(cin, searchName);
//        if (searchName == "/exit") {
//            break;
//        }
//        int rank = namelist.getRank(namelist.getHead(), searchName);
//        if (rank != -1) {
//            Student* foundStudent = namelist.searchStudentByName(searchName);
//            namelist.displayLeaderboardRow(foundStudent, rank);
//        }
//        else {
//            cout << "Student not found." << endl;
//        }
//    }
//
//    QuestionList checkQuestionList;
//    checkQuestionList.getAllQs("G13_TP068591_TP072176_TP067443_TP066377_TP070012_questions.csv");
//    checkQuestionList.checkQuestion();
//
//    return 0;
//}