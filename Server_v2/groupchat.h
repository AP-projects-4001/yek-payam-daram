#ifndef GROUPCHAT_H
#define GROUPCHAT_H
#include "chatroom_abs.h"

class GroupChat : public ChatRoom_abs
{
public:
    GroupChat();
    void setName(std::string namein) override;
    std::string getName() override;
};

#endif // GROUPCHAT_H
