#include "usersettings.h"
#include "ui_usersettings.h"

UserSettings::UserSettings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserSettings)
{
    ui->setupUi(this);
}

UserSettings::~UserSettings()
{
    delete ui;
}

void UserSettings::show_info(QString usr, QString email, QString num)
{
    ui->UserNamelineEdit->setText(usr);
    ui->EmaillineEdit->setText(email);
    ui->PhonenumberlineEdit->setText(num);
}

void UserSettings::on_pushButton_clicked()
{
    emit send_change_info(ui->UserNamelineEdit->text(), ui->EmaillineEdit->text(), ui->PhonenumberlineEdit->text());
}

