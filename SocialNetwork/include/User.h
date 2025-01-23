#ifndef USER_H
#define USER_H
#include "Post.h"
#include <string>
#include <vector>
using namespace std;
class Post;
class User
{
private:
    string username;
    string passwordHash;
    string profileInfo;
    vector<Post *> posts;
    vector<User *> followers;
    vector<User *> following;

    string hashPassword(const string &password) const;

public:
    User(const string &username, const string &password);
    string getUsername() const;
    void setProfileInfo(const string &info);
    string getProfileInfo() const;
    void addPost(const string &content);
    void deletePost(int index);
    void follow(User *userToFollow);
    void removeFollower(User *follower);
    const vector<User *> &getFollowers() const;
    const vector<User *> &getFollowing() const;
    bool checkPassword(const string &password) const;
    bool canViewProfile(const User *viewer) const;
    const vector<Post *> &getPosts() const;
};

#endif