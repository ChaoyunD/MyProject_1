#include "myscene.h"

myScene::myScene(QObject *parent) : QGraphicsScene(parent)
{
   int i=0;
   for(i=0;i<16;i++)
   {
       this->item[i]=new myItem;
       this->item[i]->setPos(i/4*this->item[i]->boundingRect().width(),i%4*this->item[i]->boundingRect().height());
       this->addItem(this->item[i]);
   }
   this->ptimer=new QTimer;
   connect(this->ptimer,SIGNAL(timeout()),this,SLOT(showMouse()));
//   this->ptimer->start(500);
}

void myScene::showMouse()
{
    //随机一个数字 0-15
    //1-3
    int count=rand()%2+1;
    int i=0;
    for(i=0;i<16;i++)
    {
        this->item[i]->setPic(":/bg/pic/bg.png");
        this->item[i]->setMouse(false);
    }
    for(i=0;i<count;i++)
    {
        int index=rand()%16;
        this->item[index]->setPic(":/bg/pic/bg1.png");
        this->item[index]->setMouse(true);
    }
}

void myScene::startGame()
{
    int i=0;
    for(i=0;i<16;i++)
    {
        this->item[i]->setStart(true);
    }
    this->ptimer->start(300);
}

void myScene::pauseGame()
{
    int i=0;
    for(i=0;i<16;i++)
    {
        this->item[i]->setStart(false);
    }
    this->ptimer->stop();
}

void myScene::stopGame()
{
    int i=0;
    for(i=0;i<16;i++)
    {
        this->item[i]->setStart(false);
    }
    this->ptimer->stop();
    for(i=0;i<16;i++)
    {
        this->item[i]->setPic(":/bg/pic/bg.png");
        this->item[i]->setMouse(false);
    }
}
