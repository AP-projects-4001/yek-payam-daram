#include "groupchat.h"

GroupChat::GroupChat()
{

}

void GroupChat::setName(std::string namein)
{
    this->name = namein;
}

std::string GroupChat::getName()
{
    return  this->name;
}
