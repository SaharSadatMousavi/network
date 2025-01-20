#include "Graph.h"

using namespace std;

void Graph::addUser(User *user)
{
    adjacencyList[user] = vector<User *>();
}

void Graph::addEdge(User *user1, User *user2)
{
    adjacencyList[user1].push_back(user2);
    adjacencyList[user2].push_back(user1);
}

const vector<User *> &Graph::getFollowers(User *user) const
{
    return adjacencyList.at(user);
}

vector<User *> Graph::suggestFriends(User *user)
{
    /*...................
    .....................*/
   
    return vector<User *>(); 
}