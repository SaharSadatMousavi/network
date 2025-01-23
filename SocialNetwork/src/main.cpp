#include "Network.h"
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>
#include <windows.h>

using namespace std;

void printColored(const string &text, int colorCode, bool bold );

void showLoadingAnimation()
{
    for (int i = 0; i < 3; i++)
    {
        system("cls");
        printColored("🌀 Loading", 36, true); // آیکون چرخش (🌀)
        for (int j = 0; j <= i; j++)
        {
            cout << ".";
        }
        cout << endl;
        Sleep(500);
    }
}

void printColored(const string &text, int colorCode, bool bold = false)
{
    cout << "\033[" << (bold ? "1;" : "0;") << colorCode << "m" << text << "\033[0m";
}

void showSuccessMessage(const string &message)
{
    printColored("✅ " + message + "\n", 32, true); // سبز با آیکون ✅
}

void showErrorMessage(const string &message)
{
    printColored("❌ " + message + "\n", 31, true); // قرمز با آیکون ❌
}

void printMenu()
{
    cout << "\033[1;36m";
    cout <<     "  \033[1;33m🌟 Social Network Menu 🌟\033[1;36m       \n" << endl;
    cout <<     " 1. 📝 \033[32mRegister\033[1;36m                  \n" << endl;
    cout <<     " 2. 🔑 \033[32mLogin\033[1;36m                     \n" << endl;
    cout <<     " 3. 👥 \033[32mSuggest Friends\033[1;36m           \n" << endl;
    cout <<     " 4. 👤 \033[32mView Profile\033[1;36m              \n" << endl;
    cout <<     " 5. 📝 \033[32mCreate a Post\033[1;36m             \n" << endl;
    cout <<     " 6. ❤️ \033[32mLike a Post\033[1;36m               \n" << endl;
    cout <<     " 7. 💔 \033[32mUnlike a Post\033[1;36m             \n" << endl;
    cout <<     " 8. 💬 \033[32mAdd Comment\033[1;36m               \n" << endl;
    cout <<     " 9. 🗑️ \033[32mDelete Account\033[1;36m            \n" << endl;
    cout <<     " 10. 🚪 \033[31mExit\033[1;36m                     \n" << endl;
    cout <<     "\033[0m";
    cout <<     "Enter your choice: ";
}

int main()
{
    Network network;
    User *currentUser = nullptr;
    int choice;

    while (true)
    {
        printMenu();
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
        {
            string username, password;
            printColored("Enter username: ", 36);
            getline(cin, username);
            printColored("Enter password: ", 36);
            getline(cin, password);
            network.registerUser(username, password);
            showLoadingAnimation();
            showSuccessMessage("User registered successfully!");
            break;
        }
        case 2:
        {
            string username, password;
            printColored("Enter username: ", 36);
            getline(cin, username);
            printColored("Enter password: ", 36);
            getline(cin, password);
            currentUser = network.login(username, password);
            if (currentUser)
            {
                showLoadingAnimation();
                showSuccessMessage("Login successful! Welcome, " + username + "!");
            }
            else
            {
                showErrorMessage("Invalid username or password!");
            }
            break;
        }
        case 3:
        {
            if (currentUser)
            {
                showLoadingAnimation();
                network.suggestFriends(currentUser);
            }
            else
            {
                showErrorMessage("Please login first!");
            }
            break;
        }
        case 4:
        {
            if (currentUser)
            {
                string username;
                printColored("Enter username to view profile: ", 36);
                getline(cin, username);
                auto it = network.getUsersTable().find(username);
                if (it != network.getUsersTable().end())
                {
                    showLoadingAnimation();
                    network.viewProfile(currentUser, it->second);
                }
                else
                {
                    showErrorMessage("User not found!");
                }
            }
            else
            {
                showErrorMessage("Please login first!");
            }
            break;
        }
        case 5:
        {
            if (currentUser)
            {
                string content;
                printColored("Enter your post content: ", 36);
                getline(cin, content);
                currentUser->addPost(content);
                showLoadingAnimation();
                showSuccessMessage("Post created successfully!");
            }
            else
            {
                showErrorMessage("Please login first!");
            }
            break;
        }
        case 6:
        {
            if (currentUser)
            {
                int postIndex;
                printColored("Enter post index to like: ", 36);
                cin >> postIndex;
                network.likePost(currentUser, postIndex);
                showLoadingAnimation();
                showSuccessMessage("Post liked successfully!");
            }
            else
            {
                showErrorMessage("Please login first!");
            }
            break;
        }
        case 7:
        {
            if (currentUser)
            {
                int postIndex;
                printColored("Enter post index to unlike: ", 36);
                cin >> postIndex;
                network.unlikePost(currentUser, postIndex);
                showLoadingAnimation();
                showSuccessMessage("Post unliked successfully!");
            }
            else
            {
                showErrorMessage("Please login first!");
            }
            break;
        }
        case 8:
        {
            if (currentUser)
            {
                int postIndex;
                string comment;
                printColored("Enter post index to comment: ", 36);
                cin >> postIndex;
                cin.ignore();
                printColored("Enter your comment: ", 36);
                getline(cin, comment);
                network.addComment(currentUser, postIndex, comment);
                showLoadingAnimation();
                showSuccessMessage("Comment added successfully!");
            }
            else
            {
                showErrorMessage("Please login first!");
            }
            break;
        }
        case 9:
        {
            if (currentUser)
            {
                string username = currentUser->getUsername();
                network.deleteUser(username);
                currentUser = nullptr;
                showLoadingAnimation();
                showSuccessMessage("User " + username + " deleted successfully!");
            }
            else
            {
                showErrorMessage("Please login first!");
            }
            break;
        }
        case 10:
        {
            showErrorMessage("Exiting...");
            return 0;
        }
        default:
        {
            showErrorMessage("Invalid choice! Please try again.");
            break;
        }
        }
    }

    return 0;
}