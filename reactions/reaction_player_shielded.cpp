#include "reaction_player_shielded.h"

ReactionPlayerShielded::ReactionPlayerShielded()
{

}


void ReactionPlayerShielded::react(GameObject *self, GameObject *target)
{
    Q_UNUSED(self);
    Player* player = dynamic_cast<Player*>(target);
    if (player)
    {
        player->setShielded();
        player->resetShieldedAfter(5000);
    }
}
