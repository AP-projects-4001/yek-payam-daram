#ifndef PRIVATE_CHAT_H
#define PRIVATE_CHAT_H

#include "chatroom_abs.h"

class Private_chat : public ChatRoom_abs
{

public:
    Private_chat();
    void sendMessage(std::string txt,std::string user_name) override;
    std::vector<Account> getAccounts();
    void setAccount(Account acc) override;
    std::string getType() override {return "Private";};
    std::string getName(std::string name) override;
};

#endif // PRIVATE_CHAT_H