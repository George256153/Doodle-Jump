#ifndef REACTIONDECREASEHP_H
#define REACTIONDECREASEHP_H

#include "reaction.h"
#include "player.h"

class ReactionPlayerBeAttacked : public Reaction
{
public:
    ReactionPlayerBeAttacked();
    void react(GameObject *self, GameObject *target) override;
};

#endif // REACTIONDECREASEHP_H
