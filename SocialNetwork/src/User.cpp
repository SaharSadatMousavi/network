#include "User.h"
#include <algorithm>
#include <iostream>
#include <sstream> 
#include <iomanip>
using namespace std;

string User::hashPassword(const string &password)const
{
    
    unsigned long hash = 5381;
    for (char c : password)
    {
        hash = ((hash << 5) + hash) + c; 
    }
    stringstream ss;
    ss << hex << hash;
    return ss.str();
}
User::User(const string &username, const string &password)
    : username(username), passwordHash(hashPassword(password)) {} // ذخیره هش پسورد

string User::getUsername() const
{
    return username;
}

void User::setProfileInfo(const string &info)
{
    profileInfo = info;
    cout << "Profile updated successfully!\n";
}

string User::getProfileInfo() const
{
    return profileInfo;
}

void User::addPost(const string &post)
{
    posts.push_back(post);
}

void User::deletePost(int index)
{
    if (index >= 0 && index < posts.size())
    {
        posts.erase(posts.begin() + index);
    }
}

void User::addFollower(User *follower)
{
    followers.push_back(follower);
}

void User::removeFollower(User *follower)
{
    followers.erase(remove(followers.begin(), followers.end(), follower), followers.end());
}

const vector<User *> &User::getFollowers() const
{
    return followers;
}

bool User::checkPassword(const string &password) const
{
    return passwordHash == hashPassword(password);
}