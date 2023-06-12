#include "Chat.h"
#include "Exception.h"
#include <iostream>

void Chat::start()
{
    isChatWork_ = true;
}

bool Chat::isChatWork() const
{
    return isChatWork_;
}

//search by login
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
                throw UserLoginExp();
            }
            else if (user.getUserLogin() == "all")
            {
                throw UserAllExp();
            }
        }
        isloginfree = true;
    }
    //accept only non empty string
    do 
    {
        std::cout << "Enter your name" << std::endl;
        std::cin >> name;
    }   while(name.empty());

    //create new user and set first password
    User user{login, name};
    user.setUserPassword();
    //add user to user array
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
    //check if user exists
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
            
            //check if password is correct: 3 attempts
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
            currentUser_ = nullptr;
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
            try
            {
                signUp();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
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

void Chat::showUserMenu()
{
    char operation;

    while (currentUser_)
    {
        std::cout << "\033[36m" << std::endl;
        std::cout << "Welcome to user menu, " << currentUser_->getUserName() << "!" << std::endl;
        std::cout << "Choose operation" << std::endl;
        std::cout << "1 - Show all chat" << std::endl;
        std::cout << "2 - Write message" << std::endl;
        std::cout << "3 - Show number of friends" << std::endl;
        std::cout << "4 - Show friends list" << std::endl;
        std::cout << "5 - Add a friend by login" << std::endl;
        std::cout << "6 - Delete a friend by login" << std::endl;
        std::cout << "0 - exit" << std::endl;
        std::cout << "\033[0m" << std::endl;

        std::cin >> operation;
            
        switch(operation)
        {
        case '1':
            showChat();
            break;
        case '2':
            writeMessage();
            break;
        case '3':
            showNumberOfFriends();
            break;
        case '4':
            showUserFriends();
            break;
        case '5':
            addUserFriend();
            break;
        case '6':
            deleteUserFriend();
            break;
        case '0':
            currentUser_ = nullptr;
            break;
        default:
            std::cout << "Enter valid operation" << std::endl;
            break;
        }

    }

}

//show messages to all or user
void Chat::showChat() const
{
    std::string from;
    std::string to;

    std::cout << "----- Chat -----" << std::endl;

    for (auto& msg : messages_)
    {
        if (currentUser_->getUserLogin() == msg.getFrom() 
        || currentUser_->getUserLogin() == msg.getTo()
        || msg.getTo() == "all")
        {
            from = (currentUser_->getUserLogin() == msg.getFrom()) ? 
            "Me" : getUserByLogin(msg.getFrom())->getUserLogin();

            if (msg.getTo() == "all")
            {
                to = "(all)";
            }
            else 
            {
                to = (currentUser_->getUserLogin() == msg.getTo()) ? 
            "Me" : getUserByLogin(msg.getTo())->getUserLogin();
            }

            std::cout << "Message from " << getUserByLogin(from)->getUserLogin() << "( " << from << " )" << " to " << to << std::endl;
            std::cout << "text: " << msg.getText() << std::endl;
        }
    }

    std::cout << "--------------------" << std::endl;
}
//write message
void Chat::writeMessage()
{
    std::string to;
    std::string text;

    std::cout << "To (login or all): ";
    std::cin >> to;
    std::cout << "Enter text: ";
    std::cin.ignore();
    getline(std::cin, text); //get line through spaces

    //receiver - all
    if (to == "all")
    {
        messages_.push_back(Message{currentUser_->getUserLogin(), "all", text});
    }
    //receiver is a certain user
    else if (!getUserByLogin(to))
    {
        std::cout << "Error sending message: Such user doesn't exist!" << std::endl;
    }
    else 
    {
        messages_.push_back(Message{currentUser_->getUserLogin(), to, text});
    }

}
//add user friend
void Chat::addUserFriend()
{
    std::string friend_login;

    std::cout << "Enter your new friend's login" << std::endl;
    std::cin >> friend_login;

    //check self-login add
    if (!friend_login.compare(currentUser_->getUserLogin()))
    {
        std::cout << "You can't add yourself as a friend" << std::endl;
        return;
    }

    //check if user is already a friend
    for (auto& user : currentUser_->getFriends())
    {
        if (!user.compare(friend_login))
        {
            std::cout << "User is already a friend" << std::endl;
            return;
        }
    }

    //check if user exists
    for (auto& user : users_)
    {
        if (!user.getUserLogin().compare(friend_login))
        {
            currentUser_->addFriend(friend_login);
            std::cout << "Friend: " << friend_login << " is added " << std::endl;
            return;
        }
    }

    std::cout << "Error: such user doesn't exist" << std::endl;
}

//delete user friend if user in the friend list
void Chat::deleteUserFriend()
{
    std::string friend_login;
    std::shared_ptr<User> friend_user = nullptr;

    std::cout << "Enter friend's login you want to delete" << std::endl;
    std::cin >> friend_login;

    //check if user is already a friend
    for (auto& user : currentUser_->getFriends())
    {
        if (!user.compare(friend_login))
        {
            currentUser_->deleteFriend(friend_login);
            std::cout << "Friend " << friend_login << " is removed " << std::endl;
            return;
        }
    }

    std::cout << "Error: such user isn't your friend" << std::endl;
}


void Chat::showUserFriends() const
{
    currentUser_->showFriends();
}

 void Chat::showNumberOfFriends() const
 {
    int n = currentUser_->getNFriends();
    if (n!= 1)
    {
    std::cout << "You have " << n << " friends" << std::endl;
    }
    else
    {
    std::cout << "You have one friend" << std::endl;
    }
 }

 std::shared_ptr<User> Chat::getCurrentUser()
 {
    return currentUser_;
 }

