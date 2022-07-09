#ifndef MYSERVER_H
#define MYSERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include "account.h"
#include "private_chat.h"
#include <QFile>
#include <vector>
#include "groupchat.h"
#include "channel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MyServer; }
QT_END_NAMESPACE

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    void startServer();
    void saving_data();
    void loading_data();
    void saving_chatrooms();
    void loading_chatroom();
signals:

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    std::vector<Account> Accounts;
    std::vector<ChatRoom_abs*> ChatRooms;
};
#endif // MYSERVER_H
