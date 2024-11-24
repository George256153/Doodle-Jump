#include "reaction_player_set_flying_state.h"

ReactionPlayerSetFlyingState::ReactionPlayerSetFlyingState()
{

}

void ReactionPlayerSetFlyingState::react(GameObject *self, GameObject *target)
{
    Player* player = dynamic_cast<Player*>(target);
    if (player)
    {
        player->playerState = PlayerState::Flying;
    }
}
