#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QObject>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include "account.h"
#include "chatroom_abs.h"
#include "private_chat.h"
#include <vector>
#include <sstream>

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(qintptr ID , std::vector<Account>& accs, std::vector<ChatRoom_abs*>& chats ,QObject *parent = 0);
    void run();

signals:
       void error(QTcpSocket::SocketError socketerror);

public slots:
       void readyRead();
       void disconnected();
       void signin(QString user, QString email, QString num, QString pass, int year, int month, int day);
       void login(QString user, QString pass);
       void myAccount();

private:
    void create_chatRoom(std::vector<std::string> infos);
    void show_chatRooms(std::vector<std::string> infos);
    std::string getInfo();
    std::vector<std::string> split(std::string str,char separator);
    QTcpSocket *socket;
    qintptr socketDescriptor;
    std::vector<Account>& accounts;
    std::vector<ChatRoom_abs*>& chats;
    int acc_index;
};

#endif // MYTHREAD_H
