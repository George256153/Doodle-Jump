#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QRectF>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QList>

#include "mover.h"

class GameObject : public QObject, public QRectF
{
    Q_OBJECT

public:
    explicit GameObject(QObject *parent = nullptr, qreal x = 0, qreal y = 0, qreal width = 0, qreal height = 0);
    virtual ~GameObject();
    virtual void paint(QPainter* painter);
    void setProfile(const QString& profilePath);
    void setProfile(QPixmap *newProfile);
    Mover *mover;

public slots:
    virtual void update();
    virtual void moveDown(qreal movement);

protected:
    QPixmap *profile;
//    qreal altitude;
};

#endif // GAMEOBJECT_H
