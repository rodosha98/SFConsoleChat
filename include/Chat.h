#pragma once 

#include<memory>
#include <vector>
#include "Message.h"
#include "User.h"


class Chat 
{
public:
    void start();
    bool isChatWork() const;
    void showStartMenu();


private: 
    bool isChatWork_ = false;
    std::vector<User> users_;
    std::vector<Message> messages_;
    std::shared_ptr<User> currentUser_ = nullptr;

    std::shared_ptr<User> getUserByLogin(const std::string& login) const;
    void signUp();
    void signIn();
};