#include "world.h"

TWorld::TWorld(QObject *parent):
    QObject(parent),
    World(new b2World(b2Vec2(0,0))),
    BackgroundImageNumber(1),
    BackgroundTimer(0),
    _gmY(-480),
    GameOvered(false),
    _gmImage(QImage(gameOver))
{
    World->SetContactListener(this);

    Player=new TPlayer(World,&Surface);
    Ball=new TBall(World,&Surface);
    _currentFrame=QImage(QString("%1%2%3").arg(bgImagesPath).arg(BackgroundImageNumber).arg(bgImagesEnd));


    // BodyDef for walls
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(0,0);
    bodyDef.angle = 0;
    b2Body *body = World->CreateBody(&bodyDef);

    b2PolygonShape polygon;
    b2FixtureDef fixture;
    fixture.restitution = 1;
    fixture.friction = 0;

    // Border #1
    polygon.SetAsBox(0.1 * bgSizeX, 0.1 * 1, b2Vec2(0, -20 * 0.1), 0);
    fixture.shape = &polygon;
    body->CreateFixture(&fixture);

    // Border #2
    polygon.SetAsBox(0.1 * 1, 0.1 *bgSizeY, b2Vec2(-20 * 0.1, 0), 0);
    fixture.shape = &polygon;
    body->CreateFixture(&fixture);

    // Border #3
    polygon.SetAsBox(0.1 * 1, 0.1 * bgSizeY, b2Vec2(0.1 * bgSizeX, 20 * 0.1),0);
    fixture.shape = &polygon;
    body->CreateFixture(&fixture);

    // Blocks
    for (int q = 0; q < 20; q++) {
        for (int i = 0; i < 5; i++) {
            Blocks.append(new TBlock(World, &Surface, QPointF(q * 40, i * 40)));
        }
    }

    Music.setCurrentSource(bgSong);
    Music.enqueue(bgSong1);
    Phonon::createPath(&Music,&AudoiOut);
    Music.play();

    startTimer(20);
}

void TWorld::timerEvent(QTimerEvent *)
{
    if (!GameOvered)
    {
        World->Step(1.0 / 50.0, 5, 2);
       for (int q = 0; q < Blocks.size(); q++)
        {
            if (Blocks[q]->IsDestroyed())
            {
                Blocks[q]->Delete();
                Blocks.remove(q);
            }
        }
        GameOvered=Ball->GameOver();
    }
}

void TWorld::paint()
{
    Surface=_currentFrame;

    if (!GameOvered) {
        Player->paint();
        Ball->Paint();

        for (int q=0;q<Blocks.size();q++) {
            Blocks[q]->Paint();
        }

        if (BackgroundTimer >= bgTime) {
            BackgroundTimer = 0;
            if (BackgroundImageNumber >= bgNumbers) {
                BackgroundImageNumber = 1;
            } else {
                BackgroundImageNumber++;
            }
        }
        else {
            BackgroundTimer++;
        }
    }
    else {
        QPainter painter(&Surface);
        painter.drawImage(0, _gmY, _gmImage);
        if (_gmY != 0)
            _gmY += 10;
    }
}

void TWorld::move(qreal x) {
    Player->move(x);
}

QImage TWorld::surface() {
    return Surface;
}

 // Collisions processing
void TWorld::BeginContact(b2Contact* contact) {
    TBlock* block = NULL;
    if (contact->GetFixtureA()->GetBody()->GetUserData() != NULL) {
        block = (TBlock*)contact->GetFixtureA()->GetBody()->GetUserData();
    }
    if (contact->GetFixtureB()->GetBody()->GetUserData() != NULL) {
        block = (TBlock*)contact->GetFixtureB()->GetBody()->GetUserData();
    }
    if (block != NULL) {
        block->Destroy();
    }
}
