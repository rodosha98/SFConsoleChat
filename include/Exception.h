#pragma once 

#include <exception>

struct UserLoginExp : public std::exception
{
    const char *what() const noexcept override
    {
        return "error::user login is busy";
    }
};

struct UserAllExp : public std::exception
{
    const char *what() const noexcept override
    {
        return "error:: login all is restricted";
    }
};