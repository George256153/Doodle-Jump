#include "detection_enter_window.h"

DetectionEnterWindow::DetectionEnterWindow()
{

}


bool DetectionEnterWindow::detected(GameObject *self, GameObject *target)
{
    Q_UNUSED(target);
    if (!self) return false;
    if (self->top() > 20)
    {
        return true;
    }
    return false;
}
