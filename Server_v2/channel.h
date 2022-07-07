#ifndef CHANNEL_H
#define CHANNEL_H
#include "chatroom_abs.h"

class Channel : public ChatRoom_abs
{
public:
    Channel();
    std::string getName() override;
    std::string getType() override{return "channel";}
};

#endif // CHANNEL_H
