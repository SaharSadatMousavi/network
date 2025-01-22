#include "Post.h"
#include "User.h"

void Post::addLike(User *user)
{
    likes.push_back(user);
}

void Post::unlike(User *user)
{
    likes.erase(remove(likes.begin(), likes.end(), user), likes.end()); 
}
void Post::addComment(const string &text, User *author)
{
    comments.push_back(Comment(text, author));
}

