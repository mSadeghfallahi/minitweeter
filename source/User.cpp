#include "../include/User.h"

User::User(string fn, string ln, string un, string pw, string E) : firstName(fn), lastName(ln), userName(un), pass(pw), Email(E)
{
    // add user to end of file user.txt
    ofstream username_file, emails_file;
    username_file.open("../data/usernames.txt", ios::app);
    username_file << userName << "\n";
    username_file.close();

    emails_file.open("../data/allemails.txt", ios::app);
    emails_file << Email << "\n";
    emails_file.close();

    // make a folder for this users twitter
    string command = "mkdir ../data/" + userName;
    system(command.c_str());

    // make a file for this users tweets
    ofstream password_file, firstname_file, lastname_file, email_file, following_file, follower_file;

    password_file.open("../data/" + userName + "/password.txt");
    password_file << pass << '\n';
    password_file.close();

    firstname_file.open("../data/" + userName + "/firstname.txt");
    firstname_file << firstName << '\n';
    firstname_file.close();

    lastname_file.open("../data/" + userName + "/lastname.txt");
    lastname_file << lastName << '\n';
    lastname_file.close();

    email_file.open("../data/" + userName + "/email.txt");
    email_file << Email << '\n';
    email_file.close();

    following_file.open("../data/" + userName + "/following.txt");
    following_file.close();

    follower_file.open("../data/" + userName + "/follower.txt");
    follower_file.close();
}

User::User(string u)
{
    userName = u;
}

void User::addTweet(Tweet tweet)
{
    ofstream id_tweets_file;
    id_tweets_file.open("../data/" + userName + "/tweets_id.txt", ios::app);
    id_tweets_file << tweet.getID() << "\n";
    id_tweets_file.close();

    ofstream tweet_text;
    string tmp = to_string(tweet.getID());
    tweet_text.open("../data/" + userName + "/" + tmp + ".txt");
    tweet_text << tweet.getTweet() << '\n';
    tweet_text.close();

    ofstream tweet_likes;
    tweet_likes.open("../data/" + userName + "/" + tmp + "likes.txt");
    tweet_likes << 0;
    tweet_likes.close();

    ofstream tweet_replies;
    tweet_replies.open("../data/" + userName + "/" + tmp + "replies.txt");
    tweet_replies.close();
}

void User::showTweets()
{
    ifstream follow_file;
    follow_file.open("../data/" + userName + "/following.txt");
    string username;
    while (follow_file >> username)
    {
        ifstream id_tweets_file;
        id_tweets_file.open("../data/" + username + "/tweets_id.txt");
        string id_tweet;
        while (id_tweets_file >> id_tweet)
        {
            cout << username << ":\n";
            ifstream tweet_text;
            tweet_text.open("../data/" + username + "/" + id_tweet + ".txt");
            string text;
            getline(tweet_text, text);
            cout << "    " << text << "\n\n";

            string answer;
            cout << "Open tweet? [Y/N]: ";
            cin >> answer;
            if (answer == "Y")
            {
                OpenTweet(username, id_tweet);
            }
        }
    }
    cout << "--------------" << endl;;
    return;
}
void User ::OpenTweet(string username, string id)
{
    ifstream tweettxt;
    tweettxt.open("../data/" + username + "/" + id + ".txt");
    string text;
    getline(tweettxt, text);
    cout << username << ": \n";
    cout << "Content:    " << text << "\n\n";

    ifstream likes_file;
    likes_file.open("../data/" + username + "/" + id + "likes.txt");
    int likes;
    likes_file >> likes;
    cout << "Likes: " << likes << endl;
    likes_file.close();

    cout << "Like this Tweet? [Y/N]: ";
    string answer;
    cin >> answer;

    if (answer == "Y")
    {
        ofstream newlikes_file;
        newlikes_file.open("../data/" + username + "/" + id + "likes.txt");
        likes++;
        newlikes_file << likes;
        cout << "Liked!" << endl;
        newlikes_file.close();
    }

    if (userName == username)
    {
        cout << "Delete Tweet? [Y/N]: ";
        string response;
        cin >> response;
        if (response == "Y")
        {
            string filepath = "../data/" + username + "/" + id + ".txt";
            int result1 = remove(filepath.c_str());

            filepath = "../data/" + username + "/" + id + "likes.txt";
            int result2 = remove(filepath.c_str());

            filepath = "../data/" + username + "/" + id + "replies.txt";
            int result3 = remove(filepath.c_str());

            int count;
            ifstream count_file;
            count_file.open ("../data/count_tweet.txt");
            count_file >> count;
            count_file.close();

            count--;
            ofstream newcount_file;
            newcount_file.open("../data/count_tweet.txt");
            newcount_file << count;
            newcount_file.close();
            
            filepath = "../data/" + username + "/tweets_id.txt";
            ifstream inputFile(filepath);
            vector<std::string> lines;
            string line;
            while (getline(inputFile, line))
            {
                lines.push_back(line);
            }
            inputFile.close();

            bool found = false;
            size_t index = 0;
            for (const std::string &currentLine : lines)
            {
                if (currentLine.find(id) != std::string::npos)
                {
                    found = true;
                    break;
                }
                index++;
            }
            lines.at(index).erase(0, id.length() + (id.find(" ") != string::npos));
            string tempFilePath = filepath + ".tmp";
            ofstream tempFile(tempFilePath);

            copy(lines.begin(), lines.end(), std::ostream_iterator<std::string>(tempFile, "\n"));
            tempFile.close();
            remove(filepath.c_str());
            rename(tempFilePath.c_str(), filepath.c_str());

            cout << "Tweet was deleted!" << endl;
        }
    }
    return;
}

void User ::searchUser(string username_search)
{
    ifstream username_file;
    int found = 0;
    string username;

    username_file.open("../data/usernames.txt");

    while (username_file >> username)
    {
        if (username == username_search)
        {
            found++;
        }
    }

    if (found == 0)
    {
        cout << "Username not found!";
        username_file.close();
        return;
    }

    profilePage(username_search);
    followReq(username_search);
    return;
}

string User::getUsername()
{
    return userName;
}

void User ::profilePage(string userprof)
{
    ifstream firstname_file, lastname_file, follower_file, following_file;
    string fname, lname;
    cout << "Username : " << userprof << endl;

    firstname_file.open("../data/" + userprof + "/firstname.txt");
    firstname_file >> fname;
    cout << "First name : " << fname << endl;

    lastname_file.open("../data/" + userprof + "/lastname.txt");
    lastname_file >> lname;
    cout << "Last name : " << lname << endl;

    string fuser;
    follower_file.open("../data/" + userprof + "/follower.txt");
    cout << "Followers : " << endl;
    while (follower_file >> fuser)
    {
        cout << fuser << endl;
    }

    string fuser2;
    following_file.open("../data/" + userprof + "/following.txt");
    cout << "Following: " << endl;
    while (following_file >> fuser2)
    {
        cout << fuser << endl;
    }

    cout << "Tweets : " << endl;
    ifstream id_tweets_file;
    id_tweets_file.open("../data/" + userprof + "/tweets_id.txt");
    string id_tweet;
    while (id_tweets_file >> id_tweet)
    {
        cout << userprof << ":\n";
        ifstream tweet_text;
        tweet_text.open("../data/" + userprof + "/" + id_tweet + ".txt");
        string text;
        getline(tweet_text, text);
        cout << "    " << text << "\n\n";
    }
}
void User ::profilePage()
{
    ifstream firstname_file, lastname_file, follower_file, following_file;
    string fname, lname;
    cout << "Username : " << userName << endl;

    firstname_file.open("../data/" + userName + "/firstname.txt");
    firstname_file >> fname;
    cout << "First name : " << fname << endl;

    lastname_file.open("../data/" + userName + "/lastname.txt");
    lastname_file >> lname;
    cout << "Last name : " << lname << endl;

    string fuser;
    follower_file.open("../data/" + userName + "/follower.txt");
    cout << "Followers : " << endl;
    while (follower_file >> fuser)
    {
        cout << fuser << "\n";
    }

    string fuser2;
    following_file.open("../data/" + userName + "/following.txt");
    cout << "Following: " << endl;
    while (following_file >> fuser2)
    {
        cout << fuser2 << "\n";
    }

    cout << "Tweets : " << endl;
    ifstream id_tweets_file;
    id_tweets_file.open("../data/" + userName + "/tweets_id.txt");
    string id_tweet;
    while (id_tweets_file >> id_tweet)
    {
        cout << userName << ":\n";
        ifstream tweet_text;
        tweet_text.open("../data/" + userName + "/" + id_tweet + ".txt");
        string text;
        getline(tweet_text, text);
        cout << "    " << text << "\n\n";
    }
}

void User ::followReq(string userprof)
{
    ifstream following_file1;
    string followUser;

    following_file1.open("../data/" + userName + "/following.txt");
    while (following_file1 >> followUser)
    {
        if (followUser == userprof)
        {
            cout << "ALREADY FOLLOWING" << endl;
            following_file1.close();
            return;
        }
    }

    ofstream following_file2;
    ofstream follower_file;
    string answer;
    cout << "Follow this user [Y/N]? : ";
    cin >> answer;
    if (answer == "Y")
    {
        following_file2.open("../data/" + userName + "/following.txt", ios ::app);
        following_file2 << userprof << '\n';

        follower_file.open("../data/" + userprof + "/follower.txt", ios ::app);
        follower_file << userName << "\n";

        cout << "STARTED FOLLOWING" << endl;
        return;
    }
    else if (answer == "N")
    {
        return;
    }
    else
    {
        cout << "Invalid input" << endl;
        return;
    }
}

void User ::editProfile()
{
    cout << "What do you want to edit ?" << endl;
    cout << "Firstname: 1 ; Lastname: 2 ; BirthDate: 3 ; Gender: 4 ; Password: 5" << endl;
    cout << "Response: ";
    int response;
    cin >> response;

    string newfirst, newlast, newdate, newgen, newpass;
    ofstream firstname_file, lastname_file, date_file, gen_file, pass_file;
    int year, month, day;
    bool result;
    switch (response)
    {
    case 1:
        cout << "Enter new firstname: ";
        cin >> newfirst;
        firstname_file.open("../data/" + userName + "/firstname.txt");
        firstname_file << newfirst << '\n';
        firstname_file.close();
        cout << "Firstname edited successfully!" << endl;
        break;

    case 2:
        cout << "Enter new lastname: ";
        cin >> newlast;
        lastname_file.open("../data/" + userName + "/lastname.txt");
        lastname_file << newlast << '\n';
        lastname_file.close();
        cout << "Lastname edited successfully!" << endl;
        break;

    case 3:
        cout << "Enter new birth date: ";
        cin >> newdate;
        date_file.open("../data/" + userName + "/birthdate.txt");
        date_file << newdate << '\n';

        year = stoi(newdate.substr(0, 4));
        month = stoi(newdate.substr(5, 2));
        day = stoi(newdate.substr(8, 2));

        result = isValidDate2(day, month, year);
        if (!result)
        {
            cout << "Date not Valid.";
            date_file.close();
            return;
        }

        date_file.close();
        cout << "Birth Date edited successfully!" << endl;
        break;

    case 4:
        cout << "Enter new gender [Male / Female]: ";
        cin >> newgen;

        if (!(newgen == "Male" || newgen == "Female"))
        {
            cout << "Gender not valid.";
            return;
        }

        gen_file.open("../data/" + userName + "/gender.txt");
        gen_file << newgen << '\n';
        gen_file.close();
        cout << "Gender edited successfully!";
        break;
    case 5:
        cout << "Enter new password: ";
        cin >> newpass;

        if (!isValid2(newpass))
        {
            cout << "Password is not valid";
            return;
        }

        pass_file.open("../data/" + userName + "/password.txt");
        pass_file << newpass << '\n';

        pass_file.close();
        cout << "Password Edited Successfully!";
    }
    return;
}

void User ::replytweet()
{
    string username, tweet_id;
    ofstream reply_file;
    ifstream tweet_file;

    cout << "Enter the username: ";
    cin >> username;
    cout << "Enter tweet ID: ";
    cin >> tweet_id;

    tweet_file.open("../data/" + username + "/" + tweet_id + ".txt");
    string text;
    getline(tweet_file, text);
    cout << "Content    " << text << "\n\n";
    tweet_file.close();

    string reply;
    cout << "Type your response: ";
    cin.ignore();
    getline(cin, reply);

    reply_file.open("../data/" + username + "/" + tweet_id + "replies.txt", ios ::app);
    string reply_text;
    reply_text = userName + " : " + reply;
    reply_file << reply_text<< '\n';
    reply_file.close();

    cout << "Reply added successfully!";

    return;
}

void User ::searchTweetID()
{
    string username, tweet_id;
    ofstream reply_file;
    ifstream tweet_file;

    cout << "Enter tweet ID: ";
    cin >> tweet_id;

    ifstream usernames_file;
    ifstream tweets_id_file;
    string file_id;

    usernames_file.open("../data/usernames.txt");
    string user2;
    bool found = false;
    while (usernames_file >> user2)
    {
        tweets_id_file.open("../data/" + user2 + "/tweets_id.txt");
        while (tweets_id_file >> file_id)
        {
            if (file_id == tweet_id)
            {
                found = true;
                username = user2;
                break;
            }
        }
        tweets_id_file.close();
    }
    usernames_file.close ();

    if (!found)
    {
        cout << "Tweet not found.";
        return;
    }

    OpenTweet(username, tweet_id);
}

void User ::searchTweetText()
{
    string search_tweet;

    cout << "Enter the text you want to search: ";
    cin.ignore();
    getline(cin, search_tweet);

    bool found = false;
    string found_user;
    string found_id;

    ifstream username_file;
    username_file.open("../data/usernames.txt");
    string username;
    while (username_file >> username)
    {
        ifstream id_tweets_file;
        id_tweets_file.open("../data/" + username + "/tweets_id.txt");
        string id_tweet;
        while (id_tweets_file >> id_tweet)
        {
            ifstream tweet_text;
            tweet_text.open("../data/" + username + "/" + id_tweet + ".txt");
            string text;
            getline(tweet_text, text);

            if (search_tweet == text)
            {
                found = true;
                found_user = username;
                found_id = id_tweet;
                tweet_text.close();
                break;
            }
            tweet_text.close();
        }
        id_tweets_file.close();
    }
    username_file.close();

    if (!found)
    {
        cout << "Tweet not found.";
        return;
    }

    OpenTweet(found_user, found_id);
    return;
}

const int MAX_VALID_YR = 9999;
const int MIN_VALID_YR = 1800;

bool isLeap2(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}

bool isValidDate2(int d, int m, int y)
{
    if (y > MAX_VALID_YR ||
        y < MIN_VALID_YR)
        return false;
    if (m < 1 || m > 12)
        return false;
    if (d < 1 || d > 31)
        return false;

    if (m == 2)
    {
        if (isLeap2(y))
            return (d <= 29);
        else
            return (d <= 28);
    }
    if (m == 4 || m == 6 ||
        m == 9 || m == 11)
        return (d <= 30);

    return true;
}

bool isValid2(string password)
{
    if (!((password.length() >= 8) &&
          (password.length() <= 15)))
        return false;

    if (password.find(" ") !=
        std::string::npos)
        return false;

    if (true)
    {
        int count = 0;
        for (int i = 0; i <= 9; i++)
        {
            string str1 = to_string(i);
            if (password.find(str1) !=
                std::string::npos)
                count = 1;
        }
        if (count == 0)
            return false;
    }
    // For special characters
    if (!((password.find("@") != std::string::npos) ||
          (password.find("#") != std::string::npos) ||
          (password.find("!") != std::string::npos) ||
          (password.find("~") != std::string::npos) ||
          (password.find("$") != std::string::npos) ||
          (password.find("%") != std::string::npos) ||
          (password.find("^") != std::string::npos) ||
          (password.find("&") != std::string::npos) ||
          (password.find("*") != std::string::npos) ||
          (password.find("(") != std::string::npos) ||
          (password.find(")") != std::string::npos) ||
          (password.find("-") != std::string::npos) ||
          (password.find("+") != std::string::npos) ||
          (password.find("/") != std::string::npos) ||
          (password.find(":") != std::string::npos) ||
          (password.find(".") != std::string::npos) ||
          (password.find(",") != std::string::npos) ||
          (password.find("<") != std::string::npos) ||
          (password.find(">") != std::string::npos) ||
          (password.find("?") != std::string::npos) ||
          (password.find("|") != std::string::npos)))
        return false;

    if (true)
    {
        int count = 0;
        for (int i = 65; i <= 90; i++)
        {
            char c = (char)i;
            string str1(1, c);

            if (password.find(str1) !=
                std::string::npos)
                count = 1;
        }
        if (count == 0)
            return false;
    }

    if (true)
    {
        int count = 0;
        for (int i = 97; i <= 122; i++)
        {
            char c = (char)i;
            string str1(1, c);

            if (password.find(str1) !=
                std::string::npos)
                count = 1;
        }
        if (count == 0)
            return false;
    }
    return true;
}