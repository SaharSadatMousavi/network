#include "Post.h"
#include "User.h"
#include <iostream>
void Post::addLike(User *user)
{
    if (find(likes.begin(), likes.end(), user) == likes.end())
    {
        likes.push_back(user);
        cout << user->getUsername() << " liked the post: " << content << "\n";
    }
    else
    {
        cout << "You have already liked this post!\n";
    }
}

void Post::unlike(User *user)
{
    auto it = find(likes.begin(), likes.end(), user);
    if (it != likes.end())
    {
        likes.erase(it);
        cout << user->getUsername() << " unliked the post: " << content << "\n";
    }
    else
    {
        cout << "You have not liked this post yet!\n";
    }
}

const vector<User *> &Post::getLikes() const
{
    return likes;
}
void Post::addComment(const string &text, User *author)
{
    comments.push_back(Comment(text, author));
}
