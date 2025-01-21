#include "Network.h"
#include<iostream>
using namespace std;

void Network::registerUser(const string &username, const string &password)
{
    if (usersTable.find(username) != usersTable.end())
    {
        cout << "Username already exists!\n";
        return;
    }
    User *newUser = new User(username, password);
    usersTable[username] = newUser;
    socialGraph.addUser(newUser);
    cout << "User registered successfully!\n";
}

User *Network::login(const string &username, const string &password)
{
    auto it = usersTable.find(username);
    if (it != usersTable.end() && it->second->checkPassword(password))
    {
        cout << "Login successful!\n";
        return it->second;
    }
    cout << "Invalid username or password!\n";
    return nullptr;
}

void Network::suggestFriends(User* user) {
    vector<User*> suggestions = socialGraph.suggestFriends(user);
    cout << "Suggested friends for " << user->getUsername() << ":\n";
    for (User* suggestedUser : suggestions) {
        cout << "- " << suggestedUser->getUsername() << "\n";
    }
}