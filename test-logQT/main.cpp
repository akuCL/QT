#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QMutex>
#include <QTextStream>
#include <QTime>
//方式二
//首先，包含头文件
#include <QDebug>

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();
    QString text;
    switch(type)
    {
    case QtInfoMsg:
        text = QString("Info:");
        break;
    case QtDebugMsg:
        text = QString("Debug:");
        break;
    case QtWarningMsg:
        text = QString("Warning:");
        break;
    case QtCriticalMsg:
        text = QString("Critical:");
        break;
    case QtFatalMsg:
        text = QString("Fatal:");
    }
    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString current_date = QString("%1").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(current_date).arg(text).arg(context_info).arg(msg);


    //判断文件夹是否存在，不存在新建
    QString aFile = QDir::currentPath() + "/LogFile/" + QDateTime::currentDateTime().toString("yyyyMMdd");
    QDir dir(aFile);
    if(!dir.exists())
    {
        dir.mkdir(aFile);//只创建一级子目录，即必须保证上级目录存在
    }

    QString current_time = QDateTime::currentDateTime().toString("yyyyMMddhh");
    QFile file(aFile+"/log"+current_time+".txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n \r\n";

    file.flush();
    file.close();
    mutex.unlock();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInstallMessageHandler(outputMessage);

    //方式一：
    //打印日志到文件中
    qDebug("This is a debug message");
    qWarning("This is a warning message");
    qCritical("This is a critical message");
    QString LogInfo="这是一个测试消息！";
    qDebug() <<LogInfo ;
    //qFatal(LogInfo.toLatin1().data());


    return a.exec();
}
