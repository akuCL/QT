#ifndef MYITEM_H
#define MYITEM_H

/*我是底层*/

#pragma once
#include <QPainter>
#include <QGraphicsItem>
#include <QPainterPath>
#include <QTime>
#include <QTimer>

//判断小球形状
#define CIRCLE   100
#define SQUARE   101
#define TRIANGLE 102

class MyItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    MyItem();
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    ~MyItem(void);

    void randNumInit(); //随机数
    void move();        //小球运动
    void suspend();     //暂停
    void stop();        //停止
    void addSpeed();    //加速
    void subSpeed();    //减速

    //切换形状
    void change2Circle();
    void change2Square();
    void change2Triangle();

    void move2Point();
    void newPath();

public slots:
    void drawMyTrace();
    void recvGoBack();
    void goingReverse();

    QGraphicsPathItem *gainPathItem()
    {
        return m_pathItem;
    }

protected:
    void timerEvent(QTimerEvent *);

private:
    int m_id;                 //定时器id
    int m_shape;              //小球形状
    int m_rand_num_x;         //横坐标增量随机数
    int m_rand_num_y;         //纵坐标增量随机数
    int m_rand_num_symbol;    //坐标增量的符号
    qreal m_shape_x;	      //小球位置横坐标
    qreal m_shape_y;	      //小球位置众坐标
    qreal m_dx, m_dy;         //移动步长单位
    QTime m_time;
    QGraphicsPathItem *m_pathItem; //曲线图元
    QPainterPath *m_path;          //轨迹

    bool m_forward;             //是否反向
};

#endif // MYITEM_H
