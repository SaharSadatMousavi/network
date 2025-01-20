#include "Network.h"

using namespace std;

void Network::registerUser(const string& username, const string& password) {
    User* newUser = new User(username, password);
    usersTable.insert(username, newUser);
    socialGraph.addUser(newUser);
}

User* Network::login(const string& username, const string& password) {
    User** userPtr = usersTable.get(username); 
    if (userPtr && *userPtr && (*userPtr)->checkPassword(password)) {
        return *userPtr; 
    }
    return nullptr;
}

void Network::suggestFriends(User* user) {
    socialGraph.suggestFriends(user);
}