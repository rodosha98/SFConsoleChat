#include "Message.h"

Message::Message(const std::string& from, const std::string& to, const std::string& text) :
from_(from), to_(to), text_(text) { }

const std::string& Message::getFrom() const 
{
    return from_;
}

const std::string& Message::getTo() const 
{
    return to_;
}

const std::string& Message::getText() const 
{
    return text_;
}