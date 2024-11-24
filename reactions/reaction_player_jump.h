#ifndef REACTION_PLAYER_JUMP_H
#define REACTION_PLAYER_JUMP_H

#include "reaction.h"
#include "player.h"

class ReactionPlayerJump : public Reaction
{
public:
    ReactionPlayerJump(qreal jumpHeight);
    void react(GameObject *self, GameObject *target) override;

private:
    qreal jumpHeight;
};

#endif // REACTIONPLAYERJUMP_H
