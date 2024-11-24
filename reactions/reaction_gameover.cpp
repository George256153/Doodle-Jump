#include "reaction_gameover.h"

ReactionGameover::ReactionGameover()
{

}


void ReactionGameover::react(GameObject *self, GameObject *target)
{
    Q_UNUSED(self);
    Player* player = dynamic_cast<Player*>(target);
    if (player)
    {
        emit player->reachBottomBoundary();
    }
}
