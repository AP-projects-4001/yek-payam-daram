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
    Date massage_date;
    TimeKhodam massage_time;
    QString sender;


};

#endif // MASSAGE_H
