#include "MyScene.h"
#include <QMessageBox>

MyScene::MyScene(QObject *parent)
    : QGraphicsScene(parent)
{
    m_pitem = new MyItem;

    //设置场景大小
    this->setSceneRect(-615, -385, 1230, 770);
    this->addItem(m_pitem);

    connect(this, &MyScene::signalGoBack, m_pitem, &MyItem::recvGoBack);
}

MyScene::~MyScene(void)
{
}

//控制运动状态
void MyScene::beginRun()
{
    m_pitem->move();
}
void MyScene::suspendRun()
{
    m_pitem->suspend();
}
void MyScene::stopRun()
{
    m_pitem->stop();

    m_timer.stop();
    this->removeItem(m_pitem->gainPathItem());
}

//加速 槽函数
void MyScene::buttonAddClicked()
{
    m_pitem->addSpeed();
}

//减速 槽函数
void MyScene::buttonSubClicked()
{
    m_pitem->subSpeed();
}

//切换形状 槽函数
void MyScene::actionCircleTriggered()
{
    m_pitem->change2Circle();
}
void MyScene::actionSquareTriggered()
{
    m_pitem->change2Square();
}
void MyScene::actionTriangleTriggered()
{
    m_pitem->change2Triangle();
}

//画轨迹
void MyScene::trajectoryTracking()
{
    m_pitem->move2Point();
    this->addItem(m_pitem->gainPathItem());
    connect(&m_timer, SIGNAL(timeout()), this->m_pitem, SLOT(drawMyTrace()));
    m_timer.start(10);
}

//反向
void MyScene::actionReverseTriggered()
{
    emit signalGoBack();

    connect(&m_timer, SIGNAL(timeout()), this->m_pitem, SLOT(goingReverse()));
    m_timer.start(10);
}

//停止画轨迹
void MyScene::stopTracking()
{
    m_timer.stop();
    this->removeItem(m_pitem->gainPathItem());
}

//清除轨迹
void MyScene::delTrace()
{
    m_timer.stop();
    this->removeItem(m_pitem->gainPathItem());
    m_pitem->newPath();
}
