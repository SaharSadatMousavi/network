#ifndef NETWORK_H
#define NETWORK_H

#include "User.h"
#include "Graph.h"
#include "HashTable.h"

using namespace std;

class Network
{
private:
    HashTable<string, User *> usersTable;
    Graph socialGraph;

public:
    void registerUser(const string &username, const string &password);
    User *login(const string &username, const string &password);
    void suggestFriends(User *user);
};

#endif