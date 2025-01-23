#include "Network.h"
#include "Post.h"

#include <iostream>

void printColored(const string &text, int colorCode, bool bold );
void showLoadingAnimation();
void showSuccessMessage(const string &message);
void showErrorMessage(const string &message);

void Network::registerUser(const string &username, const string &password)
{
    if (usersTable.find(username) != usersTable.end())
    {
        cout << "Username already exists!\n";
        return;
    }
    User *newUser = new User(username, password);
    usersTable[username] = newUser;
    socialGraph.addUser(newUser);
    cout << "User registered successfully!\n";
}

User *Network::login(const string &username, const string &password)
{
    auto it = usersTable.find(username);
    if (it != usersTable.end() && it->second->checkPassword(password))
    {
        cout << "Login successful!\n";
        return it->second;
    }
    cout << "Invalid username or password!\n";
    return nullptr;
}

void Network::suggestFriends(User *user)
{
    vector<User *> suggestions = socialGraph.suggestFriends(user);
    cout << "Suggested friends for " << user->getUsername() << ":\n";
    for (User *suggestedUser : suggestions)
    {
        cout << "- " << suggestedUser->getUsername() << "\n";
    }
}

void Network::viewProfile(const User *currentUser, const User *profileUser) const
{
    if (profileUser->canViewProfile(currentUser))
    {
        cout << "Username: " << profileUser->getUsername() << "\n";
        cout << "Profile Info: " << profileUser->getProfileInfo() << "\n";
        cout << "Posts:\n";
        for (const Post *post : profileUser->getPosts())
        {
            cout << "- " << post->content << " (Likes: " << post->likes.size() << ")\n";
            for (const Comment &comment : post->comments)
            {
                cout << "  - " << comment.author->getUsername() << ": " << comment.text << "\n";
            }
        }
    }
    else
    {
        cout << "Access denied! You are not allowed to view this profile.\n";
    }
}
bool Network::deleteUser(const string &username)
{
    auto it = usersTable.find(username);
    if (it != usersTable.end())
    {
        User *user = it->second;

        socialGraph.removeUser(user);

        usersTable.erase(it);

        delete user;

        cout << "User " << username << " deleted successfully!\n";
        return true;
    }
    cout << "User " << username << " not found!\n";
    return false;
}

void Network::likePost(User *user, int postIndex)
{
    if (postIndex >= 0 && postIndex < user->getPosts().size())
    {
        user->getPosts()[postIndex]->addLike(user);
    }
}

void Network::unlikePost(User *user, int postIndex)
{
    if (postIndex >= 0 && postIndex < user->getPosts().size())
    {
        user->getPosts()[postIndex]->unlike(user);
        cout << "Post unliked successfully!\n";
    }
    else
    {
        cout << "Invalid post index!\n";
    }
}

void Network::addComment(User *user, int postIndex, const string &comment)
{
    if (postIndex >= 0 && postIndex < user->getPosts().size())
    {
        user->getPosts()[postIndex]->addComment(comment, user);
        cout << "Comment added successfully!\n";
    }
    else
    {
        cout << "Invalid post index!\n";
    }
}

void Network::viewProfileWithInteraction(User *currentUser, User *profileUser) const
{
    if (profileUser->canViewProfile(currentUser))
    {
        while (true)
        {
            cout << "Username: " << profileUser->getUsername() << "\n";
            cout << "Profile Info: " << profileUser->getProfileInfo() << "\n";
            cout << "Posts:\n";
            int postIndex = 0;
            for (const Post *post : profileUser->getPosts())
            {
                cout << postIndex << ". " << post->content << " (Likes: " << post->getLikes().size() << ")\n";
                for (const Comment &comment : post->comments)
                {
                    cout << "  - " << comment.author->getUsername() << ": " << comment.text << "\n";
                }
                postIndex++;
            }

            cout << "\nOptions:\n";
            cout << "1. Like a post\n";
            cout << "2. Add a comment\n";
            cout << "3. Back to main menu\n";
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;
            cin.ignore();

            if (choice == 1)
            { 
                int postIndex;
                cout << "Enter the post index to like: ";
                cin >> postIndex;
                cin.ignore(); 

                if (postIndex >= 0 && postIndex < profileUser->getPosts().size())
                {
                    profileUser->getPosts()[postIndex]->addLike(currentUser);
                    showLoadingAnimation();
                    showSuccessMessage("Post liked successfully!");
                }
                else
                {
                    showErrorMessage("Invalid post index!");
                }
            }
            else if (choice == 2)
            { 
                int postIndex;
                cout << "Enter the post index to comment: ";
                cin >> postIndex;
                cin.ignore();

                if (postIndex >= 0 && postIndex < profileUser->getPosts().size())
                {
                    string commentText;
                    cout << "Enter your comment: ";
                    getline(cin, commentText);
                    profileUser->getPosts()[postIndex]->addComment(commentText, currentUser);
                    showLoadingAnimation();
                    showSuccessMessage("Comment added successfully!");
                }
                else
                {
                    showErrorMessage("Invalid post index!");
                }
            }
            else if (choice == 3)
            { 
                break;
            }
            else
            {
                showErrorMessage("Invalid choice! Please try again.");
            }
        }
    }
    else
    {
        cout << "Access denied! You are not allowed to view this profile.\n";
    }
}