#include "../include/Panel.h"

Panel::Panel()
{
    user_menu.menu_head("My Tweeter");
    user_menu.add("New Tweet", 1);
    user_menu.add("Diplay Tweets", 2);
    user_menu.add("Reply Tweet", 3);
    user_menu.add("Search User", 4);
    user_menu.add("Search tweet by ID", 5);
    user_menu.add("Search tweet by text", 6);
    user_menu.add("My profile", 7);
    user_menu.add("Edit profile", 8);
    user_menu.add("Logout", 9);

    login_menu.menu_head("Twitter But Better!");
    login_menu.add("Login", 1, "I already have an account");
    login_menu.add("Sign-up", 2, "Create new account");
    login_menu.add("Exit");

    setting_menu.menu_head("Settings");
    setting_menu.add("Logout", 1);
}

void Panel::loginPage()
{
    while (true)
    {
        string username;
        int type = login_menu.display();
        switch (type)
        {
        case 1:
            login();
            break;
        case 2:
            signUp();
            sleep_for(seconds(5));
            break;
        case 3:
            cout << "Thank You!\n";
            sleep_for(seconds(5));
            exit(0);
        default:
            cout << type << endl;
            break;
        }
        getch();
    }
}

void Panel::login()
{
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    ifstream username_file, password_file, email_file;
    username_file.open("../data/usernames.txt");

    string username_in_file, password_in_file, email_in_file;

    if (Email_valid(username))
    {
        while (username_file >> username_in_file)
        {
            email_file.open("../data/" + username_in_file + "/email.txt");
            email_file >> email_in_file;
            email_file.close();
            

            if (username == email_in_file)
            {
                password_file.open("../data/" + username_in_file + "/password.txt");
                password_file >> password_in_file;
                password_file.close();

                if (password == password_in_file)
                {
                    cout << "Login successful\n!";
                    username_file.close();
                    sleep_for(seconds(2));
                    userPage(User(username_in_file));
                    return;
                }
                cout << "Invalid password!";
                username_file.close();
                sleep_for(seconds(2));
                return;
            }
        }
    }
    while (username_file >> username_in_file)
    {
        if (username == username_in_file)
        {
            password_file.open("../data/" + username + "/password.txt");
            password_file >> password_in_file;
            password_file.close();
            username_file.close();
            if (password == password_in_file)
            {
                cout << "Login successful\n";
                sleep_for(seconds(2));
                userPage(User(username));
                return;
            }
            cout << "The password is invalid\n";
            sleep_for(seconds(2));
            return;
        }
    }
    username_file.close();
    cout << "User with this username was not found\n";
    sleep_for(seconds(2));
    return;
}

void Panel::signUp()
{
    string firstname, lastname, username, password, mail;
    cout << "Enter your Firstname: ";
    cin >> firstname;
    cout << "Enter your Lastname: ";
    cin >> lastname;
    cout << "Enter your Username: ";
    cin >> username;
    cout << "Enter your Email adress: ";
    cin >> mail;
    cout << "Enter your Password: ";
    cin >> password;

    ifstream username_file;
    username_file.open("../data/usernames.txt");

    string username_in_file;
    while (username_file >> username_in_file)
    {
        if (username == username_in_file)
        {
            cout << "Error! Duplicate username!\n";
            username_file.close();
            return;
        }
    }
    if (!Email_valid(mail))
    {
        cout << "Email is not Valid!";
        username_file.close();
        return;
    }

    ifstream emails_file;
    emails_file.open("../data/allemails.txt");
    string email_in_file;
    while (emails_file >> email_in_file)
    {
        if (mail == email_in_file)
        {
            cout << "Error! Duplicate Email!\n";
            emails_file.close();
            return;
        }
    }

    if (!isValid(password))
    {
        cout << "The password is not Valid" << endl;
        username_file.close();
        return;
    }
    string confpass;
    cout << "Re-enter your password: ";
    cin >> confpass;
    if (!(password == confpass))
    {
        cout << "Password does not match!";
        username_file.close();
        return;
    }
    cout << "The account was created successfully\n";
    username_file.close();
    User new_user(firstname, lastname, username, password, mail);

    string birthDate;
    ofstream birthDate_file;
    birthDate_file.open("../data/" + username + "/birthdate.txt");

    cout << "Enter your date of birth in YYYY/MM/DD (Enter -1 to leave empty): ";
    cin >> birthDate;

    int year, month, day;
    if (birthDate != "-1")
    {
        year = stoi(birthDate.substr(0, 4));
        month = stoi(birthDate.substr(5, 2));
        day = stoi(birthDate.substr(8, 2));

        if (isValidDate(day, month, year))
        {
            birthDate_file << birthDate << '\n';
            birthDate_file.close();
            cout << "Birth date added successfully." << endl;
        }
        else
        {
            cout << "Invalid date" << endl;
            birthDate_file.close();
        }
    }
    else
    {
        birthDate_file.close();
    }

    string gender;
    ofstream gender_file;
    gender_file.open("../data/" + username + "/gender.txt");

    cout << "Enter your gender [Male/Female] (Enter -1 to leave empty): ";
    cin >> gender;

    if (gender != "-1")
    {
        if (gender == "Male" || gender == "Female")
        {
            gender_file << gender << '\n';
            gender_file.close();
            cout << "Gender added successfully." << endl;
        }
        else
        {
            cout << "Gender not valid.";
            gender_file.close();
            return;
        }
    }
    else
    {
        gender_file.close();
    }
    return;
}

// validate  password
bool isValid(string password)
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

bool isChar(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool Email_valid(string email)
{
    if (!isChar(email[0]))
    {
        return 0;
    }
    int At = -1, Dot = -1;
    for (int i = 0;
         i < email.length(); i++)
    {
        if (email[i] == '@')
        {

            At = i;
        }
        else if (email[i] == '.')
        {

            Dot = i;
        }
    }
    if (At == -1 || Dot == -1)
        return 0;
    if (At > Dot)
        return 0;
    return !(Dot >= (email.length() - 1));
}

// Date Validation
const int MAX_VALID_YR = 9999;
const int MIN_VALID_YR = 1800;

bool isLeap(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}

bool isValidDate(int d, int m, int y)
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
        if (isLeap(y))
            return (d <= 29);
        else
            return (d <= 28);
    }
    if (m == 4 || m == 6 ||
        m == 9 || m == 11)
        return (d <= 30);

    return true;
}

void Panel::userPage(User user)
{
    int type;
    while (true)
    {
        getch();
        type = user_menu.display();
        string tweet_text;
        string searched;
        switch (type)
        {
        case 1:
            cout << "Enter the text of the tweet: ";
            getline(cin, tweet_text);
            user.addTweet(Tweet(tweet_text));
            cout << "Accepted\n";
            sleep_for(seconds(2));
            break;
        case 2:
            user.showTweets();
            sleep_for(seconds(5));
            break;
        case 3:
            user.replytweet();
            sleep_for(seconds(5));
            break;
        case 4:
            cout << "Enter the username: ";
            cin >> searched;
            user.searchUser(searched);
            sleep_for(seconds(5));
            break;

        case 5:
            user.searchTweetID();
            sleep_for(seconds(2));
            break;
        case 6:
            user.searchTweetText();
            sleep_for(seconds(2));
            break;
        case 7:
            user.profilePage();
            sleep_for(seconds(5));
            break;
        case 8:
            user.editProfile();
            sleep_for(seconds(5));
            break;
        case 9:
            getch();
            loginPage();
            break;
        default:
            cout << type << endl;
            break;
        }
        getch();
    }
}

int main()
{
    Panel main_panel;
    main_panel.loginPage();
    return 0;
}
