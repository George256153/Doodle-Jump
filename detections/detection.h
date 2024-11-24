#ifndef DETECTION_H
#define DETECTION_H

#include "gameobject.h"
#include "player.h"
#include "bullet.h"

class Detection
{
public:
    Detection();

    virtual bool detected(GameObject *self, GameObject *target) = 0;
};

#endif // DETECTION_H
