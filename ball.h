#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include "opts.h"

struct Impulse {
    qreal x,y;
};

enum Side {
    LEFT, RIGHT
};

class Ball : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

    Impulse imp;
    int speed;

public:
    Ball();

    Impulse& impulse() { return imp; }

    bool isMovingUpwards();
    bool isMovingDownwards();

public slots:
    void speedUp();
    void move();
    void init();

signals:
    void collided(QGraphicsItem*);
    void leftField(Side);
};

#endif // BALL_H
