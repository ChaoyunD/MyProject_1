#include "myitem.h"
#include <QPixmap>
#include <QDebug>
#include "handler.h"
#include <QCursor>
myItem::myItem()
{
    this->setPixmap(QPixmap(":/bg/pic/bg.png"));
    this->start=false;
    this->mouse=false;
     this->setCursor(QCursor(QPixmap(":mouse/pic/chui_up.png")));
}

void myItem::setPic(QString path)
{
    this->setPixmap(QPixmap(path));
}

void myItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(QPixmap(":mouse/pic/chui.png")));
    if(this->isStart())
    {
        handler *hand=handler::getInstance();
        if(this->isMouse())
        {
            hand->addScore();
            this->setPixmap(QPixmap(":/mouse/pic/beat.png"));
            this->mouse=false;
        }
    }
}

void myItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
     this->setCursor(QCursor(QPixmap(":mouse/pic/chui_up.png")));
}

void myItem::setMouse(bool mouse)
{
    this->mouse=mouse;
}

bool myItem::isMouse()
{
    return this->mouse;
}

void myItem::setStart(bool start)
{
    this->start=start;
}

bool myItem::isStart()
{
    return this->start;
}
