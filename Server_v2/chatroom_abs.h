#ifndef CHATROOM_ABS_H
#define CHATROOM_ABS_H

#include <string>
#include <vector>
#include <QMainWindow>
#include "date.h"
#include <message.h>
#include <account.h>

class ChatRoom_abs;
class Account;

class ChatRoom_abs
{
protected:
    std::vector <Message> messages;
    std::vector <std::string> members;
    std::vector <std::string> admins;
    std::string name;
public:
    ChatRoom_abs(){};
    ~ChatRoom_abs(){};
    virtual void sendMessage(std::string txt,std::string user_name);
    virtual void setName(std::string namein);
    virtual std::string getName(){};
    void setAdmin(std::string name);
    std::vector<std::string> getAdmin();
    virtual std::string getName(std::string acc){};
    std::vector<Message> getChats(){return this->messages;};
    void remove_room() ;
    virtual std::string getType(){};
    void setAccount(std::string accName) ;
};

#endif // CHATROOM_ABS_H
