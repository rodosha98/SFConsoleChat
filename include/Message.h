#pragma once 
#include<string>

class Message
{
public:
    Message() = default;
    Message(const std::string& from, const std::string& to, const std::string& text);
    ~Message() = default;

    const std::string& getFrom() const; 
    const std::string& getTo() const; 
    const std::string& getText() const; 


private:
    const std::string from_;
    const std::string to_;
    const std::string text_;
};