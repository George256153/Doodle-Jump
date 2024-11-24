#ifndef REACTION_H
#define REACTION_H

#include "gameobject.h"

class Reaction
{
public:
    Reaction();

    virtual void react(GameObject *self, GameObject *target = nullptr) = 0;
};

#endif // REACTION_H
