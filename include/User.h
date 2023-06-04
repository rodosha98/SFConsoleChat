#pragma once
#include <string>
#include <vector>

class User 
{
public:
    User() = default;
    User(const std::string& login, const std::string& name);
    User(const std::string& login,  const std::string& password,  const std::string& name);
    ~User() = default;

    const std::string& getUserLogin() const;

    const std::string& getUserPassword() const;
    void setUserPassword();
    void changeUserPassword();
    void showPasswordRules() const;
    bool checkPassword(const std::string& password) const;

    const std::string& getUserName() const;
    void setUserName(const std::string& name);

    void showUserName() const;

    std::vector<std::string> getFriends() const;
    void addFriend(std::string& friend_login);
    void deleteFriend(std::string& friend_login);
    int getNFriends() const;
    void showFriends();


private: 
    const std::string login_;
    std::string password_;
    std::string name_;

    std::vector<std::string> friends_;
    int NFriends_ = 0;

};