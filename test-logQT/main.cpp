#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QMutex>
#include <QTextStream>
#include <QTime>
#include <QThread>
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
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    QString current_date = QString("%1").arg(current_date_time);
    QString message = QString("%1 %2 \t%3\t%4").arg(current_date).arg(context_info).arg(text).arg(msg);

    //判断文件夹是否存在，不存在新建
    QString aFile = QDir::currentPath() + "/LogFile/" + QDateTime::currentDateTime().toString("yyyyMMdd");
    QDir dir(aFile);
    if(!dir.exists())
    {
        dir.mkdir(aFile);//只创建一级子目录，即必须保证上级目录存在
    }

    QString current_time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh");
    QFile file(aFile+"/log"+current_time+".txt");
    if(file.size() > 4 * 1024 * 1024 )
    {
        file.copy(aFile+"/log"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss.zzz") + ".txt");
        file.setFileName(aFile+"/log"+current_time+".txt");
        file.remove();
    }
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream text_stream(&file);
        text_stream << message << "\r\n";
        file.flush();
        file.close();
    }
    mutex.unlock();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInstallMessageHandler(outputMessage);

    for(int i = 0; i < 100 ; ++i)
    {
        qDebug("This is a debug message");
        qWarning("This is a warning message");
        qCritical("This is a critical message");
        QString LogInfo="这是一个测试消息！";
        qDebug() <<LogInfo ;
        //qFatal(LogInfo.toLatin1().data());
        QThread::msleep(10);
    }

    return a.exec();
}
