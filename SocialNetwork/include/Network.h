#ifndef NETWORK_H
#define NETWORK_H

#include <unordered_map>
#include <string>
#include<algorithm>
#include <iostream>
#include "User.h"
#include "Graph.h"
#include "Post.h"

using namespace std;

class Network
{
private:
    unordered_map<string, User *> usersTable;
    Graph socialGraph;

public:
    void registerUser(const string &username, const string &password);
    User *login(const string &username, const string &password);
    void suggestFriends(User *user);
    void viewProfile(const User *currentUser, const User *profileUser) const;
    bool deleteUser(const string &username);
    void likePost(User *user, int postIndex);
    void unlikePost(User *user, int postIndex);
    void addComment(User *user, int postIndex, const string &comment);
    unordered_map<std::string, User *> &getUsersTable()
    {
        return usersTable;
    }
    void viewProfileWithInteraction(User *currentUser, User *profileUser) const;
};

#endif