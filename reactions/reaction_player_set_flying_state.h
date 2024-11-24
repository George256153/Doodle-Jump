#ifndef REACTIONPLAYERSETFLYINGSTATE_H
#define REACTIONPLAYERSETFLYINGSTATE_H

#include "reaction.h"
#include "player.h"

class ReactionPlayerSetFlyingState : public Reaction
{
public:
    ReactionPlayerSetFlyingState();
    void react(GameObject *self, GameObject *target) override;
};

#endif // REACTIONPLAYERSETFLYINGSTATE_H
