#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include "User.h"

using namespace std;

class Graph
{
private:
    map<User *, vector<User *>> adjacencyList;

public:
    void addUser(User *user);
    void addEdge(User *user1, User *user2);
    const vector<User *> &getFollowers(User *user) const;
    vector<User *> suggestFriends(User *user);
};

#endif