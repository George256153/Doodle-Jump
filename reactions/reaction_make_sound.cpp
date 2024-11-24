#include "reaction_make_sound.h"

ReactionMakeSound::ReactionMakeSound(QString mediaFilePath, int volume)
    : mediaFilePath(mediaFilePath)
{
}

void ReactionMakeSound::react(GameObject *self, GameObject *target)
{
   QSound::play(mediaFilePath);
}
