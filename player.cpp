#include "player.h"

Player::Player(b2World *world, QImage *surface):
    _surface(surface),
    _image(QImage(playerImage))
{
    b2BodyDef body;
    body.type=b2_staticBody;
    body.position.Set(playerPosX,playerPosY);
    body.angle=0;
    _body=world->CreateBody(&body);
    b2PolygonShape polygon;
    polygon.SetAsBox(playerSizeX/2-4,playerSizeY/2,b2Vec2(playerSizeX/2-4,playerSizeY/2),0);
    b2FixtureDef fixture;
    fixture.shape=&polygon;
    fixture.restitution=1;
    fixture.friction=0;
    _body->CreateFixture(&fixture);
}

void Player::paint()
{
    QPainter painter(_surface);
    painter.drawImage(_body->GetPosition().x,_body->GetPosition().y,_image);
}

void Player::move(qreal x)
{
    if (x<0)
        x=0;
    else if(x+playerSizeX>bgSizeX)
        x=bgSizeX-playerSizeX;
    _body->SetTransform(b2Vec2(x,playerPosY),0);
}
