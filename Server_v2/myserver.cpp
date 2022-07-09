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
#include <vector>
#include "massage.h"

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
        loading_chatroom();
        saving_chatrooms();
        saving_data();
    }
}

// This function is called by QTcpServer when a new connection is available.
void MyServer::incomingConnection(qintptr socketDescriptor)
{
    // We have a new connection
    qDebug() << socketDescriptor << " Connecting...";

    // Every new connection will be run in a newly created thread
    MyThread *thread = new MyThread(socketDescriptor, Accounts, ChatRooms, this);
    saving_chatrooms();
    saving_data();
    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();


}

void MyServer::saving_data()
{
    qDebug() << "saving data ... ";
    QFile ofile{"C:/cpp files/project/database.json"};
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
    QFile ifile{"C:/cpp files/project/database.json"};
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


void MyServer::saving_chatrooms()
{
    qDebug() << "saving chatroom... ";
    QFile ofile{"C:/cpp files/project/chatroom.json"};
    ofile.open(QIODevice::WriteOnly);

    QJsonArray chatrooms;
    QJsonObject j;
    for (int i = 0; i < (int)ChatRooms.size(); i++)
    {
        QJsonObject chatroom;
        QString type = QString::fromStdString(ChatRooms[i]->getType());
        chatroom["type"] = type;
        QString name = QString::fromStdString(ChatRooms[i]->getName());
        chatroom["name"] = name;

        std::vector<std::string> members = ChatRooms[i]->getMembers();
        QJsonArray chatroom_array;
        for (int j = 0; j < (int)members.size(); j++)
        {
            QJsonObject member;
            QString user= QString::fromStdString(members[j]);
            member["user name"] = user;
            chatroom_array.append(member);
        }
        chatroom["members"] = chatroom_array;


        std::vector<Message> messages = ChatRooms[i]->getChats();
        QJsonArray chats_array;
        for (int j = 0; j < (int)messages.size() ; j++)
        {
            QJsonObject message;
            QString msg = QString::fromStdString(messages[j].getMessage());
            QStringList list_msg = msg.split(",");
            message["sender"] = list_msg[0];
            message["text"] = list_msg[1];
            chats_array.append(message);
        }
        chatroom["messages"] = chats_array;

        std::vector<std::string> admins = ChatRooms[i]->getAdmin();
        QJsonArray admins_array;
        for (int j = 0; j < (int)admins.size() ; j++)
        {
            QJsonObject admin;
            QString adm = QString::fromStdString(admins[j]);
            admin["admin"] = adm;
        }
        chatroom["admins"] = admins_array;
        chatrooms.append(chatroom);
    }
    j["chatrooms"] = chatrooms;
    QJsonDocument d(j);
    ofile.write(d.toJson());
    ofile.flush();
    ofile.close();
}

void MyServer::loading_chatroom()
{
    QFile ifile{"C:/cpp files/project/chatroom.json"};
    ifile.open(QIODevice::ReadOnly);
    QByteArray b = ifile.readAll();
    QJsonDocument d = QJsonDocument::fromJson(b);
    QJsonObject s = d.object();

    foreach(QJsonValue x, s["chatrooms"].toArray())
    {
        QJsonObject chatroom = x.toObject();
        QString type = chatroom["type"].toString();
        ChatRoom_abs* newchatroom ;
        if (type == "private")
        {
            newchatroom= new Private_chat;

            //name
            newchatroom->setName(chatroom["name"].toString().toStdString());

            //members
            foreach(QJsonValue t, chatroom["members"].toArray())
            {
                QJsonObject member = t.toObject();
                newchatroom->setAccount(member["user name"].toString().toStdString());
            }

            //message
            foreach(QJsonValue t, chatroom["messages"].toArray())
            {
                QJsonObject msg = t.toObject();
                newchatroom->sendMessage(msg["text"].toString().toStdString(),msg["sender"].toString().toStdString());
            }

        }

        else if(type == "group")
        {
            newchatroom = new GroupChat;

            //name
            newchatroom->setName(chatroom["name"].toString().toStdString());

            //members
            foreach(QJsonValue t, chatroom["members"].toArray())
            {
                QJsonObject member = t.toObject();
                newchatroom->setAccount(member["user name"].toString().toStdString());
            }

            //message
            foreach(QJsonValue t, chatroom["messages"].toArray())
            {
                QJsonObject msg = t.toObject();
                newchatroom->sendMessage(msg["text"].toString().toStdString(),msg["sender"].toString().toStdString());
            }

        }

        else
        {
            newchatroom = new Channel;
            //name
            newchatroom->setName(chatroom["name"].toString().toStdString());

            //members
            foreach(QJsonValue t, chatroom["members"].toArray())
            {
                QJsonObject member = t.toObject();
                newchatroom->setAccount(member["user name"].toString().toStdString());
            }

            //message
            foreach(QJsonValue t, chatroom["messages"].toArray())
            {
                QJsonObject msg = t.toObject();
                newchatroom->sendMessage(msg["text"].toString().toStdString(),msg["sender"].toString().toStdString());
            }

        }
        ChatRooms.push_back(newchatroom);

    }
}
