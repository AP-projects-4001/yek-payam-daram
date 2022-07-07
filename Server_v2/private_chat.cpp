#include "private_chat.h"

Private_chat::Private_chat()
{

}

//void Private_chat::sendMessage(std::string txt,std::string user_name)
//{
//    Message new_message(txt,user_name);
//    messages.push_back(new_message);
//}

//void Private_chat::setAccount(std::string acc)
//{
//    members.push_back(acc);
//}

std::string Private_chat::getName(std::string name)
{
    if(members[0] == name){
        return members[1];
    }
    return members[0];
}


