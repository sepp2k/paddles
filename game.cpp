#include "game.h"
#include "opts.h"
#include <algorithm>

using std::min;
using std::max;

using Opts::fieldHeight;
using Opts::fieldWidth;
using Opts::ballRadius;

Game::Game(QBrush fg, QWidget *parent)
    : QGraphicsScene(parent)
{
    leftScore = rightScore = 0;
    leftPaddle = new QGraphicsRectItem(0, 0, paddleWidth, paddleHeight);
    rightPaddle = new QGraphicsRectItem(0, 0, paddleWidth, paddleHeight);
    topBar = new QGraphicsRectItem(0, 0, fieldWidth, barWidth);
    bottomBar = new QGraphicsRectItem(0, fieldHeight-barWidth, fieldWidth, barWidth);
    ball = new Ball();

    leftPaddle->setBrush(fg);
    rightPaddle->setBrush(fg);
    topBar->setBrush(fg);
    bottomBar->setBrush(fg);
    ball->setBrush(fg);

    addItem(ball);
    addItem(leftPaddle);
    addItem(rightPaddle);
    addItem(topBar);
    addItem(bottomBar);

    connect(&tick, SIGNAL(timeout()), ball, SLOT(move()));
    connect(&tock, SIGNAL(timeout()), ball, SLOT(speedUp()));
    connect(ball, SIGNAL(leftField(Side)), SLOT(score(Side)));
    connect(ball, SIGNAL(collided(QGraphicsItem*)), SLOT(bounceOf(QGraphicsItem*)));
}

void Game::startRound() {
    int y = fieldHeight/2 - paddleHeight/2;
    leftPaddle->setPos(paddleOffset, y);
    rightPaddle->setPos(fieldWidth - paddleOffset - paddleWidth, y);
    ball->init();
    tick.start(Opts::tick);
    tock.start(Opts::speedIncTime);
}

qreal absInRange(qreal lower, qreal x, qreal upper) {
    if(x < 0.0) return -absInRange(lower, -x, upper);
    else return min(upper, max(lower, x));
}

void Game::bounceOf(QGraphicsItem *item) {
    if( (item == topBar && ball->isMovingUpwards()) || (item == bottomBar && ball->isMovingDownwards()) ) {
        ball->impulse().y *= -1;
    } else if(item == rightPaddle || item == leftPaddle) {
        qreal relY = ball->y() + ballRadius - item->y();
        qreal newY = absInRange(0.3, (relY - paddleHeight/2) / (paddleHeight/1.5), 0.7);
        qreal newX = 1.0 - qAbs(newY);
        if(item == rightPaddle) newX = -newX;
        ball->impulse().x = newX;
        ball->impulse().y = newY;
    }
}

void Game::score(Side side) {
    tick.stop();
    if(side==LEFT) {
        rightScore++;
        emit rightScoreChanged(rightScore);
    } else {
        leftScore++;
        emit leftScoreChanged(leftScore);
    }
    startRound();
}

void Game::movePaddle(Side side, int dy) {
    QGraphicsRectItem * paddle = side == LEFT ? leftPaddle : rightPaddle;
    paddle->moveBy(0, dy);
    if(!paddle->collidingItems().empty()) paddle->moveBy(0, -dy);
}

void Game::reset() {
    tick.stop();
    leftScore = 0;
    rightScore = 0;
    emit leftScoreChanged(leftScore);
    emit rightScoreChanged(rightScore);
    startRound();
}

Game::~Game()
{

}
