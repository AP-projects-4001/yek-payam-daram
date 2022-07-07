#ifndef PRIVATE_CHAT_H
#define PRIVATE_CHAT_H

#include "chatroom_abs.h"

class Private_chat : public ChatRoom_abs
{

public:
    Private_chat();
    std::vector<Account> getAccounts();
    std::string getType() override {return "Private";};
    std::string getName(std::string name) override;
};

#endif // PRIVATE_CHAT_H
