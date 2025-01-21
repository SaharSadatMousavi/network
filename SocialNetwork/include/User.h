#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;

class User {
private:
    string username;
    string password;
    string profileInfo;
    vector<string> posts;
    vector<User*> followers;

public:
    User(const string& username, const string& password);
    string getUsername() const;
    void setProfileInfo(const string& info);
    string getProfileInfo() const;
    void addPost(const string& post);
    void deletePost(int index);
    void addFollower(User* follower);
    void removeFollower(User* follower);
    const vector<User*>& getFollowers() const;
    bool checkPassword(const string& password) const;
};

#endif