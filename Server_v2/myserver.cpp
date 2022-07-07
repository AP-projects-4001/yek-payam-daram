#include "myserver.h"
#include "ui_myserver.h"
#include "myserver.h"
#include "mythread.h"
#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <string>
#include <QDebug>

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{
}

void MyServer::startServer()
{
    int port = 1025;

    if(!this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening to port " << port << "...";
        loading_data();
    }
}

// This function is called by QTcpServer when a new connection is available.
void MyServer::incomingConnection(qintptr socketDescriptor)
{
    // We have a new connection
    qDebug() << socketDescriptor << " Connecting...";

    // Every new connection will be run in a newly created thread
    MyThread *thread = new MyThread(socketDescriptor, Accounts, ChatRooms, this);

    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    saving_data();
    thread->start();
    saving_data();
}

void MyServer::saving_data()
{
    qDebug() << "saving data ... ";
    QFile ofile{"database.json"};
    ofile.open(QIODevice::WriteOnly);
    QJsonObject j;
    QJsonArray b;
    for (int i = 0; i<(int)Accounts.size() ;i++ )
    {
        QJsonObject people;
        people["User"] = Accounts[i].get_user_name();
        people["Email"] = Accounts[i].get_email();
        people["Number"] = Accounts[i].get_number();
        people["Pass"] = Accounts[i].get_password();
        people["year"] = Accounts[i].get_yDate();
        people["month"] = Accounts[i].get_mDate();
        people["day"] = Accounts[i].get_dDate();
        b.append(people);

    }
    j["accounts"] = b;
    QJsonDocument d(j);

    ofile.write(d.toJson());
    ofile.flush();
    ofile.close();
}

void MyServer::loading_data()
{
    QFile ifile{"database.json"};
    ifile.open(QIODevice::ReadOnly);
    QByteArray b = ifile.readAll();
    QJsonDocument d = QJsonDocument::fromJson(b);
    QJsonObject s = d.object();


    foreach(QJsonValue x, s["accounts"].toArray())
    {
        int i = 0;
        Account ipeople;
        QJsonObject t = x.toObject();
        ipeople.set_user_name(t["User"].toString());
        ipeople.set_email(t["Email"].toString());
        ipeople.set_number(t["Number"].toString());
        ipeople.set_password(t["Pass"].toString());
        ipeople.set_Date_birthday(t["year"].toInt(), t["month"].toInt(), t["day"].toInt());
        Accounts.push_back(ipeople);
        i++;
    }
        for(int i = 0; i < (int)Accounts.size(); i++)
        {
            qDebug() << Accounts[i].get_user_name();
            qDebug() << Accounts[i].get_email();
        }

}

