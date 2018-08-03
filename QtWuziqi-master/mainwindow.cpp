#include <QPainter>
#include <QTimer>
#include <QSound>
#include <QMouseEvent>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <math.h>
#include <QBrush>
#include "mainwindow.h"

// -------全局遍历-------//
#define CHESS_ONE_SOUND ":/res/sound/chessone.wav"
#define WIN_SOUND ":/res/sound/win.wav"
#define LOSE_SOUND ":/res/sound/lose.wav"

const int kBoardMargin = 30; // 棋盘边缘空隙
const int kRadius = 15; // 棋子半径
const int kMarkSize = 6; // 落子标记边长
const int kBlockSize = 40; // 格子的大小
const int kPosDelta = 20; // 鼠标点击的模糊距离上限

const int kAIDelay = 700; // AI下棋的思考时间

// -------------------- //

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle(tr("五子棋"));
    // 设置棋盘大小
    setFixedSize(kBoardMargin * 2 + kBlockSize * kBoardSizeNum, kBoardMargin * 2 + kBlockSize * kBoardSizeNum);
//    setStyleSheet("background-color:yellow;");

    // 开启鼠标hover功能，这两句一般要设置window的
    setMouseTracking(true);
//    centralWidget()->setMouseTracking(true);

    // 添加开始菜单
    //ps:菜单栏变大
    QMenu *gameMenu = menuBar()->addMenu(tr("开始游戏")); // menuBar默认是存在的，直接加菜单就可以了
    QAction *actionPVP = new QAction("人人模式", this);
    connect(actionPVP,&QAction::triggered,[=](){
           game_level=NONE;
           initPVPGame();
       });
    gameMenu->addAction(actionPVP);
    gameMenu->addSeparator();//添加分割线

    QMenu *botMenu= gameMenu->addMenu(tr("人机模式"));//在gameMenu再次添加菜单
    botMenu->setTitle(tr("人机模式"));

    QAction *easy=new QAction(tr("简单模式"),botMenu);//在botMenu上添加动作
    connect(easy,&QAction::triggered,[=](){
           initPVEGame();
           game_level=EASY;
       });
    botMenu->addAction(easy);

    QAction *normal=new QAction(tr("一般模式"),botMenu);
    connect(normal,&QAction::triggered,[=](){
            game_level=NORMAL;
           initPVEGame();

       });
    botMenu->addAction(normal);

    QAction *hard=new QAction(tr("困难模式"),botMenu);
    connect(hard,&QAction::triggered,[=](){
           game_level=HARD;
           initPVEGame();
       });
     botMenu->addAction(hard);

    //添加退出菜单
    QMenu *quitMenu=menuBar()->addMenu(tr("退出游戏"));
    QAction *actionQuit=new QAction(tr("退出游戏"),this);
    connect(actionQuit,SIGNAL(triggered()),this,SLOT(windowClose()));
    quitMenu->addAction(actionQuit);

    // 开始游戏
    initGame();
}

MainWindow::~MainWindow()
{
    if (game)
    {
        delete game;
        game = nullptr;
    }
}

void MainWindow::windowClose()
{
    QMessageBox::StandardButton btn_close=QMessageBox::warning(this,"关闭游戏","确认关闭游戏吗？",QMessageBox::Yes|QMessageBox::No);
    if(btn_close!=QMessageBox::No)
    {
        this->close();
    }
}

void MainWindow::initGame()
{   
    // 初始化游戏模型
    game = new GameModel;
    initPVPGame();
}

void MainWindow::initPVPGame()
{
    game_type = PERSON;
    game->gameStatus = PLAYING;
    game->startGame(game_type,game_level);
    update();
}

void MainWindow::initPVEGame()
{
    game_type = BOT;
    game->gameStatus = PLAYING;
    game->startGame(game_type,game_level);
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 绘制棋盘
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
    painter.setBrush(QColor(249,214,91));//设置背景颜色
    painter.drawRect(rect());
    QPen pen; // 调整线条宽度和设置xianta线条颜色
    pen.setWidth(2);
    painter.setPen(pen);
    for (int i = 0; i < kBoardSizeNum + 1; i++)
    {
        painter.drawLine(kBoardMargin + kBlockSize * i, kBoardMargin, kBoardMargin + kBlockSize * i, size().height() - kBoardMargin);
        painter.drawLine(kBoardMargin, kBoardMargin + kBlockSize * i, size().width() - kBoardMargin, kBoardMargin + kBlockSize * i);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    // 绘制落子标记(防止鼠标出框越界)
    if (clickPosRow > 0 && clickPosRow < kBoardSizeNum &&
        clickPosCol > 0 && clickPosCol < kBoardSizeNum &&
        game->gameMapVec[clickPosRow][clickPosCol] == 0)
    {
        if (game->playerFlag)
            brush.setColor(Qt::white);
        else
            brush.setColor(Qt::black);
        painter.setBrush(brush);
        painter.drawRect(kBoardMargin + kBlockSize * clickPosCol - kMarkSize / 2, kBoardMargin + kBlockSize * clickPosRow - kMarkSize / 2, kMarkSize, kMarkSize);
    }

    // 绘制棋子 
    for (int i = 0; i < kBoardSizeNum; i++)
        for (int j = 0; j < kBoardSizeNum; j++)
        {
            if (game->gameMapVec[i][j] == 1)
            {
                brush.setColor(Qt::white);
                painter.setPen(Qt::white); // 设置画笔颜色为白色，此时边框颜色等于白色。
                painter.setBrush(brush);// 还可以设置填充颜色
                painter.drawEllipse(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius, kRadius * 2, kRadius * 2);

            }
            else if (game->gameMapVec[i][j] == -1)
            {
                painter.setPen(Qt::black); // 设置画笔颜色为黑色，此时边框颜色等于黑色。
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius, kRadius * 2, kRadius * 2);
            }
        }

    // 判断输赢
    if (clickPosRow > 0 && clickPosRow < kBoardSizeNum &&
        clickPosCol > 0 && clickPosCol < kBoardSizeNum &&
        (game->gameMapVec[clickPosRow][clickPosCol] == 1 ||
            game->gameMapVec[clickPosRow][clickPosCol] == -1))
    {
        if (game->isWin(clickPosRow, clickPosCol) && game->gameStatus == PLAYING)
        {
            qDebug() << "win";
            game->gameStatus = WIN;
            QSound::play(WIN_SOUND);
            QString str;
            if (game->gameMapVec[clickPosRow][clickPosCol] == 1)
                str = "白棋玩家";
            else if (game->gameMapVec[clickPosRow][clickPosCol] == -1)
                str = "黑棋玩家";
            //QMessageBox::StandardButton btnValue = QMessageBox::information(this, "", str + "胜利!",QMessageBox::Ok);
            QMessageBox *btnValue=new QMessageBox(this);
             btnValue->setWindowTitle(tr("胜负判断"));//对话框标题
            //设置字体样式和大小
             QFont font;
             font.setFamily(" 叶根友毛笔行书");//样式
             font.setPointSize(15);//大小

             btnValue->setFont(font);
             btnValue->setText(str+"胜利!");//显示内容
             btnValue->setStandardButtons(QMessageBox::Ok);
             btnValue->setDefaultButton(QMessageBox::Ok);
             btnValue->exec();
            // 重置游戏状态，否则容易死循环
            if (1)
            {
                game->startGame(game_type,game_level);
                game->gameStatus = PLAYING;
            }
        }
    }


    // 判断死局
    if (game->isDeadGame())
    {
        QSound::play(LOSE_SOUND);
        QMessageBox::StandardButton btnValue = QMessageBox::information(this, "oops!", "死局!");
        if (btnValue == QMessageBox::Ok)
        {
            game->startGame(game_type,game_level);
            game->gameStatus = PLAYING;
        }

    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{   
    // 通过鼠标的hover确定落子的标记
    int x = event->x();
    int y = event->y();

    // 棋盘边缘不能落子
    if (x >= kBoardMargin + kBlockSize / 2 &&
            x < size().width() - kBoardMargin &&
            y >= kBoardMargin + kBlockSize / 2 &&
            y < size().height()- kBoardMargin)
    {
        // 获取最近的左上角的点
        int col = x / kBlockSize;
        int row = y / kBlockSize;

        int leftTopPosX = kBoardMargin + kBlockSize * col;
        int leftTopPosY = kBoardMargin + kBlockSize * row;

        // 根据距离算出合适的点击位置,一共四个点，根据半径距离选最近的
        clickPosRow = -1; // 初始化最终的值
        clickPosCol = -1;
        int len = 0; // 计算完后取整就可以了

        // 确定一个误差在范围内的点，且只可能确定一个出来
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col + 1;
        }
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - kBlockSize) * (y - leftTopPosY - kBlockSize));
        if (len < kPosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY - kBlockSize) * (y - leftTopPosY - kBlockSize));
        if (len < kPosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col + 1;
        }
    }

    // 存了坐标后也要重绘
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // 人下棋，并且不能抢机器的棋
    if (!(game_type == BOT && !game->playerFlag))
    {
        chessOneByPerson();
        // 如果是人机模式，需要调用AI下棋
        if (game->gameType == BOT && !game->playerFlag)
        {
            // 用定时器做一个延迟
            QTimer::singleShot(kAIDelay, this, SLOT(chessOneByAI()));
        }
    }

}

void MainWindow::chessOneByPerson()
{
    // 根据当前存储的坐标下子
    // 只有有效点击才下子，并且该处没有子
    if (clickPosRow != -1 && clickPosCol != -1 && game->gameMapVec[clickPosRow][clickPosCol] == 0)
    {
        game->actionByPerson(clickPosRow, clickPosCol);
        QSound::play(CHESS_ONE_SOUND);

        // 重绘
        update();
    }
}

void MainWindow::chessOneByAI()
{
    game->actionByAI(clickPosRow, clickPosCol,game_level);
    QSound::play(CHESS_ONE_SOUND);
    update();
}

