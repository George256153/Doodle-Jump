#include "mover.h"

Mover::Mover(qreal xVel, qreal yVel, qreal xAcc, qreal yAcc)
    : xVelocity(xVel)
    , yVelocity(yVel)
    , xAcceleration(xAcc)
    , yAcceleration(yAcc)
    , leftBound(0)
    , rightBound(0)
    , topBound(0)
    , bottomBound(0)
    , horizontal(none)
    , vertical(none)
{

}

void Mover::setVelocity(qreal newXVelocity, qreal newYVelocity)
{
    xVelocity = newXVelocity;
    yVelocity = newYVelocity;
}

void Mover::setAcceleration(qreal newXAcceleration, qreal newYAcceleration)
{
    xAcceleration = newXAcceleration;
    yAcceleration = newYAcceleration;
}

void Mover::setBoundary(qreal newTopBound, qreal newBottomBound, qreal newLeftBound, qreal newRightBound)
{
    topBound = newTopBound;
    bottomBound = newBottomBound;
    leftBound = newLeftBound;
    rightBound = newRightBound;
}

void Mover::setBoundary(qreal newTopBound, qreal newBottomBound)
{
    topBound = newTopBound;
    bottomBound = newBottomBound;
}

void Mover::setBoundaryReaction(BoundaryReaction newHorizontal, BoundaryReaction newVertical)
{
    horizontal = newHorizontal;
    vertical = newVertical;
}

qreal Mover::xVel() const
{
    return xVelocity;
}

qreal Mover::yVel() const
{
    return yVelocity;
}

qreal Mover::xAcc() const
{
    return xAcceleration;
}

qreal Mover::yAcc() const
{
    return yAcceleration;
}

void Mover::move(QRectF *moved)
{
    moved->moveLeft(moved->left() + xVelocity);         // horizontal move by xVel
    moved->moveTop(moved->top() + yVelocity);           // vertical move by yVel

    xVelocity += xAcceleration;
    yVelocity += yAcceleration;

    boundaryProcessing(moved);
}

qreal Mover::getTopBound() const
{
    return topBound;
}

qreal Mover::getBottomBound() const
{
    return bottomBound;
}

qreal Mover::getRightBound() const
{
    return rightBound;
}

qreal Mover::getLeftBound() const
{
    return leftBound;
}

BoundaryReaction Mover::getHorizontal() const
{
    return horizontal;
}

BoundaryReaction Mover::getVertical() const
{
    return vertical;
}

void Mover::boundaryProcessing(QRectF* target)
{
    switch (horizontal) {
        case none:
            break;

        case rebound:
            if (target->left() <= leftBound || target->right() >= rightBound) xVelocity *= -1;
            break;

        case passThrough:
            if (target->right() <= leftBound)
                target->moveLeft(rightBound - target->width() / 2);

            else if (target->left() >= rightBound)
                target->moveRight(leftBound + target->width() / 2);
            break;

        default:
            break;
    }

    switch (vertical) {
        case none:
            break;

        case rebound:
            if (target->top() <= topBound || target->bottom() >= bottomBound) yVelocity *= -1;
            break;

        case passThrough:
            if (target->bottom() <= topBound)
                target->moveTop(bottomBound - target->height() / 2);

            else if (target->top() >= bottomBound)
                target->moveBottom(topBound + target->width() / 2);
            break;

        default:
            break;
    }
}
