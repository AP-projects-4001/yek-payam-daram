#ifndef GROUPCHAT_H
#define GROUPCHAT_H
#include "chatroom_abs.h"

class GroupChat : public ChatRoom_abs
{
public:
    GroupChat();
    void setName(std::string namein) override;
    std::string getName() override;
    std::string getType() override{return "group";}
};

#endif // GROUPCHAT_H
