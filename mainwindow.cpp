#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sign_in.h"
#include "log_in.h"
#include <QByteArray>
#include <string>


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

//sign in function

void MainWindow::on_signin_openwindow_Button_clicked()
{
    Sign_in* d = new Sign_in(this);
    d->show();
    clientsocket = new QTcpSocket(this);

    connect(d,SIGNAL(recive_info(QString,QString,QString,QString,int,int,int)),this,SLOT(submit_acc(QString,QString,QString,QString,int,int,int)));

    }

void MainWindow::submit_acc(QString nameinp, QString emailinp, QString phonenuminp, QString passinp, int year, int month, int day)
{
    //clientsocket = new QTcpSocket(this);
    new_acc = new Account;
    new_acc->set_user_name(nameinp);
    new_acc->set_email(emailinp);
    new_acc->set_number(phonenuminp);
    new_acc->set_password(passinp);
    new_acc->set_Date_birthday(year,month,day);
    Accounts.push_back(new_acc);

    clientsocket->connectToHost("127.0.0.1", 1025);

    connect(clientsocket,SIGNAL(connected()),this, SLOT(connecttoserver()));

    connect(clientsocket,SIGNAL(bytesWritten(qint64)),this,SLOT(writingdata()));

    connect(clientsocket,SIGNAL(readyRead()),this,SLOT(readingdata()));

    connect(clientsocket,SIGNAL(disconnected()),this,SLOT(dissconnect()));


}

void MainWindow::readingdata()
{
    QByteArray data =clientsocket->readAll();
    qDebug() << data;
    qDebug() << "reading secssusfuly";
}

void MainWindow::writingdata()
{

    qDebug() << "writing data ... ";
}

void MainWindow::connecttoserver()
{
    qDebug() << "connected.";
    clientsocket->write("signin");
    clientsocket->write(",");
    std::string ba = Accounts[Accounts.size()-1]->get_user_name().toStdString();
    const char *c_str1 = ba.data();
    clientsocket->write(c_str1);
    clientsocket->write(",");

        std::string ba1 = Accounts[Accounts.size()-1]->get_email().toStdString();
        const char *c_str2 = ba1.data();
        clientsocket->write(c_str2);
        clientsocket->write(",");

        std::string ba2 = Accounts[Accounts.size()-1]->get_number().toStdString();
        const char *c_str3 = ba2.data();
        clientsocket->write(c_str3);
        clientsocket->write(",");

        std::string ba3 = Accounts[Accounts.size()-1]->get_password().toStdString();
        const char *c_str4 = ba3.data();
        clientsocket->write(c_str4);
        clientsocket->write(",");

    QByteArray qbaint1;
    qbaint1.setNum(new_acc->get_yDate());
    clientsocket->write(qbaint1);
    clientsocket->write(",");
    QByteArray qbaint2 ;
    qbaint2.setNum(new_acc->get_mDate());
    clientsocket->write(qbaint2);
    clientsocket->write(",");
    QByteArray qbaint3 ;
    qbaint3.setNum(new_acc->get_dDate());
    clientsocket->write(qbaint3);


}

void MainWindow::dissconnect()
{
    qDebug() << "connection lost!";
}


///////////////////////////////////////////////////////////////

//log in function

void MainWindow::on_Login_openwindow_Button_clicked()
{
    d = new Log_in(this);
    d->show();
    clientsocket = new QTcpSocket(this);
    connect(d,SIGNAL(login_info(QString,QString)),this,SLOT(login_acc(QString,QString)));

}

void MainWindow::login_acc(QString user_inp, QString pass)
{
    clientsocket->connectToHost("127.0.0.1", 1025);

//    while(!clientsocket->waitForReadyRead(-1))
//        qDebug() << "data recive" << clientsocket->readAll();
    clientsocket->write("login");
    clientsocket->write(",");
    QByteArray us = user_inp.toUtf8();
    clientsocket->write(us);
    clientsocket->write(",");
    QByteArray pa = pass.toUtf8();
    clientsocket->write(pa);
    clientsocket->waitForBytesWritten(-1);
    qDebug() << "massege sent";
    while(clientsocket->waitForReadyRead(-1))
    {

        QByteArray datain = clientsocket->readAll();
        qDebug() << "data recive" << datain;
        d->login_status((QString)datain);
        if (datain == "log in secessfuly")
        {
            delete d;
            mainpagewindow = new MainPage(this);
            mainpagewindow->show();

        }
        break;
    }
    while(clientsocket->waitForReadyRead(-1))
    {
        QByteArray datain = clientsocket->readAll();
        mainpagewindow->load_chatrooms((QString)datain);
        break;
    }
}



