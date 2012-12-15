#pragma once
#include <Box2D/Box2D.h>
#include <QImage>
#include <QPainter>
#include <QPointF>

#include "values.h"


class TBlock
{
public:
    TBlock(b2World *world, QImage *surface, const QPointF &position);
    void Paint();
    bool IsDestroyed();
    void Destroy();
    void Delete();
private:
    QImage* Surface;
    QImage Image;
    b2Body* Body;
    bool Destroyed;
};
