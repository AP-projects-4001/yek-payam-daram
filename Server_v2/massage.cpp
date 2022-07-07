#include "massage.h"

Massage::Massage()
{

}

QString Massage::get_text()
{
    return text;
}

void Massage::set_text(QString text_inp)
{
    text = text_inp;
}

QString Massage::get_sender()
{
    return sender;
}

void Massage::set_sender(QString sender_inp)
{
    sender = sender_inp;
}
