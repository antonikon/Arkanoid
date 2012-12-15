#include "ball.h"

TBall::TBall(b2World *world, QImage *surface):
    Surface(surface),
    Image(QImage(ballImage))
{
    b2BodyDef body;
    body.type=b2_dynamicBody;
    body.position.Set(0.1*ballX, 0.1*ballY);
    body.angle=0;
    Body=world->CreateBody(&body);
    b2CircleShape circle;
    circle.m_radius=0.1*ballSize;
    b2FixtureDef fixture;
    fixture.shape=&circle;
    fixture.restitution=1;
    fixture.friction=0;
    Body->CreateFixture(&fixture);
    Body->SetLinearVelocity(b2Vec2(6, -25));
    Body->SetAngularDamping(1);
}

void TBall::Paint()
{
    QPainter painter(Surface);
    painter.drawImage(Body->GetPosition().x * 10, Body->GetPosition().y * 10, Image);
}

bool TBall::GameOver()
{
    if (Body->GetPosition().y > 0.1 * bgSizeY)
        return true;
    else
        return false;
}
