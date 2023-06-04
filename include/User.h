#pragma once
#include <string>

class User 
{
public:
    User() = default;
    User(const std::string& login,  const std::string& password,  const std::string& name);
    ~User() = default;

    const std::string& getUserLogin() const;

    const std::string& getUserPassword() const;
    void setUserPassword();
    void showPasswordRules() const;
    bool checkPassword(const std::string& password) const;

    const std::string& getUserName() const;
    void setUserName(const std::string& name);

    void showUserName() const;

private: 
    const std::string login_;
    std::string password_;
    std::string name_;

};