#include "Chat.h"
#include <iostream>

void Chat::start()
{
    isChatWork_ = true;
}

bool Chat::isChatWork() const
{
    return isChatWork_;
}

std::shared_ptr<User> Chat::getUserByLogin(
    const std::string& login ) const 
{
    for (auto& user : users_)
    {
        if (user.getUserLogin() == login)
        {
            return std::make_shared<User>(user);
        }
    }

    return nullptr;
}

void Chat::signUp()
{
    std::string login; 
    std::string name; 
    std::string password;
    std::string password_confirmed;

    std::cout << "Welcome to chat registration panel!" << std::endl;

    //check if login already exists in the base
    bool isloginfree = false;
    while (!isloginfree)
    {
        std::cout << "Enter your login" << std::endl;
        std::cin >> login;

        for (auto& user : users_)
        {
            if (user.getUserLogin() == login)
            {
                std::cout << "User with such login already exists" << std::endl;
                break;
            }
            else if (user.getUserLogin() == "all")
            {
                std::cout << "User with login <all> is restricted" << std::endl;
                break;
            }
        }
        isloginfree = true;
    }

    do 
    {
        std::cout << "Enter your name" << std::endl;
        std::cin >> name;
    }   while(name.empty());

    User user{login, name};
    user.setUserPassword();

    users_.push_back(user);
    currentUser_ = std::make_shared<User>(user);
    
}

void Chat::signIn()
{
    std::string login;
    std::string password;

    std::cout << "Welcome to Sign In panel!" << std::endl;

    std::cout << "Enter Login" << std::endl;
    std::cin >> login;

    currentUser_ = getUserByLogin(login);

    if (currentUser_ == nullptr)
    {
        std::cout << "Such user doesn't exist" << std::endl;
    }
    else
    {
        bool is_correct = false;
        //3 attempts to enter correct password
        for (int i = 0; i < 3; i++)
        {
            std::cout << "Enter password" << std::endl;
            std::cin >> password;
            
            //check if password is correct
            if (password == currentUser_->getUserPassword())
            {
                is_correct = true;
                std::cout << "Welcome, " << currentUser_->getUserName() << std::endl;
                break;
            }
            else
            {
                std::cout << "Wrong password! Try again. Attempts: " << 2 - i << std::endl;
            }
        }

        if (!is_correct)
        {
            std::cout << "Authorization failed" << std::endl;
            currentUser_ == nullptr;
            return;
        }
    }
}


void Chat::showStartMenu()
{
    currentUser_ = nullptr;
    char operation;

    std::cout << "\033[32m" << "Welcome to chat start menu. Choose one of the following operations" << std::endl;
    while(!currentUser_ && isChatWork_)
    {
        std::cout << std::endl;
        std::cout << "\033[1m\033[32m" << "1 - SignIn" << std::endl;
        std::cout << "\033[1m\033[32m" << "2 - SignUp" << std::endl;
        std::cout << "\033[1m\033[32m" << "0 - ShutDown" << std::endl;
        std::cout << "\033[0m" << std::endl;
        std::cin >> operation;
        
        switch(operation)
        {
        case '1':
            signIn();
            break;
        case '2':
            signUp();
            break;
        case '0':
            isChatWork_ = false;
            break;
        default:
            std::cout << "Enter valid operation" << std::endl;
            break;
        }
    }
}