#include "profile.h"
#include "ui_profile.h"
#include <QListWidget>
Profile::Profile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Profile)
{
    ui->setupUi(this);

}

Profile::~Profile()
{
    delete ui;
}

void Profile::show_profile(QString type ,QString usr, QString email, QString num)
{
    if (type == "private")
    {
        ui->UserlistWidget->addItem(usr);
        ui->EmaillistWidget->addItem(email);
        ui->numberlistWidget->addItem(num);
    }
}
