#ifndef REACTION_DISAPPEAR_H
#define REACTION_DISAPPEAR_H

#include "reaction.h"

class ReactionDisappear : public Reaction
{
public:
    ReactionDisappear();
    void react(GameObject *self, GameObject *target = nullptr) override;
};

#endif // REACTION_DISAPPEAR_H
