#ifndef USER_H
#define USER_H

#include <bits/stdc++.h>
#include "Tweet.h"

using namespace std;

class User
{
private:
    string firstName;
    string lastName;
    string userName;
    string pass;
    string Email;

public:
    User(string, string, string, string, string);
    User(string);
    void addTweet(Tweet);
    void showTweets();
    string getUsername();
    void searchUser (string);
    void profilePage (string);
    void profilePage ();
    void followReq (string);
    void OpenTweet (string, string);
    void editProfile ();
    void replytweet ();
    void searchTweetID ();
    void searchTweetText ();
};

bool isValidDate2 (int, int, int);
bool isValid2 (string);

#endif