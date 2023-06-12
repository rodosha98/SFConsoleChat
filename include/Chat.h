#pragma once 

#include<memory>
#include <vector>
#include "Message.h"
#include "User.h"


class Chat 
{
public:
    //chat start funtcion
    void start();
    //get chat status
    bool isChatWork() const;
    //show start menu signIn, signUp, Exit
    void showStartMenu();
    //show user menu with options
    void showUserMenu();
    //get current user status, show user menu if not nullptr
    std::shared_ptr<User> getCurrentUser();


private: 
    bool isChatWork_ = false; 
    std::vector<User> users_; // user array
    std::vector<Message> messages_; // message array
    std::shared_ptr<User> currentUser_ = nullptr;

    std::shared_ptr<User> getUserByLogin(const std::string& login) const;
    //register new user
    void signUp(); 
    //enter chat
    void signIn();
    //show input messages
    void showChat() const;
    //write message to all or user_login
    void writeMessage();
    //add user to friend list if exists
    void addUserFriend();
    //delete user from friend list if exists
    void deleteUserFriend();
    //show user friend list
    void showUserFriends() const;
    //show number of friends
    void showNumberOfFriends() const;
};