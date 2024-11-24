#include "bullet.h"
#include <QDebug>
#include <QtMath>

Bullet::Bullet(QObject *parent, qreal x, qreal y, qreal width, qreal height)
    : GameObject(parent, x, y, width, height)
{
    mover = new Mover();
    mover->setBoundary(0, WINDOW_HEIGHT, 0, WINDOW_WIDTH);
//    mover->setBoundaryReaction(BoundaryReaction::rebound, BoundaryReaction::rebound);
    mover->setBoundaryReaction(BoundaryReaction::none, BoundaryReaction::none);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Bullet::update);

    setProfile(":/dataset/images/bullet.png");
}

Bullet::~Bullet()
{

}

void Bullet::emitTo(QPoint shooted)
{
    QPointF diff = shooted - topLeft();
    qreal length = QPointF::dotProduct(diff, diff);
    length = qSqrt(length);
    mover->setVelocity(diff.x() / length * BULLET_STEP, diff.y() / length * BULLET_STEP);

    timer->start(50);
}

