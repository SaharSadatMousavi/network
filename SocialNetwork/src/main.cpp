#include <iostream>
#include "Network.h"

using namespace std;

int main()
{
    Network socialNetwork;
    socialNetwork.registerUser("sahar", "1234");
    socialNetwork.registerUser("ali", "5678");
    User *user = socialNetwork.login("sahar", "1234");
    if (user)
    {
        cout << "Welcome, " << user->getUsername() << "!\n";
    }
    else
    {
        cout << "Login failed!\n";
    }
    user = socialNetwork.login("sahar", "wrongpassword");
    if (user)
    {
        cout << "Welcome, " << user->getUsername() << "!\n";
    }
    else
    {
        cout << "Login failed!\n";
    }
    return 0;
}