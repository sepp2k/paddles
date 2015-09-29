#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include "ball.h"

class Game : public QGraphicsScene
{
    Q_OBJECT

    static const int paddleWidth = 20;
    static const int paddleHeight = 60;
    static const int barWidth = paddleWidth;
    static const int paddleOffset = 5;

private:
    int leftScore;
    int rightScore;
    QGraphicsRectItem *leftPaddle, *rightPaddle, *topBar, *bottomBar;
    Ball *ball;
    QTimer tick;
    QTimer tock;

public:
    Game(QBrush fg, QWidget *parent = 0);
    ~Game();

public slots:
    void bounceOf(QGraphicsItem *item);
    void score(Side side);
    void startRound();
    void movePaddle(Side side, int dx);
    void reset();

signals:
    void leftScoreChanged(int);
    void rightScoreChanged(int);
};

#endif // GAME_H
