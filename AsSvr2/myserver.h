#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "myclient.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);

    void StartServer();
    void setConnectCount(uint count);
protected:
    void incomingConnection(int Hnadle);

signals:

public slots:
    void slot_disconnected();

private:
    QList<MyClient*> MyClientList;
    uint m_ConnectCount;

};

#endif // MYSERVER_H
