#ifndef MYSCENE_H
#define MYSCENE_H

/*我是中间层*/

#include "MyItem.h"
#include <QGraphicsScene>
#include <QTimer>

class MyScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MyScene(QObject *parent = 0);
    ~MyScene(void);
    //运动相关
    void beginRun();
    void stopRun();
    void suspendRun();

    //轨迹相关
    void trajectoryTracking();
    void stopTracking();
    void delTrace();

    void buttonAddClicked();
    void buttonSubClicked();

public slots:
    void actionCircleTriggered();
    void actionSquareTriggered();
    void actionTriangleTriggered();
    void actionReverseTriggered();

signals:
    void signalGoBack();

private:
    MyItem *m_pitem;
    QTimer m_timer;
};

#endif // MYSCENE_H
