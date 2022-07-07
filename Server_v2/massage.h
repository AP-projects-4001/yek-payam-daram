#ifndef MASSAGE_H
#define MASSAGE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "date.h"
#include "timekhodam.h"

class Massage
{
public:
    Massage();

private:
    QString text;
    QString sender;

    Date massage_date;
    TimeKhodam massage_time;

public:
    QString get_text();
    void set_text(QString text_inp);

    QString get_sender();
    void set_sender(QString sender_inp);
};

#endif // MASSAGE_H
