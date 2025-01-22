#include <iostream>
#include "Network.h"

using namespace std;

int main()
{
    Network socialNetwork;

    //ثبت‌نام ۱۰ کاربر
    cout << "Registering 10 users...\n";
    socialNetwork.registerUser("sahar", "1234");
    socialNetwork.registerUser("ali", "5678");
    socialNetwork.registerUser("reza", "91011");
    socialNetwork.registerUser("maryam", "121314");
    socialNetwork.registerUser("ahmad", "151617");
    socialNetwork.registerUser("fatemeh", "181920");
    socialNetwork.registerUser("hossein", "212223");
    socialNetwork.registerUser("zahra", "242526");
    socialNetwork.registerUser("mohammad", "272829");
    socialNetwork.registerUser("narges", "303132");
    cout << "10 users registered successfully!\n\n";

    //ورود کاربران
    cout << "Logging in users...\n";
    User *sahar = socialNetwork.login("sahar", "1234");
    User *ali = socialNetwork.login("ali", "5678");
    User *reza = socialNetwork.login("reza", "91011");
    User *maryam = socialNetwork.login("maryam", "121314");
    User *ahmad = socialNetwork.login("ahmad", "151617");
    User *fatemeh = socialNetwork.login("fatemeh", "181920");
    User *hossein = socialNetwork.login("hossein", "212223");
    User *zahra = socialNetwork.login("zahra", "242526");
    User *mohammad = socialNetwork.login("mohammad", "272829");
    User *narges = socialNetwork.login("narges", "303132");

    if (!sahar || !ali || !reza || !maryam || !ahmad || !fatemeh || !hossein || !zahra || !mohammad || !narges)
    {
        cout << "Login failed for one or more users!\n";
        return 1;
    }
    cout << "All users logged in successfully!\n\n";

    // اضافه کردن پست‌ها
    cout << "Adding posts...\n";
    sahar->addPost("Hello, this is Sahar's first post!");
    ali->addPost("Hi, this is Ali's post!");
    reza->addPost("Reza here, just joined the network!");
    maryam->addPost("Maryam's post: Enjoying the network!");
    ahmad->addPost("Ahmad's post: Learning C++!");
    fatemeh->addPost("Fatemeh's post: Working on a project!");
    hossein->addPost("Hossein's post: Hello everyone!");
    zahra->addPost("Zahra's post: Nice to meet you all!");
    mohammad->addPost("Mohammad's post: Let's code together!");
    narges->addPost("Narges's post: Happy coding!");
    cout << "Posts added successfully!\n\n";

    //نمایش پروفایل‌ها
    cout << "Viewing profiles...\n";
    cout << "Sahar's profile:\n";
    socialNetwork.viewProfile(sahar, sahar);
    cout << "\nAli's profile (viewed by Sahar):\n";
    socialNetwork.viewProfile(sahar, ali);
    cout << "\n";

    // دنبال کردن کاربران
    cout << "Following users...\n";
    sahar->follow(ali); // Sahar, Ali رو دنبال می‌کنه
    if (ali->canViewProfile(sahar))
    {
        cout << "Sahar can view Ali's profile.\n";
    }
    else//اینجا بررسی میشه که تابع canview درست کار میکنه
    {
        cout << "Sahar cannot view Ali's profile.\n";
    }
    sahar->follow(reza);       
    ali->follow(maryam);      
    reza->follow(ahmad);      
    maryam->follow(fatemeh);  
    ahmad->follow(hossein);   
    fatemeh->follow(zahra);  
    hossein->follow(mohammad); 
    zahra->follow(narges);    
    mohammad->follow(sahar); 
    cout << "Users followed successfully!\n\n";
    //پیشنهاددوستان
    cout << "Suggesting friends...\n";

    socialNetwork.suggestFriends(sahar);

    socialNetwork.suggestFriends(ali);
    cout << "\n";

    // لایک و کامنت
    cout << "Liking and commenting on posts...\n";
    socialNetwork.likePost(sahar, 0);                        // Sahar پست خودش رو لایک می‌کنه
    socialNetwork.likePost(ali, 0);                          // Ali پست Sahar رو لایک می‌کنه
    socialNetwork.addComment(sahar, 0, "Nice post, Sahar!"); // Sahar روی پست خودش کامنت می‌ذاره
    socialNetwork.addComment(ali, 0, "Great post, Sahar!");  // Ali روی پست Sahar کامنت می‌ذاره
    cout << "\n";

    // نمایش پروفایل‌ها بعد از لایک و کامنت
    cout << "Viewing profiles after likes and comments...\n";
    cout << "Sahar's profile:\n";
    socialNetwork.viewProfile(sahar, sahar);
    cout << "\nAli's profile (viewed by Sahar):\n";
    socialNetwork.viewProfile(sahar, ali);
    cout << "\n";

    //حذف اکانت
    cout << "Deleting Reza's account...\n";
    socialNetwork.deleteUser("reza");
    cout << "Reza's account deleted successfully!\n\n";

    // نمایش پروفایل‌ها بعد از حذف اکانت
    cout << "Viewing profiles after deleting Reza's account...\n";
    cout << "Sahar's profile:\n";
    socialNetwork.viewProfile(sahar, sahar);
    cout << "\nAli's profile (viewed by Sahar):\n";
    socialNetwork.viewProfile(sahar, ali);
    cout << "\n";

    //  تست دسترسی به پروفایل بعد از حذف اکانت
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