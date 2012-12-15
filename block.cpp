#include "block.h"

Block::Block(b2World *world, QImage *surface, const QPointF &position):
    _surface(surface),
    _image(QImage(blockImage)),
    _isDestroy(false)
{
    b2BodyDef body;
    body.type=b2_dynamicBody;
    body.position.Set(position.x(),position.y());
    body.angle=0;
    _body=world->CreateBody(&body);
    b2CircleShape circle;
    circle.m_radius=blockSize/2;
    b2FixtureDef fixture;
    fixture.shape=&circle;
    fixture.restitution=1;
    fixture.friction=0;
    _body->CreateFixture(&fixture);
    _body->SetAngularDamping(1);
    _body->SetLinearDamping(1);
}

void Block::paint()
{
    QPainter painter(_surface);
    painter.drawImage(_body->GetPosition().x,_body->GetPosition().y,_image);
}

void Block::update()
{
    if (abs(_body->GetLinearVelocity().x)+abs(_body->GetLinearVelocity().y)!=0)
    {
        _body->GetWorld()->DestroyBody(_body);
        _isDestroy=true;
    }
}

bool Block::isDestroy()
{
    return _isDestroy;
}
