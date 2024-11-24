#ifndef DETECTIONENTERWINDOW_H
#define DETECTIONENTERWINDOW_H

#include "detection.h"

class DetectionEnterWindow : public Detection
{
public:
    DetectionEnterWindow();

    // Detection interface
public:
    bool detected(GameObject *self, GameObject *target) override;
};

#endif // DETECTIONENTERWINDOW_H
