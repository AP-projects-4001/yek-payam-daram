#include "myserver.h"

#include <QApplication>

#include "account.h"

int Account::idgenerator = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyServer server;
    server.startServer();
    return a.exec();
}
