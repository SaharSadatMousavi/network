#include <iostream>
#include "Network.h"

using namespace std;

int main()
{
    Network socialNetwork;

    cout << "Registering users...\n";
    socialNetwork.registerUser("sahar", "1234");
    socialNetwork.registerUser("ali", "5678");
    socialNetwork.registerUser("reza", "91011");
    socialNetwork.registerUser("maryam", "121314");
    cout << "Users registered successfully!\n\n";

    cout << "Logging in users...\n";
    User *sahar = socialNetwork.login("sahar", "1234");
    User *ali = socialNetwork.login("ali", "5678");
    User *reza = socialNetwork.login("reza", "91011");
    User *maryam = socialNetwork.login("maryam", "121314");

    if (!sahar || !ali || !reza || !maryam)
    {
        cout << "Login failed for one or more users!\n";
        return 1;
    }
    cout << "Users logged in successfully!\n\n";

    cout << "Viewing profiles...\n";
    cout << "Sahar's profile:\n";
    socialNetwork.viewProfile(sahar, sahar);
    cout << "\nAli's profile (viewed by Sahar):\n";
    socialNetwork.viewProfile(sahar, ali);
    cout << "\n";

    cout << "Adding posts...\n";
    sahar->addPost("Hello, this is Sahar's first post!");
    ali->addPost("Hi, this is Ali's post!");
    reza->addPost("Reza here, just joined the network!");
    maryam->addPost("Maryam's post: Enjoying the network!");

    cout << "Posts added successfully!\n\n";

    cout << "Viewing profiles after adding posts...\n";
    cout << "Sahar's profile:\n";
    socialNetwork.viewProfile(sahar, sahar);
    cout << "\nAli's profile (viewed by Sahar):\n";
    socialNetwork.viewProfile(sahar, ali);
    cout << "\n";

    cout << "Following users...\n";
    sahar->addFollower(ali);
    sahar->addFollower(reza);
    ali->addFollower(maryam);

    cout << "Users followed successfully!\n\n";

    cout << "Viewing profiles after following...\n";
    cout << "Sahar's profile (viewed by Ali):\n";
    socialNetwork.viewProfile(ali, sahar);
    cout << "\nMaryam's profile (viewed by Ali):\n";
    socialNetwork.viewProfile(ali, maryam);
    cout << "\n";

    cout << "Suggesting friends...\n";

    socialNetwork.suggestFriends(sahar);

    socialNetwork.suggestFriends(ali);
    cout << "\n";

    cout << "Deleting Reza's account...\n";
    socialNetwork.deleteUser("reza");
    cout << "Reza's account deleted successfully!\n\n";

    cout << "Viewing profiles after deleting Reza's account...\n";
    cout << "Sahar's profile:\n";
    socialNetwork.viewProfile(sahar, sahar);
    cout << "\nAli's profile (viewed by Sahar):\n";
    socialNetwork.viewProfile(sahar, ali);
    cout << "\n";

    cout << "Trying to view Reza's profile (should fail):\n";
    User *rezaAfterDeletion = socialNetwork.login("reza", "91011");
    if (rezaAfterDeletion)
    {
        socialNetwork.viewProfile(sahar, rezaAfterDeletion);
    }
    else
    {
        cout << "Reza's account not found!\n";
    }

    return 0;
}