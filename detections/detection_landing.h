#ifndef DETECTION_LANDING_H
#define DETECTION_LANDING_H

#include <QDebug>
#include "detection.h"
#include "player.h"

class DetectionLanding : public Detection
{
public:
    DetectionLanding();

    // Detection interface
public:
    bool detected(GameObject *self, GameObject *target) override;
};

#endif // DETECTION_LANDING_H
