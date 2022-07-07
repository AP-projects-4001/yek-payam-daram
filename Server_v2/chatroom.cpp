#include "chatroom.h"
#include "account.h"

Chatroom::Chatroom()
{

}

void Chatroom::add_admin(QString admin_inp)
{
    admins.push_back(admin_inp);
}

QString Chatroom::get_subject()
{
    return subject;
}

void Chatroom::set_subject(QString subject_inp)
{
    subject = subject_inp;
}

void Chatroom::set_type(QString type_chat)
{
    type_of_chatroom = type_chat;
}

QString Chatroom::get_type()
{
    return type_of_chatroom;
}

bool Chatroom::chek_admin(QString user)
{
    for (int i = 0; i < (int)admins.size(); i++)
    {
        if ( admins[i] == user)
            return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////
//Private_chat functions

Private_chat::Private_chat(Account* member1, Account* member2)
{
    Members.push_back(member1);
    Members.push_back(member2);
    set_subject(member1->get_user_name()+":"+member2->get_user_name());
}

void Private_chat::edit_chatroom()
{

}

void Private_chat::remove_chatroom()
{

}

///////////////////////////////////////////////////////////////////////////////////////////
//group functions
Group::Group(std::vector<Account *> members)
{

    for (int i = 0; i < (int)members.size(); i++)
    {
        Members.push_back(members[i]);
    }

}

void Group::edit_chatroom()
{

}

void Group::remove_chatroom()
{

}

void Group::set_admin(QString admin_inp)
{
    add_admin(admin_inp);
}

////////////////////////////////////////////////////////////////////////////////////////////////
//channel functions

Channel::Channel(std::vector<Account *> members)
{
    for (int i = 0; i < (int)members.size(); i++)
    {
        Members.push_back(members[i]);
    }
}

void Channel::edit_chatroom()
{

}

void Channel::remove_chatroom()
{

}

void Channel::set_admin(QString admin_inp)
{
    add_admin(admin_inp);
}

