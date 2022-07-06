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
    std::string type;
public:
    ChatRoom_abs(){};
    ~ChatRoom_abs(){};
    virtual void sendMessage(std::string txt,std::string user_name) {} ;
    virtual void setName(std::string namein){};
    virtual std::string getName(){};
    virtual std::string getName(std::string acc){};
    void remove_room() ;
    virtual std::string getType(){};
    virtual void setAccount(Account acc) {};            //private chat
};

#endif // CHATROOM_ABS_H
