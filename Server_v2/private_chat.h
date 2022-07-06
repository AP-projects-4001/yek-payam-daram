#ifndef PRIVATE_CHAT_H
#define PRIVATE_CHAT_H

#include "chatroom_abs.h"

class Private_chat : public ChatRoom_abs
{
    std::string name;
public:
    Private_chat();
    void sendMessage(std::string txt,std::string user_name) override;
    void setName(std::string namein) override;
    std::string getType() override {return "Private";};
};

#endif // PRIVATE_CHAT_H
