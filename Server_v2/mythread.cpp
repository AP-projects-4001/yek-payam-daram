#include "mythread.h"
#include "myserver.h"
#include <QFile>
#include <fstream>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <string>
#include <QDebug>
#include <QByteArray>

MyThread::MyThread(std::vector<Account*>& Accounts,qintptr ID, QObject *parent) :
    QThread(parent)
{
    accounts = Accounts;
    this->socketDescriptor = ID;

    //loading_data();
}

void MyThread::run()
{
    // thread starts here
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    // set the ID
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    exec();
}




////////////////////////////////////////////////////////////////////////////////////

void MyThread::readyRead()
{
    // get the information
    QByteArray Data = socket->readAll();

    QString qData = QString(Data);

    QStringList list1 = qData.split(',');



    if (list1[0] == "signin")
    {
        qDebug() << list1[1] << list1[2] << list1[3] << list1[4];
        qDebug() << "sign up";
        signin(list1[1],list1[2],list1[3],list1[4],list1[5].toInt(),list1[6].toInt(),list1[7].toInt());
    }
    else if (list1[0] == "login")
    {
        qDebug() << list1[0] << list1[1] << list1[2];
        qDebug() << "log in";
        login(list1[1],list1[2]);
    }
    else
    {
        socket->write("salam cmd user");
        socket->flush();
        socket->waitForBytesWritten(-1);
    }

    // will write on server side window
    qDebug() << socketDescriptor << " Data in: " << Data;

    //socket->write(Data);
}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";


    socket->deleteLater();
    exit(0);
}

/////////////////////////////////////////////////////////////////////////////

//sign up function

void MyThread::signin(QString user, QString email, QString num, QString pass, int year, int month, int day)
{
    new_acc = new Account;
    new_acc->set_user_name(user);
    new_acc->set_email(email);
    new_acc->set_number(num);
    new_acc->set_password(pass);
    new_acc->set_Date_birthday(year, month, day);
    accounts.push_back(new_acc);
    //saving_data();

}

////////////////////////////////////////////////////////////////////////////////
//log in function

void MyThread::login(QString user, QString pass)
{
    int flag = 0;
    for (int i = 0; i < (int)accounts.size(); i++)
    {
        if (user == accounts[i]->get_user_name())
        {
            if(pass == accounts[i]->get_password())
            {
              qDebug() << "log in secessfuly ";
              QString secessfuly_str = "log in secessfuly";
              QByteArray secessfuly_byte = secessfuly_str.toUtf8();
              socket->write(secessfuly_byte, secessfuly_byte.size());
              //socket->flush();
              socket->waitForBytesWritten(-1);


              flag = 1;
              account_run(accounts[i]->get_ID_NUM());
              break;
            }
            else
            {
                qDebug() << "your pass is wrong ";
                QString wrong_str = "your pass is wrong!!!";
                socket->write(wrong_str.toUtf8(),wrong_str.toUtf8().size());
                socket->waitForBytesWritten(-1);
                flag = 1;
            }
        }
    }
    if(flag == 0)
    {
        qDebug() << "your username is wrong";
        socket->write("your username is wrong");
        socket->waitForBytesWritten(-1);
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void MyThread::account_run(int ID_num_inp)
{
    int selected = ID_num_inp;
    updata_clinet_vector();
//    socket->write("Welcome ");
//    qDebug() << socketDescriptor;
//    QByteArray us = accounts[selected]->get_user_name().toUtf8();
//    socket->write(us);
//    socket->waitForBytesWritten(-1);
}

void MyThread::updata_clinet_vector()
{
    QString size = QString::number((int)accounts.size());
    QByteArray size_v = size.toUtf8();
    socket->write(size_v);
    socket->write(":");
    socket->waitForBytesWritten(-1);

    for (int i = 0; i<(int)accounts.size() ;i++ )
    {
        QByteArray user = accounts[i]->get_user_name().toUtf8();
        socket->write(user);
        socket->write(",");
        QByteArray email = accounts[i]->get_email().toUtf8();
        socket->write(email);
        socket->write(",");
        QByteArray number = accounts[i]->get_number().toUtf8();
        socket->write(number);
        socket->write(",");
        QString size_f = QString::number((int)accounts[i]->frend.size());
        QByteArray size_friend = size_f.toUtf8();
        socket->write(size_friend);

        for (int j = 0; j < (int)accounts[i]->frend.size(); j++)
        {
            socket->write(",");
            socket->write(accounts[i]->frend[j].toUtf8());
        }
        socket->write("/");
    }
    socket->waitForBytesWritten(-1);
}



