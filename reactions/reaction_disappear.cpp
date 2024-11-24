#include "reaction_disappear.h"

ReactionDisappear::ReactionDisappear()
{

}


void ReactionDisappear::react(GameObject *self, GameObject *target)
{
    Q_UNUSED(target);
//    self->moveBottomRight( {0, 0} );
    if (!self) return;
    self->moveTopLeft( {WINDOW_WIDTH, WINDOW_HEIGHT});
}

