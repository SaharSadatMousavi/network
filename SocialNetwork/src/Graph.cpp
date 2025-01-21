#include "Graph.h"
#include <algorithm>
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

vector<User*> Graph::suggestFriends(User* user) {
    vector<User*> suggestions;
    const vector<User*>& followers = getFollowers(user);

    //احتمال اشنایی
    for (const auto& pair : adjacencyList) {
        User* otherUser = pair.first;
        if (otherUser == user) continue; 

        const vector<User*>& otherFollowers = getFollowers(otherUser);
        int commonFollowers = 0;

        //  فالور مشترک
        for (User* follower : followers) {
            if (find(otherFollowers.begin(), otherFollowers.end(), follower) != otherFollowers.end()) {
                commonFollowers++;
            }
        }

        // اگر حداقل یک دنبال‌کننده مشترک وجودداشت،پیشنهادبده
        if (commonFollowers > 0) {
            suggestions.push_back(otherUser);
        }
    }

    // اگر پیشنهادی نبود، کاربران جدید رو پیشنهاد بده
    if (suggestions.empty()) {
        for (const auto& pair : adjacencyList) {
            if (pair.first != user) {
                suggestions.push_back(pair.first);
                if (suggestions.size() >= 6) break; //حداکثر6
            }
        }
    }

    return suggestions;
}