#include "block.h"

TBlock::TBlock(b2World *world, QImage *surface, const QPointF &position)
    : Surface(surface)
    , Image(QImage(blockImage))
    , Destroyed(false)
{
    b2BodyDef body;
    body.type = b2_staticBody;
    body.position.Set(0.1 * position.x(), 0.1 * position.y());
    body.angle = 0;
    Body=world->CreateBody(&body);
    b2CircleShape circle;
    circle.m_radius = 0.1 * blockSize / 2;
    b2FixtureDef fixture;
    fixture.shape = &circle;
    fixture.restitution = 1;
    fixture.friction = 0;
    Body->CreateFixture(&fixture);
    Body->SetAngularDamping(1);
    Body->SetLinearDamping(1);
    Body->SetUserData(this);
}

void TBlock::Destroy() {
    Destroyed = true;
}

void TBlock::Delete() {
    Body->GetWorld()->DestroyBody(Body);
    delete this;
}

void TBlock::Paint()
{
    QPainter painter(Surface);
    painter.drawImage(Body->GetPosition().x * 10, Body->GetPosition().y * 10 ,Image);
}

bool TBlock::IsDestroyed()
{
    return Destroyed;
}
