#include "detector.h"

Detector::Detector(QObject *parent, qreal x, qreal y, qreal width, qreal height)
    : GameObject(parent, x, y, width, height)
{
    passenger = nullptr;
    timer = nullptr;
}

Detector::~Detector()
{
    if (passenger)
    {
        if (passenger->mover)
        {
            passenger->mover = nullptr; // set to nullptr before delete to avoid multiple deletion on same mover
        }
        delete passenger;
    }
    passenger = nullptr;
    if (timer) delete timer;
    timer = nullptr;
}

void Detector::detectTo(GameObject *target)
{
    QString targetClassName = typeid(*target).name();

    for (Detection* detection : rules[targetClassName].keys())
    {
        if (!detection || detection->detected(this, target))
        {
            for (Reaction* reaction : rules[targetClassName][detection])
            {
                reaction->react(this, target);
            }
        }
    }
}

void Detector::moveDown(qreal movement)
{
    GameObject::moveDown(movement);
    if (passenger) passenger->moveDown(movement);
}

bool Detector::hasPassenger() const
{
    return (passenger != nullptr);
}

void Detector::moveTop(qreal pos)
{
    qreal dy = pos - top();
    GameObject::moveTop(pos);
    if (passenger) passenger->moveTop(passenger->top() + dy);
}

void Detector::moveLeft(qreal pos)
{
    qreal dx = pos - left();
    GameObject::moveLeft(pos);
    if (passenger) passenger->moveLeft(passenger->left() + dx);
}

void Detector::setPassenger(Detector *newPassenger)
{
    passenger = newPassenger;
}

void Detector::addRule(Detection *detection, Reaction *reaction, QString targetClassName)
{
    rules[targetClassName][detection].push_back( reaction );
}


void Detector::paint(QPainter *painter)
{
    GameObject::paint(painter);                 // paint itself
    if (passenger) {
        passenger->paint(painter);   // paint the passenger
    }
}

void Detector::update()
{
    GameObject::update();
    if (passenger) passenger->update();
}
