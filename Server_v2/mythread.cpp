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
#include "chatroom.h"
#include "massage.h"

MyThread::MyThread(std::vector<Account*>& Accounts,std::vector<Chatroom*>& chatrooms,qintptr ID, QObject *parent) :
    QThread(parent)
{
    accounts = Accounts;
    chatrooms_th = chatrooms;
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
        //qDebug() << "log in";
        login(list1[1],list1[2]);
    }
    else
    {
        socket->write("salam cmd user");
        socket->flush();
        socket->waitForBytesWritten(-1);
    }

    // will write on server side window
//    qDebug() << socketDescriptor << " Data in: " << Data;

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

    if (check_valid_info(user ,email ,num))
    {
        new_acc->set_user_name(user);
        new_acc->set_email(email);
        new_acc->set_number(num);
        new_acc->set_password(pass);
        new_acc->set_Date_birthday(year, month, day);
        accounts.push_back(new_acc);
    }

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

              QString secess = "log in secessfuly";
              socket->write((secess+'\n').toUtf8());
              socket->flush();
              socket->waitForBytesWritten(30000);
              socket->waitForBytesWritten(-1);

              flag = 1;
              login_acc = accounts[i];
              account_run();

              break;
            }
            else
            {
                qDebug() << "your pass is wrong ";
                QString wrong_str = "your username or password is wrong!!!";
                socket->write(wrong_str.toUtf8(),wrong_str.toUtf8().size());
                socket->waitForBytesWritten(-1);
                flag = 1;
            }
        }
    }
    if(flag == 0)
    {
        qDebug() << "your username is wrong";
        socket->write("your username or password is wrong!!!");
        socket->waitForBytesWritten(-1);
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void MyThread::account_run()
{
    while (socket->waitForReadyRead(-1))
    {
        QByteArray loginok = socket->readAll();
        break;
    }

    updata_clinet_vector();
    readingdata();
}


void MyThread::readingdata()
{
    while(true)
    {
        QStringList list1;
        while (socket->waitForReadyRead(-1)) {
            QByteArray Data = socket->readAll();
            qDebug() << socketDescriptor << " Data in: " << Data;
            QString qData = QString(Data);
            list1 = qData.split(',');
            break;
        }
        qDebug() << list1;

        if(list1.isEmpty())
            break;

        if (list1[0] == "create_chatroom")
        {
            if(list1[1] == "private")
            {
                for(int i = 0; i < (int)accounts.size(); i++)
                {
                    if (list1[2] == accounts[i]->get_user_name())
                    {
                        Chatroom* newchat = new Private_chat(login_acc,accounts[i]);
                        newchat->set_type("private");
                        //newchat->set_subject(accounts[i]->get_user_name());
                        login_acc->chatrooms.push_back(newchat);

                        //newchat->set_subject(login_acc->get_user_name());
                        accounts[i]->chatrooms.push_back(newchat);
                        chatrooms_th.push_back(newchat);
                        break;
                    }
                }
            }
            else if (list1[1] == "group")
            {
                Chatroom* newchat;
                std::vector<Account*> list_membera;
                for (int j = 2; j < list1.length()-1 ; j++)
                {
                    for(int i = 0; i < (int)accounts.size(); i++)
                    {
                        if (list1[j] == accounts[i]->get_user_name())
                        {
                            list_membera.push_back(accounts[i]);
                            break;
                        }
                    }
                }
                newchat = new Group(list_membera);
                for (int j = 0; j < (int)list_membera.size() ; j++)
                {
                    list_membera[j]->chatrooms.push_back(newchat);
                }
                login_acc->chatrooms.push_back((newchat));
                newchat->add_admin(login_acc->get_user_name());
                newchat->set_type("group");
                newchat->set_subject(list1[list1.length()-1]);
                chatrooms_th.push_back(newchat);
            }
            else if(list1[1] == "channel") //channel
            {

                Chatroom* newchat;
                std::vector<Account*> list_membera;
                for (int j = 2; j < list1.length()-1 ; j++)
                {
                    for(int i = 0; i < (int)accounts.size(); i++)
                    {
                        if (list1[j] == accounts[i]->get_user_name())
                        {
                            list_membera.push_back(accounts[i]);
                            break;
                        }
                    }
                }
                newchat = new Channel(list_membera);
                for (int j = 0; j < (int)list_membera.size() ; j++)
                {
                    list_membera[j]->chatrooms.push_back(newchat);
                }
                login_acc->chatrooms.push_back((newchat));
                newchat->add_admin(login_acc->get_user_name());
                newchat->set_type("channel");
                newchat->set_subject(list1[list1.length()-1]);
                chatrooms_th.push_back(newchat);
            }
        }
        else if (list1[0] == "send_massage")
        {
            for (int i = 0; i < (int)login_acc->chatrooms.size(); i++)
            {
                if(list1[2] == login_acc->chatrooms[i]->get_subject())
                {
                    if (login_acc->chatrooms[i]->get_type() == "channel")
                    {
                        if(login_acc->chatrooms[i]->chek_admin(login_acc->get_user_name())){
                            Massage newmsg;
                            newmsg.set_text(list1[1]);
                            newmsg.set_sender(login_acc->get_user_name());
                            login_acc->chatrooms[i]->massages.push_back(newmsg);
                        }
                    }
                    else
                    {
                        Massage newmsg;
                        newmsg.set_text(list1[1]);
                        newmsg.set_sender(login_acc->get_user_name());
                        login_acc->chatrooms[i]->massages.push_back(newmsg);
                    }
                }
            }
        }
        else if (list1[0] == "select_chatroom") //show messages
        {
            int flag = 0;
            for (int i = 0; i < (int)login_acc->chatrooms.size(); i++)
            {
                if(list1[1] == login_acc->chatrooms[i]->get_subject())
                {
                    for (int j = 0; j < (int)login_acc->chatrooms[i]->massages.size(); j++)
                    {
                        socket->write(login_acc->chatrooms[i]->massages[j].get_sender().toUtf8());
                        socket->write(",");
                        socket->write(login_acc->chatrooms[i]->massages[j].get_text().toUtf8());
                        socket->write(",");
                        flag = 1;
                    }

                }
            }
            if (flag == 0)
            {
                socket->write("empty");
                socket->write(",");

                socket->waitForBytesWritten(-1);
            }
        }
        else if (list1[0] == "setting")//setting
        {
            if(check_valid_info(list1[1] ,list1[2], list1[3]))
            {
                login_acc->set_user_name(list1[1]);
                login_acc->set_email(list1[2]);
                login_acc->set_number(list1[3]);
                qDebug() << "changing complit";
            }
        }
        else if (list1[0] == "profile") {
            for (int i = 0; i < (int)login_acc->chatrooms.size(); i++)
            {
                if(list1[1] == login_acc->chatrooms[i]->get_subject())
                {
                    socket->write(login_acc->chatrooms[i]->get_type().toUtf8());
                    socket->write(",");
                    if(login_acc->chatrooms[i]->get_type() == "private")
                    {
                        QStringList name = login_acc->chatrooms[i]->get_subject().split(":");
                        QString usr;
                        if(name[0] == login_acc->get_user_name())
                        {
                             usr = name[1];
                        }
                        else
                        {
                            usr = name[1];
                        }
                        if (login_acc->chatrooms[i]->Members[0]->get_user_name() == usr)
                        {
                            socket->write(login_acc->chatrooms[i]->Members[0]->get_user_name().toUtf8());
                            socket->write(",");
                            socket->write(login_acc->chatrooms[i]->Members[0]->get_email().toUtf8());
                            socket->write(",");
                            socket->write(login_acc->chatrooms[i]->Members[0]->get_number().toUtf8());
                        }
                        else
                        {
                            socket->write(login_acc->chatrooms[i]->Members[1]->get_user_name().toUtf8());
                            socket->write(",");
                            socket->write(login_acc->chatrooms[i]->Members[1]->get_email().toUtf8());
                            socket->write(",");
                            socket->write(login_acc->chatrooms[i]->Members[1]->get_number().toUtf8());
                        }
                    }

                    else{
                        socket->write(login_acc->chatrooms[i]->get_subject().toUtf8());
                        socket->write(",");
                        for (int j = 0 ; j < (int)login_acc->chatrooms[i]->Members.size(); j++)
                        {
                            socket->write(login_acc->chatrooms[i]->Members[j]->get_user_name().toUtf8());
                            socket->write(",");
                        }
                    }
                    socket->waitForBytesWritten(-1);
                }
            }
        }
        else //show chatrooms
        {
            int flag = 0;

            for (int i = 0; i < (int)login_acc->chatrooms.size(); i++)
            {
                socket->write(login_acc->chatrooms[i]->get_subject().toUtf8());
                socket->write(",");     
                flag=1;
            }
            if (flag == 0)
            {
                socket->write("empety");
                socket->waitForBytesWritten(-1);
            }
        }

    }
}


/////////////////////////////////////////////////////////////////////
// send data from vector accounts to vector client

void MyThread::updata_clinet_vector()
{
    QString size = QString::number((int)accounts.size());
    QByteArray size_v = size.toUtf8();

    socket->write(size_v);
    socket->write(":");


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




bool MyThread::check_valid_info(QString usr ,QString email, QString number)
{
    int flag = 0;
    for (int i = 0; i < (int)accounts.size(); i++)
    {
        if (accounts[i]->get_user_name() == usr)
        {
            qDebug() << "your user name is wrong";
            flag =1;
        }
    }

    for (int i = 0; i < (int)accounts.size(); i++)
    {
        if (accounts[i]->get_user_name() == email)
        {
            qDebug() << "your user name is wrong";
            flag =1;
        }
    }

    for (int i = 0; i < (int)accounts.size(); i++)
    {
        if (accounts[i]->get_email() == email)
        {
            qDebug() << "your email is wrong";
            flag =1;
        }
    }

    for (int i = 0; i < (int)accounts.size(); i++)
    {
        if (accounts[i]->get_number() == number)
        {
            qDebug() << "your number is wrong";
            flag =1;
        }
    }
    return flag;
}
