#pragma once
#include <QtCore>
#include <Box2D/Box2D.h>
#include <QImage>
#include <QPainter>
#include "values.h"
#include "ball.h"

class TPlayer
{
public:
    TPlayer(b2World *world, QImage *surface);
    void paint();
    void move(qreal x);
private:
    b2Body* Body;
    QImage* Surface;
    QImage Image;
};
