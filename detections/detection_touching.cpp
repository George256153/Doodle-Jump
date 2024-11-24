#include "detection_touching.h"

DetectionTouching::DetectionTouching()
{

}


bool DetectionTouching::detected(GameObject *self, GameObject *target)
{
    if (!self) return false;
    return (self->intersects(*target));
}
