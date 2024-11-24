#include "reaction_player_be_attacked.h"

ReactionPlayerBeAttacked::ReactionPlayerBeAttacked()
{

}

void ReactionPlayerBeAttacked::react(GameObject *self, GameObject *target)
{
    Q_UNUSED(self);
    Player* player = dynamic_cast<Player*>(target);
    if (player)
    {
        player->beAttacked();
    }
}
