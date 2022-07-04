#include "private_chat.h"

Private_chat::Private_chat()
{

}

void Private_chat::sendMessage(std::string txt,std::string user_name)
{
    Message new_message(txt,user_name);
    messages.push_back(new_message);
}

void Private_chat::setName(std::string namein)
{
    name = namein;
}

