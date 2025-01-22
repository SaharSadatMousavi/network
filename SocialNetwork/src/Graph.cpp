#include "Graph.h"
#include <algorithm>

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
    vector<pair<double, User *>> suggestionsWithP;
    const vector<User *> &followers = getFollowers(user);

    for (const auto &pair : adjacencyList)
    {
        User *otherUser = pair.first;
        if (otherUser == user)
            continue;

        const vector<User *> &otherFollowers = getFollowers(otherUser);
        int commonFollowers = 0;

        for (User *follower : followers)
        {
            if (find(otherFollowers.begin(), otherFollowers.end(), follower) != otherFollowers.end())
            {
                commonFollowers++;
            }
        }

        double probability = (double)commonFollowers / (followers.size() + otherFollowers.size() - commonFollowers);
        if (probability > 0)
        {
            suggestionsWithP.push_back(make_pair(probability, otherUser));
        }
    }

    if (suggestionsWithP.empty())
    {
        for (const auto &pair : adjacencyList)
        {
            if (pair.first != user)
            {
                suggestionsWithP.push_back(make_pair(0.0, pair.first));
                if (suggestionsWithP.size() >= 6)
                    break;
            }
        }
    }

    sort(suggestionsWithP.begin(), suggestionsWithP.end(), [](const pair<double, User *> &a, const pair<double, User *> &b)
         { return a.first > b.first; });

    vector<User *> suggestions;
    for (const auto &pair : suggestionsWithP)
    {
        suggestions.push_back(pair.second);
        if (suggestions.size() >= 6)
            break;
    }

    return suggestions;
}
void Graph::removeUser(User *user)
{
    adjacencyList.erase(user);

    for (auto &pair : adjacencyList)
    {
        auto &followers = pair.second;
        followers.erase(remove(followers.begin(), followers.end(), user), followers.end());
    }
}