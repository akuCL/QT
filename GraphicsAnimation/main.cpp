#include "GraphicsAnimation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphicsAnimation w;
    w.show();

    return a.exec();
}
