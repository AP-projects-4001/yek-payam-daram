#include "mythread.h"
#include "myserver.h"
#include "groupchat.h"
#include "channel.h"
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
    Account new_acc;
    if(check_valid_info(user,email,num) == 0){
        new_acc.set_user_name(user);
        new_acc.set_email(email);
        new_acc.set_number(num);
        new_acc.set_password(pass);
        new_acc.set_Date_birthday(year,month,day);
        accounts.push_back(new_acc);
    }

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
              QString secess = "log in secessfuly";
              socket->write((secess+'\n').toUtf8());
              socket->flush();
              socket->waitForBytesWritten(-1);
              flag = 1;
              acc_index = i;
              myAccount();
            }
            else
            {
                qDebug() << "your pass is wrong ";
                socket->write("your username or password is wrong!!!");
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


void MyThread::myAccount()
{

    getInfo();
    //update vector accounts in client app
    updata_clinet_vector();

    while (true) {
        std::string info = getInfo();
        std::vector<std::string> infos = split(info,',');
        if(infos[0] == "create_chatroom"){         //case 1 (adding a chat_room)
            create_chatRoom(infos);
        }
        else if (infos[0] == "send_massage"){
            int index = find_room(infos[2]);
            if(chats[index]->getType() == "channel"){
                std::vector<std::string> admins = chats[index]->getAdmin();
                for(int i = 0;i < (int)admins.size(); i++){
                    if(accounts[acc_index].get_user_name().toStdString() == admins[i]){
                        chats[index]->sendMessage(infos[1],accounts[acc_index].get_user_name().toStdString());
                    }
                }
            }

            else{chats[index]->sendMessage(infos[1],accounts[acc_index].get_user_name().toStdString());}
        }
        else if(infos[0] == "show chatrooms"){
            show_chatRooms();
        }
        else if(infos[0] == "select_chatroom"){
            select_chatRoom(infos[1]);
        }
        else if (infos[0] == "setting")//setting
        {
            accounts[acc_index].set_user_name(QString::fromStdString(infos[1]));
            accounts[acc_index].set_email(QString::fromStdString(infos[2]));
            accounts[acc_index].set_number(QString::fromStdString(infos[3]));
            qDebug() << "changing complit";
        }
        else if (infos[0] == "profile") {
            profile(infos[1]);
        }
        else if (infos[0] == "exit") {
            break;
        }
        else
        {
            qDebug() << QString::fromStdString(infos[0]);
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
    return -1;      //there is no Chat
}

void MyThread::profile(std::string name)
{
    int index = find_room(name);
    if(chats[index]->getType() == "private"){
        std::string res = "private";
          res += ',';res += accounts[acc_index].get_user_name().toStdString();res+= ',';res += accounts[acc_index].get_email().toStdString();
          res += ',';res+= accounts[acc_index].get_number().toStdString();
          sendInfo(res);
          return;
    }
    else{
        std::string res = chats[index]->getType();
        res += ',';
        res += chats[index]->getName();
        res += ',';
        std::vector<std::string> members = chats[index]->getMembers();
        for(unsigned long int i = 0; i < members.size(); i++){
            res += members[i];
            if(i < members.size() - 1)
                res += ',';
        }
        sendInfo(res);
    }
}

int MyThread::find_acc(std::string acc_name)
{
    for(unsigned long int i = 0; i < chats.size(); i++){
        if(accounts[i].get_user_name().toStdString() == acc_name)
            return i;
    }
}

void MyThread::settings(std::string user, std::string mail, std::string number)
{
    accounts[acc_index].set_user_name(QString::fromStdString(user));
    accounts[acc_index].set_email(QString::fromStdString(mail));
    accounts[acc_index].set_number(QString::fromStdString(number));
    sendInfo();
}

void MyThread::create_chatRoom(std::vector<std::string> infos)
{
    if(infos[1] == "private"){
        for(unsigned long int i = 0; i < accounts.size(); i++){
            if(accounts[i].get_user_name().toStdString() == infos[2]){
                ChatRoom_abs* chat = new Private_chat;
                chat->setAccount(accounts[i].get_user_name().toStdString());
                chat->setAccount(accounts[acc_index].get_user_name().toStdString());
                chats.push_back(chat);
                //sendInfo("done");
                return;
            }
        }
        //if username is invalid???
    }
    else if(infos[1] == "group"){
        ChatRoom_abs* chat = new GroupChat;
        for( unsigned long i = 2; i < infos.size() - 1; i++){
            chat->setAccount(accounts[find_acc(infos[i])].get_user_name().toStdString());
        }
        chat->setAccount(accounts[acc_index].get_user_name().toStdString());
        chat->setName(infos[infos.size()-1]);
        chats.push_back(chat);
        return;
    }
    else {
        ChatRoom_abs* chat = new Channel;
        for( unsigned long i = 2; i < infos.size() - 1; i++){
            chat->setAccount(accounts[find_acc(infos[i])].get_user_name().toStdString());
        }
        chat->setAccount(accounts[acc_index].get_user_name().toStdString());
        chat->setName(infos[infos.size()-1]);
        chat->setAdmin(accounts[acc_index].get_user_name().toStdString());
        chats.push_back(chat);
        return;
    }
}

void MyThread::show_chatRooms()
{
    std::string res;
    if (chats.size() == 0){
        res = "empty";
    }
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
    if(texts.size() == 0){
        res = "empty";
    }
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
        qDebug() << socketDescriptor << " Data in: " << info;
        break;
    }
    std::string str_info = info.toStdString();

    return str_info;
}

void MyThread::sendInfo(std::string str)
{
    QByteArray res (str.c_str(),str.length());
    socket->write(res);
    socket->waitForBytesWritten(-1);
}

void MyThread::sendInfo()
{
    socket->write("done");
    socket->waitForBytesWritten(-1);
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

void MyThread::updata_clinet_vector()
{
    QString size = QString::number((int)accounts.size());
    QByteArray size_v = size.toUtf8();
    socket->write(size_v);
    socket->write(":");


    for (int i = 0; i<(int)accounts.size() ;i++ )
    {
        QByteArray user = accounts[i].get_user_name().toUtf8();
        socket->write(user);
        socket->write(",");
        QByteArray email = accounts[i].get_email().toUtf8();
        socket->write(email);
        socket->write(",");
        QByteArray number = accounts[i].get_number().toUtf8();
        socket->write(number);
        socket->write(",");
        QString size_f = QString::number((int)accounts[i].frend.size());
        QByteArray size_friend = size_f.toUtf8();
        socket->write(size_friend);

        for (int j = 0; j < (int)accounts[i].frend.size(); j++)
        {
            socket->write(",");
            socket->write(accounts[i].frend[j].get_user_name().toUtf8());
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
        if (accounts[i].get_user_name() == usr)
        {
            qDebug() << "invalid username ";
            flag =1;
            break;
        }
    }

    for (int i = 0; i < (int)accounts.size(); i++)
    {
        if (accounts[i].get_email() == email)
        {
            qDebug() << "invalid email";
            flag =1;
            break;
        }
    }

    for (int i = 0; i < (int)accounts.size(); i++)
    {
        if (accounts[i].get_number() == number)
        {
            qDebug() << "invalid number ";
            flag =1;
            break;
        }
    }
    return flag;
}
