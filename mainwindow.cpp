#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QGLWidget>
#include <QDebug>

using Opts::fieldHeight;
using Opts::fieldWidth;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    // Required to make arrow keys work.
    this->setFocus();

    QPixmap bg("bg.jpg");

    game = new Game(QColor(213,213,213,200));
    m_ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::DirectRendering),this));
    m_ui->graphicsView->setScene(game);
    QRectF rect = m_ui->graphicsView->sceneRect();
    m_ui->graphicsView->setBackgroundBrush(bg.scaled(rect.width(), rect.height()));
    m_ui->graphicsView->resize(Opts::fieldWidth, Opts::fieldHeight);
    connect(game, SIGNAL(leftScoreChanged(int)), m_ui->leftScore, SLOT(display(int)));
    connect(game, SIGNAL(rightScoreChanged(int)), m_ui->rightScore, SLOT(display(int)));
    connect(&tickerick, SIGNAL(timeout()), SLOT(movePaddles()));
    connect(m_ui->action_New_Game, SIGNAL(triggered()), game, SLOT(reset()));
    connect(m_ui->action_Quit, SIGNAL(triggered()), SLOT(close()));

    game->startRound();
    tickerick.start(10);
    lup=ldown=rdown=rup=false;
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_W:
        lup=true;
        break;

    case Qt::Key_S:
        ldown=true;
        break;

    case Qt::Key_8:
    case Qt::Key_Up:
        rup=true;
        break;

    case Qt::Key_2:
    case Qt::Key_Down:
        rdown=true;
        break;
    }
    QMainWindow::keyPressEvent(e);
}
void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_W:
        lup=false;
        break;

    case Qt::Key_S:
        ldown=false;
        break;

    case Qt::Key_8:
    case Qt::Key_Up:
        rup=false;
        break;

    case Qt::Key_2:
    case Qt::Key_Down:
        rdown=false;
        break;
    }
    QMainWindow::keyReleaseEvent(e);
}

void MainWindow::movePaddles() {
    if(lup) game->movePaddle(LEFT, -5);
    if(ldown) game->movePaddle(LEFT, 5);
    if(rup) game->movePaddle(RIGHT, -5);
    if(rdown) game->movePaddle(RIGHT, 5);
}
