#include "player.h"

TPlayer::TPlayer(b2World *world, QImage *surface):
    Surface(surface),
    Image(QImage(playerImage))
{
    b2BodyDef body;
    body.type=b2_staticBody;
    body.position.Set(playerPosX * 0.1 ,playerPosY * 0.1);
    body.angle=0;
    Body=world->CreateBody(&body);
    b2PolygonShape polygon;

    polygon.SetAsBox((playerSizeX / 2 - 4) * 0.1,
                     playerSizeY * 0.1 / 2,
                     b2Vec2((playerSizeX / 2 - 4) * 0.1,
                            playerSizeY * 0.1 / 2),
                     0);

    b2FixtureDef fixture;
    fixture.shape = &polygon;
    fixture.restitution = 1;
    fixture.friction = 0;
    Body->CreateFixture(&fixture);
}

void TPlayer::paint()
{
    QPainter painter(Surface);
    painter.drawImage(Body->GetPosition().x * 10, Body->GetPosition().y*10, Image);
}

void TPlayer::move(qreal x)
{
    if (x<0) {
        x=0;
    } else if(x+playerSizeX>bgSizeX) {
        x=bgSizeX-playerSizeX;
    }
    Body->SetTransform(b2Vec2(x * 0.1, playerPosY * 0.1), 0);
}
