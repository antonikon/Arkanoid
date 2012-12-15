#pragma once
#include <Box2D/Box2D.h>
#include <QImage>
#include <QPainter>
#include "values.h"
#include <QPointF>

class Block
{
public:
    Block(b2World *world, QImage *surface, const QPointF &position);
    void paint();
    void update();
    bool isDestroy();
private:
    QImage *_surface, _image;
    b2Body *_body;
    bool _isDestroy;
};
