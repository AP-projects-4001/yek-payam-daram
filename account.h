#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QMainWindow>

#include <vector>
#include "date.h"

class Account
{
private:
    QString number;
    QString user_name;
    QString password;
    QString email;
    Date birthday;


public:
    Account();
    void set_number(QString numberinp);
    QString get_number();
    void set_user_name(QString user_name_inp);
    QString get_user_name();
    void set_password(QString password_inp);
    QString get_password();
    void set_email(QString email_inp);
    QString get_email();
    void set_Date_birthday(int year,int month,int day);
    int get_yDate();
    int get_mDate();
    int get_dDate();

public:
    std::vector<QString> frend;
};

#endif // ACCOUNT_H
