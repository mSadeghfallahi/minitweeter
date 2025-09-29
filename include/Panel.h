#ifndef PANEL_H
#define PANEL_H

#include <bits/stdc++.h>

#include "mmaker.h"
#include "Tweet.h"
#include "User.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

class Panel {
    private:
        menu login_menu, user_menu, setting_menu;
    public:
        Panel();
        void loginPage();
        void userPage(User);
        void login();
        void signUp();


};
bool isValid (string);
bool isChar (char);
bool Email_valid (string);
bool isLeap (int);
bool isValidDate (int, int, int);

#endif 