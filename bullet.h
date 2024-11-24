#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"
#include "mover.h"
#include "constants.h"
#include <QPointF>
#include <QTimer>

class Bullet : public GameObject
{
    Q_OBJECT
public:
    explicit Bullet(QObject *parent = nullptr, qreal x = 0, qreal y = 0, qreal width = BULLET_WIDTH, qreal height = BULLET_HEIGHT);
    virtual ~Bullet();

    void setTarget(QPoint shooted);

public slots:
    void emitTo(QPoint shooted);

private:
    QTimer *timer;
};

#endif // BULLET_H
