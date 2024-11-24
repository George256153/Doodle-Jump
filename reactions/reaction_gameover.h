#ifndef REACTIONGAMEOVER_H
#define REACTIONGAMEOVER_H

#include "reaction.h"
#include "player.h"

class ReactionGameover : public Reaction
{
public:
    ReactionGameover();

    // Reaction interface
public:
    void react(GameObject *self, GameObject *target) override;
};

#endif // REACTIONGAMEOVER_H
