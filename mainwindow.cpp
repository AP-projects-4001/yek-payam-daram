#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sign_in.h"
#include "log_in.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_signin_openwindow_Button_clicked()
{
    Sign_in* d = new Sign_in(this);
    d->show();
    connect(d,SIGNAL(recive_info(QString,QString,QString,QString,int,int,int)),this,SLOT(submit_acc(QString,QString,QString,QString,int,int,int)));
}

void MainWindow::submit_acc(QString nameinp, QString emailinp, QString phonenuminp, QString passinp, int year, int month, int day)
{
    Account new_acc;
    new_acc.set_user_name(nameinp);
    new_acc.set_email(emailinp);
    new_acc.set_number(phonenuminp);
    new_acc.set_password(passinp);
    new_acc.set_Date_birthday(year,month,day);
}




void MainWindow::on_Login_openwindow_Button_clicked()
{
    Log_in* d = new Log_in(this);
    d->show();
}

