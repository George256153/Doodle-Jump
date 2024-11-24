#ifndef MOVER_H
#define MOVER_H

#include <QRectF>

#include "constants.h"

enum BoundaryReaction {
    none,
    rebound,
    passThrough
};

class Mover
{
public:
    Mover(qreal xVel = 0, qreal yVel = 0, qreal xAcc = 0, qreal yAcc = 0);
//    Mover(const Mover& newMover);

    void setVelocity(qreal newXVelocity, qreal newYVelocity);
    void setAcceleration(qreal newXAcceleration, qreal newYAcceleration);
    void setBoundary(qreal newTopBound, qreal newBottomBound, qreal newLeftBound, qreal newRightBound);
    void setBoundary(qreal newTopBound, qreal newBottomBound);
    void setBoundaryReaction(BoundaryReaction horizontal, BoundaryReaction vertical);

    qreal xVel() const;
    qreal yVel() const;
    qreal xAcc() const;
    qreal yAcc() const;

public:
    void move(QRectF* moved);

    qreal getTopBound() const;
    qreal getBottomBound() const;

    qreal getRightBound() const;
    qreal getLeftBound() const;

    BoundaryReaction getHorizontal() const;
    BoundaryReaction getVertical() const;

private:
    qreal xVelocity;
    qreal yVelocity;
    qreal xAcceleration;
    qreal yAcceleration;

    /* Boundary detection */
    qreal leftBound;
    qreal rightBound;
    qreal topBound;
    qreal bottomBound;
    BoundaryReaction horizontal;
    BoundaryReaction vertical;

    void boundaryProcessing(QRectF* target);
};

#endif // MOVER_H
