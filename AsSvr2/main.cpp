#include <QCoreApplication>
#include "myserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyServer Server;
    Server.StartServer();
    Server.setConnectCount(5);
    return a.exec();
}
