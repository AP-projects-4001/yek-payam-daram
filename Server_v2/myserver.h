#ifndef MYSERVER_H
#define MYSERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include "account.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MyServer; }
QT_END_NAMESPACE

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    void startServer();
signals:

public slots:
    void saving_data();
    void loading_data();
protected:
    void incomingConnection(qintptr socketDescriptor);

public:
    std::vector<Account*> Accounts;

};
#endif // MYSERVER_H
