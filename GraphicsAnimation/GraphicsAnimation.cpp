#include "GraphicsAnimation.h"
#include <QMessageBox>
#include <QTime>
#include <QApplication>
#include "ui_GraphicsAnimation.h"

GraphicsAnimation::GraphicsAnimation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphicsAnimation)
{
    ui->setupUi(this);

    //状态栏
    statusBar();

    ui->pb_begin->setStyleSheet("border:none;");
    ui->pb_stop->setStyleSheet("border:none;");
    ui->pb_faster->setStyleSheet("border:none;");
    ui->pb_slower->setStyleSheet("border:none;");
    ui->pb_like->setStyleSheet("border:none;");

    m_flag = BEGIN;
    m_trace = false;

    m_scene = new MyScene(this);

    //将场景可视化并设置背景属性
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setBackgroundBrush(QColor(0x9F, 0x66, 0x33));
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->show();

    //控制各个按钮使能，防误操作
    ui->pb_stop->setEnabled(false);
    ui->pb_slower->setEnabled(false);
    ui->pb_faster->setEnabled(false);
    ui->pb_trace->setEnabled(false);
    ui->pb_del_trace->setEnabled(false);

    ui->actionDelTrace->setEnabled(false);
    ui->actionReverse->setEnabled(false);
    ui->actionStopTrace->setEnabled(false);
    ui->actionTrace->setEnabled(false);

    //信号槽绑定连接
    connect(ui->pb_begin,       &QAbstractButton::clicked, this, &GraphicsAnimation::buttonStartClicked);
    connect(ui->pb_stop,        &QAbstractButton::clicked, this, &GraphicsAnimation::buttonStopClicked);
    connect(ui->pb_trace,       &QAbstractButton::clicked, this, &GraphicsAnimation::buttonTraceClicked);
    connect(ui->pb_faster,      &QAbstractButton::clicked, this, &GraphicsAnimation::buttonAddClicked);
    connect(ui->pb_slower,      &QAbstractButton::clicked, this, &GraphicsAnimation::buttonSubClicked);
    connect(ui->pb_del_trace,   &QAbstractButton::clicked, this, &GraphicsAnimation::buttonDelTraceClicked);
    connect(ui->pb_screenshots, &QAbstractButton::clicked, this, &GraphicsAnimation::buttonScreenshotsClicked);
    connect(ui->pb_like,        &QAbstractButton::clicked, this, &GraphicsAnimation::buttonLikeClicked);

    connect(ui->actionCircle,   &QAction::triggered, this->m_scene, &MyScene::actionCircleTriggered);
    connect(ui->actionSquare,   &QAction::triggered, this->m_scene, &MyScene::actionSquareTriggered);
    connect(ui->actionTriangle, &QAction::triggered, this->m_scene, &MyScene::actionTriangleTriggered);
    connect(ui->actionReverse,  &QAction::triggered, this->m_scene, &MyScene::actionReverseTriggered);

    connect(ui->actionSave,     &QAction::triggered, this, &GraphicsAnimation::buttonScreenshotsClicked);
    connect(ui->actionTrace,    &QAction::triggered, this, &GraphicsAnimation::buttonTraceClicked);
    connect(ui->actionDelTrace, &QAction::triggered, this, &GraphicsAnimation::buttonDelTraceClicked);   
}

GraphicsAnimation::~GraphicsAnimation()
{
    delete ui;
}

//延时函数 ms
void GraphicsAnimation::sleep(unsigned int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

//加减速
void GraphicsAnimation::buttonAddClicked()
{
    m_scene->buttonAddClicked();

    //呈现视觉效果,按钮点击效果
    ui->pb_faster->setEnabled(false);
    sleep(35);
    ui->pb_faster->setEnabled(true);
}
void GraphicsAnimation::buttonSubClicked()
{
    m_scene->buttonSubClicked();

    ui->pb_slower->setEnabled(false);
    sleep(35);
    ui->pb_slower->setEnabled(true);
}

//开始运动 槽函数
void GraphicsAnimation::buttonStartClicked()
{
    if (m_flag == BEGIN)
    {
        m_flag = SUSPEND;
        ui->pb_begin->setIcon(QIcon(":/new/prefix1/image/Suspend.png"));
        ui->pb_begin->setStatusTip(QString("暂停"));
        m_scene->beginRun();

        ui->pb_stop->setEnabled(true);
        ui->pb_slower->setEnabled(true);
        ui->pb_faster->setEnabled(true);
        ui->pb_trace->setEnabled(true);

        ui->actionReverse->setEnabled(true);
        ui->actionTrace->setEnabled(true);
    }
    else if (m_flag == SUSPEND)
    {
        m_flag = GOHEAD;
        ui->pb_begin->setIcon(QIcon(":/new/prefix1/image/Begin.png"));
        ui->pb_begin->setStatusTip(QString("继续"));
        m_scene->suspendRun();

        ui->pb_slower->setEnabled(false);
        ui->pb_faster->setEnabled(false);
    }
    else
    {
        m_flag = SUSPEND;
        ui->pb_begin->setIcon(QIcon(":/new/prefix1/image/Suspend.png"));
        m_scene->beginRun();

        ui->pb_slower->setEnabled(true);
        ui->pb_faster->setEnabled(true);
    }
}

//停止运动 槽函数
void GraphicsAnimation::buttonStopClicked()
{
    m_scene->stopRun();

    ui->pb_trace->setIcon(QIcon(":/new/prefix1/image/Trace.png"));

    ui->pb_begin->setIcon(QIcon(":/new/prefix1/image/Begin.png"));
    ui->pb_begin->setStatusTip(QString("开始"));
    m_flag = BEGIN;

    ui->pb_begin->setEnabled(true);
    ui->pb_stop->setEnabled(false);
    ui->pb_slower->setEnabled(false);
    ui->pb_faster->setEnabled(false);
    ui->pb_trace->setEnabled(false);
    ui->pb_del_trace->setEnabled(false);

    ui->actionDelTrace->setEnabled(false);
    ui->actionReverse->setEnabled(false);
    ui->actionStopTrace->setEnabled(false);
    ui->actionTrace->setEnabled(false);
}

//轨迹跟踪 槽函数
void GraphicsAnimation::buttonTraceClicked()
{
    if (m_trace == false)
    {
        m_trace = true;
        ui->pb_trace->setIcon(QIcon(":/new/prefix1/image/Back.png"));

        ui->pb_del_trace->setEnabled(true);
        ui->actionTrace->setEnabled(false);
        ui->actionStopTrace->setEnabled(true);
        ui->actionDelTrace->setEnabled(true);

        m_scene->trajectoryTracking();
    }
    else
    {
        m_trace = false;
        ui->pb_trace->setIcon(QIcon(":/new/prefix1/image/Trace.png"));
        ui->actionTrace->setEnabled(true);

        m_scene->stopTracking();
    }
}

//删除轨迹 槽函数
void GraphicsAnimation::buttonDelTraceClicked()
{
    int ret = QMessageBox::question(this, "清除轨迹", "是否确定清除轨迹？", "是", "否");
    if (0 == ret)
    {
        m_trace = false;
        ui->pb_trace->setIcon(QIcon(":/new/prefix1/image/Trace.png"));
        m_scene->delTrace();
        ui->pb_del_trace->setEnabled(false);
        ui->actionDelTrace->setEnabled(false);
    }
}

//截屏 槽函数
void GraphicsAnimation::buttonScreenshotsClicked()
{
    //以Windows风格保存图片
    QString path = QFileDialog::getSaveFileName(this,
        tr("Save Picture"),
        ".",
        tr("JPEG Files(*.jpg);;PNG Files(*.png)"));
    if(!path.isEmpty())
    {
        QPixmap m_pix(path);

        //截屏起始点坐标以及宽高，注意留出工具栏的高度
        m_pix = this->grab(QRect(0, 69, ui->graphicsView->width(), ui->graphicsView->height()));
        if (!m_pix.save(path))
        {
            QMessageBox::warning(this, tr("warning"),
                tr("Cannot save Picture:\n%1").arg(path));
            return;
        }
    }
}

void GraphicsAnimation::buttonLikeClicked()
{
    const QUrl regUrl(QLatin1String("https://blog.csdn.net/hua12134"));
    QDesktopServices::openUrl(regUrl);
    
    ui->pb_slower->setEnabled(false);
    sleep(35);
    ui->pb_slower->setEnabled(true);
}
