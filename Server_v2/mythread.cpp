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
              socket->write("log in secessfuly");
              socket->flush();
              socket->waitForBytesWritten(-1);

              flag = 1;
              account_run(accounts[i]->get_ID_NUM());
              break;
            }
            else
            {
                qDebug() << "your pass is wrong ";
                socket->write("your pass is wrong!!!");
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

    socket->write("Welcome ");
    qDebug() << socketDescriptor;
    QByteArray us = accounts[selected]->get_user_name().toUtf8();
    socket->write(us);
    socket->waitForBytesWritten(-1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//file handling

//void MyThread::saving_data()
//{
//    qDebug() << "saving data ... ";
//    QFile ofile{"C:/cpp files/project/database.json"};
//    ofile.open(QIODevice::WriteOnly);
//    QJsonObject j;
//    QJsonArray b;
//    for (int i = 0; i<(int)accounts.size() ;i++ )
//    {
//        QJsonObject people;
//        people["User"] = accounts[i]->get_user_name();
//        people["Email"] = accounts[i]->get_email();
//        people["Number"] = accounts[i]->get_number();
//        people["Pass"] = accounts[i]->get_password();
//        people["year"] = accounts[i]->get_yDate();
//        people["month"] = accounts[i]->get_mDate();
//        people["day"] = accounts[i]->get_dDate();
//        b.append(people);

//    }
//    j["accounts"] = b;
//    QJsonDocument d(j);

//    ofile.write(d.toJson());
//    ofile.flush();
//    ofile.close();
//}

//void MyThread::loading_data()
//{
//    QFile ifile{"C:/cpp files/project/database.json"};
//    ifile.open(QIODevice::ReadOnly);
//    QByteArray b = ifile.readAll();
//    QJsonDocument d = QJsonDocument::fromJson(b);
//    QJsonObject s = d.object();


//    foreach(QJsonValue x, s["accounts"].toArray())
//    {
//        int i = 0;
//        Account* ipeople = new Account;
//        QJsonObject t = x.toObject();
//        ipeople->set_user_name(t["User"].toString());
//        ipeople->set_email(t["Email"].toString());
//        ipeople->set_number(t["Number"].toString());
//        ipeople->set_password(t["Pass"].toString());
//        ipeople->set_Date_birthday(t["year"].toInt(), t["month"].toInt(), t["day"].toInt());
//        accounts.push_back(ipeople);
//        i++;
//    }
//        for(int i = 0; i < (int)accounts.size(); i++)
//        {
//            qDebug() << accounts[i]->get_user_name();
//            qDebug() << accounts[i]->get_email();
//        }

//}



