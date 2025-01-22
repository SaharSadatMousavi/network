#ifndef POST_H
#define POST_H
#include <algorithm>
#include <string>
#include <vector>
#include "User.h"

using namespace std;
// وای خدا خودت کمکم کن

class User;
class Comment
{
public:
    string text;
    User *author;

    Comment(const string &text, User *author) : text(text), author(author) {}
};

class Post
{
public:
    string content;
    User *author;
    vector<User *> likes;
    vector<Comment> comments;

    Post(const string &content, User *author)
        : content(content), author(author) {}

    void addLike(User *user);
    void unlike(User *user);
    void addComment(const string &text, User *author);
};
#endif