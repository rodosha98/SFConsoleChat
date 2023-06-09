#include "User.h"
#include<iostream>

//sign up constructor
User::User(const std::string& login, const std::string& name) 
    : login_(login), name_(name) { }

User::User(const std::string& login, const std::string& password, const std::string& name) 
    : login_(login), password_(password), name_(name) { }

const std::string& User::getUserLogin() const 
{
    return this->login_;
}

const std::string& User::getUserPassword() const 
{
    return this->password_;
}

//set user password when sign up new user
void User::setUserPassword()  
{
    std::string new_pass;
    std::string confirm_pass;

    //check if password corresponds to requirements
    bool pass = false;
    while (!pass)
    {
        showPasswordRules();
        std::cout << "Enter new password" << std::endl;
        std::cin >> new_pass;
        pass = checkPassword(new_pass);
    }

    //confirm new pass(passwords must coincide)
    bool pass_confirm = false;
    while (!pass_confirm)
    {
        std::cout << "Confirm password" << std::endl;
        std::cin >> confirm_pass;
        if (!new_pass.compare(confirm_pass))
        {
            pass_confirm = true;
        }
        else
        {
            std::cout << "Confirm password failed. Try again" << std::endl;
        }
    }

    password_.clear();
    password_.assign(new_pass);
    std::cout << "Password set complete" << std::endl;

}

//change old password to new one
void User::changeUserPassword()  
{
    std::string old_pass;
    std::string new_pass;

    //3 attempts to enter the pass correctly
    std::cout << "Enter current password" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cin >> old_pass;
        if (!password_.compare(old_pass))
        {
            bool pass = false;
            while (!pass)
            {
                showPasswordRules();
                std::cout << "Enter new password" << std::endl;
                std::cin >> new_pass;
                pass = checkPassword(new_pass);
            }
            password_.clear();
            password_.assign(new_pass);
            std::cout << "Password change complete" << std::endl;
            return;
        }
        else
        {
            std::cout << "Sorry, try again. Attempts:" << 2 - i << std::endl;
        }
    }

    std::cout << "Password change failed" << std::endl;
    return;
    
}

//show password  rules to user
void User::showPasswordRules() const
{
    std::cout << "Password must satisfy the following rules: " << std::endl
     << "\t 1 - At least 8 characters long" << std::endl
     << "\t 2 - Must include a digit" << std::endl
     << "\t 3 - Must include a lower case character" << std::endl
     << "\t 4 - Must include an upper case character" << std::endl;
}

//check if password satisfies to the rules
bool User::checkPassword(const std::string& password) const
{
    const std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string lower = "abcdefghijklmnopqrstuvwxyz";
    const std::string digits = "0123456789";

    return  (password.size() >= 8 && password.find_first_of(upper) != std::string::npos
            && password.find_first_of(lower) && password.find_first_of(digits));
}

const std::string& User::getUserName() const
{
    return name_;
}

void User::setUserName(const std::string& name) 
{
    name_ = name;
}


void User::showUserName() const
{
    std::cout << this->name_ << std::endl;
}

//return vector of user friends(logins)
std::vector<std::string> User::getFriends() const
{
    return friends_;
}
//add new login to friend list
void User::addFriend(std::string& friend_login)
{
    friends_.push_back(friend_login);
    NFriends_++;
}

void User::deleteFriend(std::string& friend_login)
{
    //check the last element of vector
    if (!friend_login.compare(friends_.back()))
    {
        friends_.pop_back();
    }
    //iterate over friends vector
    for (auto it = friends_.begin(); it != friends_.end() - 1; it++)
    {
        // compare function to check if coincides
        if (!friend_login.compare(*it))
        {
            
            friends_.erase(it);
            NFriends_--;
        }
    }
}

int User::getNFriends() const
{
    return NFriends_;
}
//show list of user friends logins
void User::showFriends()
{
    int id = 1;

    for (auto& user : friends_)
    {
        std::cout << id++ << ": " << user << std::endl;
    }

    std::cout << std::endl;
}