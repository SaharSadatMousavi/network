#ifndef NETWORK_H
#define NETWORK_H

#include <unordered_map>
#include <string>
#include "User.h"
#include "Graph.h"

using namespace std;

class Network {
private:
    unordered_map<string, User*> usersTable;
    Graph socialGraph;

public:
    void registerUser(const string& username, const string& password);
    User* login(const string& username, const string& password);
    void suggestFriends(User* user);
    void viewProfile(const User* currentUser, const User* profileUser) const;
    bool deleteUser(const string& username);

};

#endif