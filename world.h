#pragma once
#include "player.h"
#include "ball.h"
#include "block.h"
#include <QVector>
#include <Box2D/Box2D.h>
#include <QtCore>
#include <QImage>
#include <QPainter>
#include <QObject>
#include <QString>
#include "values.h"
#include <phonon/phonon>
#include <QTimerEvent>
#include <QPointF>

class World: public QObject
{
    Q_OBJECT
public:
    World(QObject *parent=0);
    void timerEvent(QTimerEvent *);
    void paint();
    void move(qreal x);
    QImage surface();
private:
    Player *_player;
    Ball *_ball;
    QVector <Block*> _blockList;
    b2World *_world;
    QImage _surface,_gmImage;
    qint32 _bgNumber, _bgTimer, _gmY;
    Phonon::MediaObject _music;
    Phonon::AudioOutput _output;
    bool _gm;
};

