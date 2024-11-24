#include "reaction_player_jump.h"

ReactionPlayerJump::ReactionPlayerJump(qreal jumpHeight)
    : jumpHeight(jumpHeight)
{

}


void ReactionPlayerJump::react(GameObject *self, GameObject *target)
{
    Q_UNUSED(self);
    Player* player = dynamic_cast<Player*>(target);
    if (player)
    {
        if (jumpHeight == -1)
        {
            player->jump(player->defaultJumpHeight);                     // player jumps
        }
        else {
            player->jump(jumpHeight);                     // player jumps
        }
    }
//    else qDebug() << Q_FUNC_INFO << "Not a Player";
}
