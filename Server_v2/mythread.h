#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QObject>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include "account.h"
#include <vector>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(qintptr ID ,QObject *parent = 0);

    void run();

signals:
       void error(QTcpSocket::SocketError socketerror);

public slots:
       void readyRead();
       void disconnected();
       void signin(QString user, QString email, QString num, QString pass, int year, int month, int day);
       void login(QString user, QString pass);
       void saving_data();
       void loading_data();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
private:
    Account* new_acc;
    std::vector<Account*> accounts;
};

#endif // MYTHREAD_H
