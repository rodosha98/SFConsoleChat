#include<iostream>
#include<memory>
#include "Message.h"
#include "User.h"
#include "Chat.h"

int main(void)
{
    Chat chat;

    chat.start();
    chat.registerUsers();
    
    while (chat.isChatWork())
    {
        chat.showStartMenu();
        while (chat.getCurrentUser())   {
            chat.showUserMenu();
        }
    }
  
    return 0;
}
