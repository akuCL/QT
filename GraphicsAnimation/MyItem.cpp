#include "MyItem.h"

MyItem::MyItem()
{
    m_pathItem = new QGraphicsPathItem;
    m_path = new QPainterPath;

    //设置初始形状为圆形
    m_shape = CIRCLE;

    //向前运动
    m_forward = true;

    //起始位置在中心
    m_shape_x = 0;
    m_shape_y = 0;

    m_time = QTime::currentTime();
    qsrand(m_time.msec() + m_time.second() * 1000);
    randNumInit();
}

MyItem::~MyItem(void)
{
}

QRectF MyItem::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(-50 - penWidth / 2, -50 - penWidth / 2,
        100 + penWidth, 100 + penWidth);
}

void MyItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //下面是根据情况画出小球的形状以及设置属性
    if (m_shape == CIRCLE)
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(Qt::blue,Qt::SolidPattern));
        painter->drawEllipse(-25, -25, 50, 50);
    }
    else if (m_shape == SQUARE)
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(Qt::red,Qt::SolidPattern));
        painter->drawRect(-25, -25, 50, 50);
    }
    else if (m_shape == TRIANGLE)
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(Qt::green,Qt::SolidPattern));
        static const QPointF points[3] = {
            QPointF(-25, -25),
            QPointF(25,-25),
            QPointF(0, 25),
        };
        painter->drawPolygon(points, 3);
    }
}

//随机数，小球运动方向随机
void MyItem::randNumInit()
{
    m_rand_num_x = qrand() % 3 + 1;
    m_rand_num_y = qrand() % 3 + 1;
    m_rand_num_symbol = qrand() % 4;

    if (m_rand_num_symbol == 0)
    {
        m_dx = m_rand_num_x * 0.1;
        m_dy = m_rand_num_y * 0.1;
    }
    else if (m_rand_num_symbol == 1)
    {
        m_dx = -m_rand_num_x * 0.1;
        m_dy = m_rand_num_y * 0.1;
    }
    else if (m_rand_num_symbol == 2)
    {
        m_dx = m_rand_num_x * 0.1;
        m_dy = -m_rand_num_y * 0.1;
    }
    else if (m_rand_num_symbol == 3)
    {
        m_dx = -m_rand_num_x * 0.1;
        m_dy = -m_rand_num_y * 0.1;
    }
}

//重写定时器事件
void MyItem::timerEvent(QTimerEvent *event)
{
    if (m_forward == true)
    {
        m_shape_x += m_dx;
        m_shape_y += m_dy;
    }
    else    //反向运动
    {
        m_shape_x -= m_dx;
        m_shape_y -= m_dy;
    }

    setPos(m_shape_x, m_shape_y);

    //碰撞检测
    if (m_shape_x + 50 >= 638 || m_shape_x <= -590)
    {
        m_dx = -m_dx;
    }
    if (m_shape_y + 50 >= 330 || m_shape_y <= -278)
    {
        m_dy = -m_dy;
    }
}

//小球运动
void MyItem::move()
{
    m_id = startTimer(5);
}

void MyItem::move2Point()
{
    m_path->moveTo(m_shape_x, m_shape_y);
}

//暂停
void MyItem::suspend()
{
    killTimer(m_id);
}

//删除轨迹
void MyItem::newPath()
{
    m_path = new QPainterPath;
}

//停止运动
void MyItem::stop()
{
    suspend();

    m_shape_x = 0;
    m_shape_y = 0;
    setPos(m_shape_x, m_shape_y);
    newPath();

    randNumInit();
}

//小球加减速并设置上限
void MyItem::addSpeed()
{
    if (m_dx <= 50 && m_dx >= -50 && m_dy <= 50 && m_dy >= -50)
    {
        m_dx *= 2;
        m_dy *= 2;
    }
}
void MyItem::subSpeed()
{
    m_dx *= 0.5;
    m_dy *= 0.5;
}

//反向运动 槽函数
void MyItem::recvGoBack()
{
    m_forward = !m_forward;
}

//形状切换
void MyItem::change2Circle()
{
    m_shape = CIRCLE;
    update();
}
void MyItem::change2Square()
{
    m_shape = SQUARE;
    update();
}
void MyItem::change2Triangle()
{
    m_shape = TRIANGLE;
    update();
}

//画轨迹 槽函数
void MyItem::drawMyTrace()
{
    m_pathItem->setPath(*m_path);
    m_path->lineTo(m_shape_x, m_shape_y);
}

void MyItem::goingReverse()
{
    /*写个函数实现反向运动时慢慢“吃掉”轨迹*/
}
