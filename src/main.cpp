#include<iostream>
#include "Message.h"
#include "User.h"

int main(void)
{
    Message msg1{"rodosha", "mike_deen", "Hello!"};
    User user1{"rodosha", "Qwerty12345", "Oleg"};

    user1.showUserName();

    user1.setUserPassword();
  
    return 0;

