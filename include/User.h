#pragma once
#include <string>
#include <vector>

class User 
{
public:
    //constructor 
    User() = default;
    //constructor for sign up
    User(const std::string& login, const std::string& name);
    User(const std::string& login,  const std::string& password,  const std::string& name);
    ~User() = default;

    const std::string& getUserLogin() const;
    const std::string& getUserPassword() const;

    //set password while sign up
    void setUserPassword();
    //change old password to new password
    void changeUserPassword();
    //show password rules(lenght, size, etc.)
    void showPasswordRules() const;
    //check if password satisfies the rules
    bool checkPassword(const std::string& password) const; 

    // get user name and change, and show it 
    const std::string& getUserName() const;
    void setUserName(const std::string& name);
    void showUserName() const;

    // get list of user friends
    std::vector<std::string> getFriends() const;
    // add a friend to the list(vector array)
    void addFriend(std::string& friend_login);
    //delete a friend from the list
    void deleteFriend(std::string& friend_login);
    //get number of friends
    int getNFriends() const;
    //show list of ftiends
    void showFriends();


private: 
    const std::string login_; //login is unique
    std::string password_; //pass and name can be changed
    std::string name_;

    std::vector<std::string> friends_; //vector array of user friends(logins)
    int NFriends_ = 0; //number of user friends

};