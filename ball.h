#pragma once
#include <Box2D/Box2D.h>
#include <QtCore>
#include <QImage>
#include <QPainter>

#include "values.h"

class TBall
{
public:
    TBall(b2World *world, QImage *surface);
    void Paint();
    bool GameOver();
private:
    b2Body* Body;
    QImage* Surface;
    QImage Image;
    b2Vec2 Speed;
};
