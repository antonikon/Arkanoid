#include "ball.h"

Ball::Ball(b2World *world, QImage *surface):
    _surface(surface),
    _image(QImage(ballImage))
{
    b2BodyDef body;
    body.type=b2_dynamicBody;
    body.position.Set(ballX,ballY);
    body.angle=0;
    _body=world->CreateBody(&body);
    b2CircleShape circle;
    circle.m_radius=ballSize;
    b2FixtureDef fixture;
    fixture.shape=&circle;
    fixture.restitution=1;
    fixture.friction=0;
    _body->CreateFixture(&fixture);
    _body->SetLinearVelocity(b2Vec2(0,50));
    _body->SetAngularDamping(1);
}

void Ball::paint()
{
    QPainter painter(_surface);
    painter.drawImage(_body->GetPosition().x,_body->GetPosition().y,_image);
    //qDebug() << abs(_body->GetLinearVelocity().x)+abs(_body->GetLinearVelocity().y);
}

void Ball::update()
{
    if (abs(_body->GetLinearVelocity().x)+abs(_body->GetLinearVelocity().y)-40<0)
        _body->SetLinearVelocity(b2Vec2(-_speed.x,-_speed.y));
    else
        _speed=_body->GetLinearVelocity();
}

bool Ball::gameOver()
{
    if (_body->GetPosition().y>bgSizeY)
        return true;
    else
        return false;
}
