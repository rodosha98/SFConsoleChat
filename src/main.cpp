#include <iostream>
#include "../include/User.h"

int main(void)
{
    User user1{"rodosha", "Qwerty12345", "Oleg"};

    user1.showUserName();

    user1.setUserPassword();

    return 0;
}