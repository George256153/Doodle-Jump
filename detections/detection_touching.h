#ifndef DETECTIONTOUCHING_H
#define DETECTIONTOUCHING_H

#include "detection.h"
#include <QDebug>

class DetectionTouching : public Detection
{
public:
    DetectionTouching();
    bool detected(GameObject *self, GameObject *target) override;

};

#endif // DETECTIONTOUCHING_H
