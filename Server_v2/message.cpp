#include "message.h"

Message::Message(std::string txt, std::string _sender)
{
    this->sender = _sender;
    this->text = txt;
}

void Message::setText(std::string txt)
{
    this->text = txt;
}
