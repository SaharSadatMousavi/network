#include "User.h"
#include "Post.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>

string User::hashPassword(const string &password) const
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

void User::addPost(const string &content)
{
    posts.push_back(new Post(content, this));
}

void User::deletePost(int index)
{
    if (index >= 0 && index < posts.size())
    {
        posts.erase(posts.begin() + index);
    }
}

void User::follow(User *userToFollow)
{
    if (userToFollow != this)
    {
        userToFollow->followers.push_back(this);
        this->following.push_back(userToFollow);
        cout << this->getUsername() << " is now following " << userToFollow->getUsername() << ".\n";
    }
    else
    {
        cout << "You cannot follow yourself!\n";
    }
}

void User::removeFollower(User *follower)
{
    followers.erase(remove(followers.begin(), followers.end(), follower), followers.end());
}

const vector<User *> &User::getFollowers() const
{
    return followers;
}

const vector<User *> &User::getFollowing() const
{
    return following;
}

bool User::checkPassword(const string &password) const
{
    return passwordHash == hashPassword(password);
}

bool User::canViewProfile(const User *viewer) const
{
    if (viewer == this)
    {
        return true;
    }
    for (const User *follower : followers)
    {
        if (follower == viewer)
        {
            return true;
        }
    }
    return false;
}

const vector<Post *> &User::getPosts() const
{
    return posts;
}