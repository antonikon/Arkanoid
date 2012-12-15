#include "world.h"

World::World(QObject *parent):
    QObject(parent),
    _world(new b2World(b2Vec2(0,0))),
    _bgNumber(1),
    _bgTimer(0),
    _gm(false),
    _gmY(-480),
    _gmImage(QImage(gameOver))
{
    _player=new Player(_world,&_surface);
    _ball=new Ball(_world,&_surface);
    b2BodyDef bodyDef;
    bodyDef.type=b2_staticBody;
    bodyDef.position.Set(0,0);
    bodyDef.angle=0;
    b2Body *body=_world->CreateBody(&bodyDef);
    b2PolygonShape polygon;
    polygon.SetAsBox(bgSizeX,1,b2Vec2(0,-20),0);
    b2FixtureDef fixture;
    fixture.shape=&polygon;
    fixture.restitution=1;
    fixture.friction=0;
    body->CreateFixture(&fixture);
    polygon.SetAsBox(1,bgSizeY,b2Vec2(-20,0),0);
    fixture.shape=&polygon;
    body->CreateFixture(&fixture);
    polygon.SetAsBox(1,bgSizeY,b2Vec2(bgSizeX,20),0);
    fixture.shape=&polygon;
    body->CreateFixture(&fixture);

    for (int q=0;q<20;q++)
        for (int i=0;i<5;i++)
            _blockList.append(new Block(_world,&_surface,QPointF(q*40,i*40)));
    _music.setCurrentSource(bgSong);
    _music.enqueue(bgSong1);
    Phonon::createPath(&_music,&_output);
    _music.play();
    startTimer(5);
}

void World::timerEvent(QTimerEvent *)
{
    if (!_gm)
    {
        _world->Step(1.0/20.0,5,2);
       for (int q=0;q<_blockList.size();q++)
        {
            _blockList[q]->update();
            if (_blockList[q]->isDestroy())
            {
                delete _blockList[q];
                _blockList.remove(q);
            }
        }
        _ball->update();
        _gm=_ball->gameOver();
    }
}

void World::paint()
{
    _surface=QImage(QString("%1%2%3").arg(bgImagesPath).arg(_bgNumber).arg(bgImagesEnd));
    if (!_gm)
    {
        _player->paint();
        _ball->paint();
        for (int q=0;q<_blockList.size();q++)
            _blockList[q]->paint();
        if (_bgTimer>=bgTime)
        {
            _bgTimer=0;
            if (_bgNumber>=bgNumbers)
                _bgNumber=1;
            else
                _bgNumber++;
        }
        else
            _bgTimer++;
    }
    else
    {
        QPainter painter(&_surface);
        painter.drawImage(0,_gmY,_gmImage);
        if (_gmY!=0)
            _gmY+=10;
    }
}

void World::move(qreal x)
{
    _player->move(x);
}

QImage World::surface()
{
    return _surface;
}
