#include "detection_landing.h"

DetectionLanding::DetectionLanding()
{

}

bool DetectionLanding::detected(GameObject *self, GameObject *target)
{
//    qDebug() << "landing:" << "start for self =" << self;
    if (!self)
    {
//        qDebug() << "landing:" << "self is a nullptr";
        return false;
    }

    Player* player = dynamic_cast<Player*>(target);

    qreal yVel = (self->mover) ? self->mover->yVel() : 0;

//    qDebug() << "landing:" << "before the if (self =" << self;
    if (self->intersects(*player)
        && player->bottom() >= self->top() && player->bottom() < self->bottom()
        && player->bottom() - player->mover->yVel() < self->top() - yVel)
    {
//        qDebug() << Q_FUNC_INFO << "Player is landing";
//        qDebug() << "landing:" << "enter the if (self =" << self;
        return true;
    }
//    qDebug() << "landing:" << "pass the if (self =" << self;
    return false;
}



//bool TouchExceptLanding::detect(GameObject *self, GameObject *target)
//{
//    return self->intersects(*target) && !topDetectRule.detect(self, target);
//}
