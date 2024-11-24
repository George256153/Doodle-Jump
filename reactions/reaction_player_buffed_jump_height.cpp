#include "reaction_player_buffed_jump_height.h"

ReactionPlayerBuffedJumpHeight::ReactionPlayerBuffedJumpHeight()
    : player(nullptr)
    , timer(nullptr)
{
    timer = new QTimer();
}


void ReactionPlayerBuffedJumpHeight::react(GameObject *self, GameObject *target)
{
    Q_UNUSED(self);
    player = dynamic_cast<Player*>(target);
    if (player)
    {
        player->defaultJumpHeight = 2000;
        timer->singleShot(SPRING_SHOES_DURATION, this, &ReactionPlayerBuffedJumpHeight::resetPlayerJumpHeight);
    }
}

void ReactionPlayerBuffedJumpHeight::resetPlayerJumpHeight()
{
    player->defaultJumpHeight = PLAYER_BASIC_JUMP_HEIGHT;
    if (player->playerState != PlayerState::Flying)
    {
        player->setProfileLeftPath(":/dataset/images/doodleL.png");
        player->setProfileRightPath(":/dataset/images/doodleR.png");
    }
}
