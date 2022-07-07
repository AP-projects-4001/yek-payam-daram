#include "chatroom_abs.h"

void ChatRoom_abs::sendMessage(std::string txt, std::string user_name)
{
    Message new_message(txt,user_name);
    messages.push_back(new_message);
}

void ChatRoom_abs::setName(std::string namein)
{
    this->name = namein;
}

void ChatRoom_abs::setAdmin(std::string name)
{
    this->admins.push_back(name);
}

std::vector<std::string> ChatRoom_abs::getAdmin()
{
    return this->admins;
}

void ChatRoom_abs::setAccount(std::string accName)
{
    members.push_back(accName);
}
