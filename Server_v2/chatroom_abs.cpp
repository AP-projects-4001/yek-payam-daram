#include "chatroom_abs.h"

void ChatRoom_abs::sendMessage(std::string txt, std::string user_name)
{
    Message new_message(txt,user_name);
    messages.push_back(new_message);
}

void ChatRoom_abs::setAccount(std::string accName)
{
    members.push_back(accName);
}
