#pragma once
#include <Box2D/Box2D.h>
#include <QtCore>
#include <QImage>
#include <QPainter>
#include "values.h"

class Ball
{
public:
    Ball(b2World *world, QImage *surface);
    void paint();
    void update();
    bool gameOver();
private:
    b2Body *_body;
    QImage _image,*_surface;
    b2Vec2 _speed;
};

