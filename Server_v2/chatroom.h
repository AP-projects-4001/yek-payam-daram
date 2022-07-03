#ifndef CHATROOM_H
#define CHATROOM_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <vector>
#include "massage.h"
#include "account.h"

class Chatroom
{
public:
    Chatroom();
private:
    QString subject;

//    std::vector<Account> Members;

//    std::vector<Massage> massages;

public:
    virtual void create_chatroom()= 0;
    virtual void edit_chatroom()= 0;
    virtual void remove_chatroom()= 0;

};


#endif // CHATROOM_H
