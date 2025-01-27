#include "Network.h"
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>
#include <windows.h>

using namespace std;

#include <algorithm>

template <typename T>
bool isElementExists(const vector<T> &arr, const T &element)
{
    return count(arr.begin(), arr.end(), element) > 0;
}

void printColored(const string &text, int colorCode, bool bold = false)
{
    cout << "\033[" << (bold ? "1;" : "0;") << colorCode << "m" << text << "\033[0m";
}

void showLoadingAnimation()
{
    for (int i = 0; i < 3; i++)
    {
        system("cls");
        printColored("🌀 Loading", 36, true);
        for (int j = 0; j <= i; j++)
        {
            cout << ".";
        }
        cout << endl;
        Sleep(500);
    }
}

void showSuccessMessage(const string &message)
{
    printColored("✅ " + message + "\n", 32, true);
}

void showErrorMessage(const string &message)
{
    printColored("❌ " + message + "\n", 31, true);
}

void printMenu()
{
    cout << "\033[1;36m";
    cout << "  \033[1;33m🌟 Social Network Menu 🌟\033[1;36m       " << endl;
    cout << " 1. 📝 \033[32mRegister\033[1;36m                  " << endl;
    cout << " 2. 🔑 \033[32mLogin\033[1;36m                     " << endl;
    cout << " 3. 👥 \033[32mSuggest Friends\033[1;36m           " << endl;
    cout << " 4. 👤 \033[32mView Profile\033[1;36m              " << endl;
    cout << " 5. 📝 \033[32mCreate a Post\033[1;36m             " << endl;
    cout << " 6. 👤 \033[32mView Profile with Interaction\033[1;36m " << endl;
    cout << " 7. 🗑️ \033[32mDelete Account\033[1;36m            " << endl;
    cout << " 8. 👤 \033[32mFollow User\033[1;36m               " << endl;
    cout << " 9. 🚪 \033[31mExit\033[1;36m                     " << endl;
    cout << "\033[0m";
    cout << "Enter your choice: ";
}

int main()
{
    Network network;
    cout << "Registering 10 users...\n";
    network.registerUser("sahar", "1234");
    network.registerUser("ali", "5678");
    network.registerUser("reza", "91011");
    network.registerUser("maryam", "121314");
    cout << "Users registered successfully!\n\n";
    network.registerUser("ahmad", "151617");
    network.registerUser("fatemeh", "181920");
    network.registerUser("hossein", "212223");
    network.registerUser("zahra", "242526");
    network.registerUser("mohammad", "272829");
    network.registerUser("narges", "303132");
    cout << "10 users registered successfully!\n\n";

    User *sahar = network.login("sahar", "1234");
    User *ali = network.login("ali", "5678");
    User *reza = network.login("reza", "91011");
    User *maryam = network.login("maryam", "121314");
    User *ahmad = network.login("ahmad", "151617");
    User *fatemeh = network.login("fatemeh", "181920");
    User *hossein = network.login("hossein", "212223");
    User *zahra = network.login("zahra", "242526");
    User *mohammad = network.login("mohammad", "272829");
    User *narges = network.login("narges", "303132");

    cout << "Adding posts...\n";
    sahar->addPost("Hello, this is Sahar's first post!");
    ali->addPost("Hi, this is Ali's post!");
    reza->addPost("Reza here, just joined the network!");
    maryam->addPost("Maryam's post: Enjoying the network!");
    ahmad->addPost("Ahmad's post: Learning C++!");
    fatemeh->addPost("Fatemeh's post: Working on a project!");
    hossein->addPost("Hossein's post: Hello everyone!");
    zahra->addPost("Zahra's post: Nice to meet you all!");
    mohammad->addPost("Mohammad's post: Let's code together!");
    narges->addPost("Narges's post: Happy coding!");
    cout << "Posts added successfully!\n\n";

    User *currentUser = nullptr;
    int choice;
    vector<int> validC = {1, 2, 3, 4, 5, 6, 7, 8};
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
                string username;
                printColored("Enter username to view profile: ", 36);
                getline(cin, username);
                auto it = network.getUsersTable().find(username);
                if (it != network.getUsersTable().end())
                {
                    network.viewProfileWithInteraction(currentUser, it->second);
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
        case 7:
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
        case 8: 
        {
            if (currentUser)
            {
                string username;
                printColored("Enter username to follow: ", 36);
                getline(cin, username);
                auto it = network.getUsersTable().find(username);
                if (it != network.getUsersTable().end())
                {
                    currentUser->follow(it->second);
                    showLoadingAnimation();
                    showSuccessMessage("You are now following " + username + "!");
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
        case 9:
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
        if (!(isElementExists(validC, choice)))
        {
            break;
        }
    }

    return 0;
}