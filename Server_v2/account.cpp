#include "account.h"
#include <string>
#include "chatroom.h"

Account::Account()
{
    ID_NUM = idgenerator;
    idgenerator++;
}

void Account::set_number(QString numberinp)
{
    number = numberinp;
}

QString Account::get_number()
{
    return number;
}

void Account::set_user_name(QString user_name_inp)
{
    user_name = user_name_inp;
}

QString Account::get_user_name()
{
    return user_name;
}

void Account::set_password(QString password_inp)
{
    password = password_inp;
}

QString Account::get_password()
{
    return password;
}

void Account::set_email(QString email_inp)
{
    email = email_inp;
}

QString Account::get_email()
{
    return email;
}

void Account::set_Date_birthday(int year,int month, int day)
{
    birthday.set_year(year);
    birthday.set_month(month);
    birthday.set_day(day);
}

int Account::get_yDate()
{
    return birthday.get_year();
}
int Account::get_mDate()
{
    return birthday.get_month();
}
int Account::get_dDate()
{
    return birthday.get_day();
}

int Account::get_ID_NUM()
{
    return ID_NUM;
}
