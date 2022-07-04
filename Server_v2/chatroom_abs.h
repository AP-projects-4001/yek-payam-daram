#ifndef CHATROOM_ABS_H
#define CHATROOM_ABS_H

#include <string>
#include <vector>
#include <message.h>
#include <account.h>

class Account;
class ChatRoom_abs
{
protected:
    std::vector <Message> messages;
    std::vector <Account> members;
    std::string name;
public:
    ChatRoom_abs()
    {

    }
    ~ChatRoom_abs(){};
    int sendMessage(std::string txt,std::string user_name) ;
    virtual void setName(std::string namein);
    void remove_room() ;
};

#endif // CHATROOM_ABS_H
