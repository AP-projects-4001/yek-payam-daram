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

MyThread::MyThread(qintptr ID , std::vector<Account>& accs, std::vector<ChatRoom_abs*>& chats ,QObject *parent ) :
    QThread(parent) ,accounts(accs),chats(chats)
{
    this->socketDescriptor = ID;


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
    else
    {
        qDebug() << list1[0] << list1[1] << list1[2];
        qDebug() << "log in";
        login(list1[1],list1[2]);
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
//    new_acc = new Account;
//    new_acc->set_user_name(user);
//    new_acc->set_email(email);
//    new_acc->set_number(num);
//    new_acc->set_password(pass);
//    new_acc->set_Date_birthday(year, month, day);
//    accounts.push_back(new_acc);
    Account new_acc;
    new_acc.set_user_name(user);
    new_acc.set_email(email);
    new_acc.set_number(num);
    new_acc.set_password(pass);
    new_acc.set_Date_birthday(year,month,day);
    accounts.push_back(new_acc);


}

//log in function

void MyThread::login(QString user, QString pass)
{
    int flag = 0;
    for (int i = 0; i < (int)accounts.size(); i++)
    {
        if (user == accounts[i].get_user_name())
        {
            if(pass == accounts[i].get_password())
            {
              qDebug() << "log in secessfuly ";
              socket->write("log in secessfuly");
              socket->waitForBytesWritten(-1);
              flag = 1;
              acc_index = i;
              myAccount();
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

//file handling


void MyThread::myAccount()
{
    while (true) {
        std::string info = getInfo();
        std::vector<std::string> infos = split(info,',');
        if(infos[0] == "create_chatRoom"){         //case 1 (adding a chat_room)
            create_chatRoom(infos);
        }
        else if (infos[0] == "send_message"){

        }
    }
}

int MyThread::find_room(std::string roomName)
{
    for(unsigned long int i = 0; i < chats.size(); i++){
        if(chats[i]->getType() == "Private"){
           if(roomName ==  chats[i]->getName(accounts[acc_index].get_user_name().toStdString()))
               return i;
        }
        else{
            if(roomName == chats[i]->getName())
                return i;
        }
    }
}

void MyThread::create_chatRoom(std::vector<std::string> infos)
{
    if(infos[1] == "private"){
        for(unsigned long int i = 0; i < accounts.size(); i++){
            if(accounts[i].get_user_name().toStdString() == infos[2]){
                ChatRoom_abs* chat = new Private_chat;
                chat->setAccount(accounts[i]);
                chat->setAccount(accounts[acc_index]);
                chats.push_back(chat);
                return;
            }
        }
        //if username is invalid???
    }
    else if(infos[0] == "group"){

    }
    else {

    }
}

void MyThread::show_chatRooms()
{
    std::string res;
    for(unsigned long int i = 0; i < chats.size(); i++){
        if(chats[i]->getType() == "Private"){
            res += chats[i]->getName(accounts[acc_index].get_user_name().toStdString());
            if(i < chats.size() - 1)
                res += ',';
        }
        else{
            res += chats[i]->getName();
            if(i < chats.size() - 1)
                res += ',';
        }
    }
    sendInfo(res);
}

void MyThread::select_chatRoom(std::string roomName)
{
    int index = find_room(roomName);
    std::string res;
    std::vector<Message> texts = chats[index]->getChats();
    for(unsigned long int i = 0; i < texts.size(); i++){
        res += texts[i].getMessage();
        if(i < texts.size() - 1){
            res += ',';
        }
    }
    sendInfo(res);
}

std::string MyThread::getInfo()
{
    QByteArray info;
    while(socket->waitForReadyRead(-1)){
        info = socket->readAll();
    }
    std::string str_info = info.toStdString();

    return str_info;
}

std::vector<std::string> MyThread::split(std::string str, char separator)
{
    std::vector<std::string>res;
    std::istringstream string(str);
    std::string s;
    while (std::getline(string,s,separator)) {
        res.push_back(s);
    }
    return res;
}

