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

class TWorld: public QObject, public b2ContactListener
{
    Q_OBJECT
public:
    TWorld(QObject *parent=0);
    void timerEvent(QTimerEvent *);
    void paint();
    void move(qreal x);
    QImage surface();
private:
    void BeginContact(b2Contact* contact);
private:
    TPlayer* Player;
    TBall* Ball;
    QVector <TBlock*> Blocks;
    b2World* World;
    qint32 BackgroundImageNumber, BackgroundTimer, _gmY;
    bool GameOvered;
    QImage Surface, _gmImage, _currentFrame;
    Phonon::MediaObject Music;
    Phonon::AudioOutput AudoiOut;
};

