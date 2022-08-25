#include "myclient.h"

MyClient::MyClient(QObject *parent) : QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(1000);
}

void MyClient::SetSocket(int Descriptor)
{
    socket = new QTcpSocket(this);

    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this, SLOT(readyRead()));

    socket->setSocketDescriptor(Descriptor);
    qDebug() << "client connected";
}


void MyClient::connected()
{
    qDebug() << "client connected event";
}

void MyClient::disconnected()
{
    qDebug() << "client disconnected";
    emit sig_disconnected();
}

void MyClient::readyRead()
{
    qDebug()<< socket->readAll();

    MyTask * mytask = new MyTask();
    mytask->setAutoDelete(true);
    connect(mytask,SIGNAL(Result(int)),this,SLOT(TaskResult(int)));
    QThreadPool::globalInstance()->start(mytask);
}

void MyClient::TaskResult(int Number)
{
    QByteArray Buffer;
    Buffer.append("\r\nTask Result = ");
    Buffer.append(QString::number(Number));

    socket->write(Buffer);
    qDebug() << "TaskResult : " << socket;
}
