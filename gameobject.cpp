#include "gameobject.h"

GameObject::GameObject(QObject *parent, qreal x, qreal y, qreal width, qreal height)
    : QObject(parent)
    , QRectF(x, y, width, height)
//    , altitude(0)
{
    profile = nullptr;
    mover = nullptr;
}

GameObject::~GameObject()
{
    if (mover) delete mover;
    mover = nullptr;
    if (profile) delete profile;
    profile = nullptr;
}

void GameObject::setProfile(const QString &profilePath)
{
    if (!profile) profile = new QPixmap();
    profile->load(profilePath);
}

void GameObject::setProfile(QPixmap *newProfile)
{
    profile = newProfile;
}

void GameObject::paint(QPainter* painter)
{
    if (profile) painter->drawPixmap(left(), top(), *profile);
    //else qDebug() << Q_FUNC_INFO << "No profile";
}

void GameObject::update()
{
    if (mover) mover->move(this);
}

void GameObject::moveDown(qreal movement)
{
    moveTop(top() + movement);
    if (mover) // movable stairs
    {
        mover->setBoundary(
            mover->getTopBound() + movement,
            mover->getBottomBound() + movement
        );
    }
}
