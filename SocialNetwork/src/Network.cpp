#include "Network.h"

using namespace std;

void Network::registerUser(const string &username, const string &password)
{
    User *newUser = new User(username, password);
    usersTable[username] = newUser;
    socialGraph.addUser(newUser);
}

User *Network::login(const string &username, const string &password)
{
    auto it = usersTable.find(username);
    if (it != usersTable.end() && it->second->checkPassword(password))
    {
        return it->second;
    }
    return nullptr;
}

void Network::suggestFriends(User *user)
{
    socialGraph.suggestFriends(user);
}