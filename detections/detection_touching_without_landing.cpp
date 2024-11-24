#include "detection_touching_without_landing.h"

DetectionTouchingWithoutLanding::DetectionTouchingWithoutLanding()
{
    detectionLanding = new DetectionLanding();
    detectionTouching = new DetectionTouching();
}

bool DetectionTouchingWithoutLanding::detected(GameObject *self, GameObject *target)
{
    if (!self) return false;
    return detectionTouching->detected(self, target) && !detectionLanding->detected(self, target);
}
