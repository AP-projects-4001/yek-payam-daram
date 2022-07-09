#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>


class Message
{
    std:: string text;
    std:: string sender;
public:
    Message(std::string txt, std::string _sender);
    void setText(std::string txt);
    std::string getMessage(){return this->sender + ',' + this->text;};

    void set_sender(std::string sender_inp);
};

#endif // MESSAGE_H
