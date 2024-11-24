#ifndef DETECTIONTOUCHINGWITHOUTLANDING_H
#define DETECTIONTOUCHINGWITHOUTLANDING_H

#include "detection.h"
#include "detection_touching.h"
#include "detection_landing.h"

class DetectionTouchingWithoutLanding : public Detection
{
public:
    DetectionTouchingWithoutLanding();
    bool detected(GameObject *self, GameObject *target) override;

private:
    DetectionLanding *detectionLanding;
    DetectionTouching *detectionTouching;
};

#endif // DETECTIONTOUCHINGWITHOUTLANDING_H
