#include "Network.h"
#include <iostream>
#include <limits>

using namespace std;

void printMenu() {
    cout << "===== Social Network Menu =====" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Suggest Friends" << endl;
    cout << "4. View Profile" << endl;
    cout << "5. Like a Post" << endl;
    cout << "6. Unlike a Post" << endl;
    cout << "7. Add Comment" << endl;
    cout << "8. Delete Account" << endl;
    cout << "9. Exit" << endl;
    cout << "==============================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Network network;
    User* currentUser = nullptr;
    int choice;

    while (true) {
        printMenu();
        cin >> choice;

       
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                string username, password;
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                network.registerUser(username, password);
                break;
            }
            case 2: {
                string username, password;
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                currentUser = network.login(username, password);
                break;
            }
            case 3: {
                if (currentUser) {
                    network.suggestFriends(currentUser);
                } else {
                    cout << "Please login first!" << endl;
                }
                break;
            }
            case 4: {
                if (currentUser) {
                    string username;
                    cout << "Enter username to view profile: ";
                    getline(cin, username);
                    auto it = network.getUsersTable().find(username);
                    if (it != network.getUsersTable().end()) {
                        network.viewProfile(currentUser, it->second);
                    } else {
                        cout << "User not found!" << endl;
                    }
                } else {
                    cout << "Please login first!" << endl;
                }
                break;
            }
            case 5: {
                if (currentUser) {
                    int postIndex;
                    cout << "Enter post index to like: ";
                    cin >> postIndex;
                    network.likePost(currentUser, postIndex);
                } else {
                    cout << "Please login first!" << endl;
                }
                break;
            }
            case 6: {
                if (currentUser) {
                    int postIndex;
                    cout << "Enter post index to unlike: ";
                    cin >> postIndex;
                    network.unlikePost(currentUser, postIndex);
                } else {
                    cout << "Please login first!" << endl;
                }
                break;
            }
            case 7: {
                if (currentUser) {
                    int postIndex;
                    string comment;
                    cout << "Enter post index to comment: ";
                    cin >> postIndex;
                    cin.ignore(); // Clear the input buffer
                    cout << "Enter your comment: ";
                    getline(cin, comment);
                    network.addComment(currentUser, postIndex, comment);
                } else {
                    cout << "Please login first!" << endl;
                }
                break;
            }
            case 8: {
                if (currentUser) {
                    string username = currentUser->getUsername();
                    network.deleteUser(username);
                    currentUser = nullptr;
                } else {
                    cout << "Please login first!" << endl;
                }
                break;
            }
            case 9: {
                cout << "Exiting..." << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
        }
    }

    return 0;
}