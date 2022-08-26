/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Server
{
public:
    QLabel *serverStatusLabel;
    QProgressBar *serverProgressBar;
    QPushButton *startButton;

    void setupUi(QDialog *Server)
    {
        if (Server->objectName().isEmpty())
            Server->setObjectName(QStringLiteral("Server"));
        Server->resize(400, 300);
        serverStatusLabel = new QLabel(Server);
        serverStatusLabel->setObjectName(QStringLiteral("serverStatusLabel"));
        serverStatusLabel->setGeometry(QRect(50, 60, 291, 16));
        serverProgressBar = new QProgressBar(Server);
        serverProgressBar->setObjectName(QStringLiteral("serverProgressBar"));
        serverProgressBar->setGeometry(QRect(50, 100, 321, 23));
        serverProgressBar->setValue(0);
        startButton = new QPushButton(Server);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(230, 200, 75, 23));

        retranslateUi(Server);

        QMetaObject::connectSlotsByName(Server);
    } // setupUi

    void retranslateUi(QDialog *Server)
    {
        Server->setWindowTitle(QApplication::translate("Server", "Server", 0));
        serverStatusLabel->setText(QApplication::translate("Server", "\346\234\215\345\212\241\345\231\250\347\253\257", 0));
        startButton->setText(QApplication::translate("Server", "\345\274\200\345\247\213\347\233\221\345\220\254", 0));
    } // retranslateUi

};

namespace Ui {
    class Server: public Ui_Server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
