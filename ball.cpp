#include "ball.h"
#include "opts.h"
#include <stdlib.h>

using Opts::fieldHeight;
using Opts::fieldWidth;
using Opts::ballRadius;

Ball::Ball()
        : QGraphicsEllipseItem(0, 0, 2*ballRadius, 2*ballRadius)
{
}

void Ball::init() {
    setPos(fieldWidth/2 - ballRadius, fieldHeight/2 - ballRadius);
    imp.x = (rand()%2) ? 0.8 : -0.8;
    imp.y = (rand()%2) ? 0.2 : -0.2;
    speed = Opts::startingSpeed;
}

void Ball::move() {
    for(int i=0; i < speed; i++) {
        setPos(pos().x() + imp.x, pos().y() + imp.y);
        QList<QGraphicsItem *> coll = collidingItems();
        if(x() <= 0) {
            emit leftField(LEFT);
            return;
        }
        if(x() + ballRadius*2 >= fieldWidth) {
            emit leftField(RIGHT);
            return;
        }
        for(auto item : coll) {
            emit collided(item);
        }
    }
}

void Ball::speedUp() {
    if(speed < Opts::maxSpeed) speed++;
}

bool Ball::isMovingDownwards() {
    return imp.y > 0;
}

bool Ball::isMovingUpwards() {
    return imp.y < 0;
}
