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


void MainWindow::on_signin_openwindow_Button_clicked()
{
    Sign_in* d = new Sign_in(this);
    d->show();
    clientsocket = new QTcpSocket();
    clientsocket->connectToHost("127.0.0.1", 1025);
    qDebug() << "connecting...";


    connect(d,SIGNAL(recive_info(QString,QString,QString,QString,int,int,int)),this,SLOT(submit_acc(QString,QString,QString,QString,int,int,int)));

    connect(clientsocket,SIGNAL(connected()),this, SLOT(connecttoserver()));


    connect(clientsocket,SIGNAL(bytesWritten(qint64)),this,SLOT(writingdata()));
    connect(clientsocket,SIGNAL(readyRead()),this,SLOT(readingdata()));
    connect(clientsocket,SIGNAL(disconnected()),this,SLOT(dissconnect()));
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
//    QByteArray *br = new QByteArray(new_acc->get_user_name().toUtf8());
      clientsocket->write("salam farmande");
      std::string ba = new_acc->get_user_name().toStdString();
//      const char *c_str2 = ba.data();
      QByteArray ab = new_acc->get_email().toUtf8();
      clientsocket->write(ab);
//    QByteArray br1 = new_acc->get_email().toUtf8();
//    clientsocket->write(br1);
//    QByteArray br2 = new_acc->get_number().toUtf8();
//    clientsocket->write(br2);
//    QByteArray br3 = new_acc->get_password().toUtf8();
//    clientsocket->write(br3);
//    QByteArray qbaint1;
//    qbaint1.setNum(new_acc->get_yDate());
//    clientsocket->write(qbaint1);
//    QByteArray qbaint2 ;
//    qbaint2.setNum(new_acc->get_mDate());
//    clientsocket->write(qbaint2);
//    QByteArray qbaint3 ;
//    qbaint3.setNum(new_acc->get_dDate());
//    clientsocket->write(qbaint3);
}

void MainWindow::dissconnect()
{
    qDebug() << "connection lost!";
}

void MainWindow::on_Login_openwindow_Button_clicked()
{
    Log_in* d = new Log_in(this);
    d->show();
}



