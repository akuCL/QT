#include "myserver.h"
//#include <QDebug>

MyServer::MyServer(QObject *parent):
    QTcpServer(parent)
{
}

void MyServer::StartServer()
{
    if(listen(QHostAddress::Any,1234))
    {
        qDebug() << "started";
    }
    else
    {
        qDebug()<< "not started";
    }
}

void MyServer::setConnectCount(uint count)
{
    m_ConnectCount = count;
}

void MyServer::incomingConnection(int handle)
{
    MyClient *client = new MyClient(this);
    client->SetSocket(handle);
    connect(client,SIGNAL(sig_disconnected()),this,SLOT(slot_disconnected()));

    MyClientList.append(client);

    if(m_ConnectCount <= (uint)MyClientList.count())
    {
        close();
    }
    qDebug() << "incomingConnection count:" << MyClientList.count();
}

void MyServer::slot_disconnected()
{
    MyClient* myClient = dynamic_cast<MyClient*>(sender());
    for(int i = 0 ; i < MyClientList.count() ; ++i)
    {
        if(MyClientList[i] == myClient)
        {
            qDebug() << "incomingConnection count:" << MyClientList.count();
            disconnect(MyClientList[i],SIGNAL(sig_disconnected()),this,SLOT(slot_disconnected()));
            MyClientList.removeAt(i);
            i = 0;
            StartServer();
        }
    }
}
