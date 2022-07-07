#ifndef CHATROOM_H
#define CHATROOM_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <vector>
#include "massage.h"

class Account;

class Chatroom
{
public:
    Chatroom();
private:
    QString subject;
    QString type_of_chatroom;

protected:
    std::vector<QString> admins;

public:
    std::vector<Account*> Members;
    std::vector<Massage> massages;


public:
    virtual void edit_chatroom()= 0;
    virtual void remove_chatroom()= 0;

    void add_admin(QString admin_inp);

    QString get_subject();
    void set_subject(QString subject_inp);

    void set_type(QString type_chat);
    QString get_type();

    //for chek user is admin
    bool chek_admin(QString user);

};

class Private_chat : public Chatroom
{
public:
    Private_chat(Account* member1, Account* member2);
    void edit_chatroom();
    void remove_chatroom();
};

////////////////////////////////////////////////////////////////////////////////////////////////

class Group : public Chatroom
{
private:
    QString user_admin;

public:
    Group(std::vector<Account *> members);
    void edit_chatroom();
    void remove_chatroom();
    void set_admin(QString admin_inp);
};

////////////////////////////////////////////////////////////////////////////////////////////////

class Channel : public Chatroom
{
public:

    Channel(std::vector<Account *> members);
    void edit_chatroom();
    void remove_chatroom();
    void set_admin(QString admin_inp);


};

#endif // CHATROOM_H
