#include "myserver.h"
#include <QApplication>

#include "account.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyServer server;
    server.startServer();
    return a.exec();
}
