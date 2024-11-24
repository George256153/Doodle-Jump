#ifndef REACTIONPLAYERSHIELDED_H
#define REACTIONPLAYERSHIELDED_H

#include "reaction.h"
#include "player.h"

class ReactionPlayerShielded : public Reaction
{
public:
    ReactionPlayerShielded();

    // Reaction interface
public:
    void react(GameObject *self, GameObject *target) override;
};

#endif // REACTIONPLAYERSHIELDED_H
