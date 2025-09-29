#ifndef TWEET_H
#define TWEET_H

#include <bits/stdc++.h>
using namespace std;

class Tweet
{
private:
    int id;
    string text;
    static int allid;

public:
    Tweet(string);
    int getID();
    string getTweet();
};

#endif