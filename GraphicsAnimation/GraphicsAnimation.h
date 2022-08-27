#ifndef GRAPHICSANIMATION_H
#define GRAPHICSANIMATION_H

/*我是顶层*/

#include "MyScene.h"
#include <QtWidgets/QMainWindow>
#include "ui_GraphicsAnimation.h"
#include <QGraphicsView>
#include <QPushButton>
#include <QPixmap>
#include <QFileDialog>
#include <QUrl>
#include <QDesktopServices>

#define  BEGIN    0
#define  SUSPEND  1
#define  GOHEAD   2

namespace Ui {
class GraphicsAnimation;
}

class GraphicsAnimation : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphicsAnimation(QWidget *parent = 0);
    ~GraphicsAnimation();

    void sleep(unsigned int);

public slots:
     void buttonStartClicked();
     void buttonScreenshotsClicked();
     void buttonStopClicked();
     void buttonTraceClicked();
     void buttonDelTraceClicked();
     void buttonLikeClicked();
     void buttonAddClicked();
     void buttonSubClicked();

private:
    Ui::GraphicsAnimation *ui;
    MyScene *m_scene;   //定义中间层对象指针，方便调用中间层接口
    int m_flag;         //开始暂停标志位
    bool m_trace;       //是否已画轨迹
};

#endif // GRAPHICSANIMATION_H
