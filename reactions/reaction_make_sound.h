#ifndef REACTIONMAKESOUND_H
#define REACTIONMAKESOUND_H

#include "reaction.h"
#include <QSound>

class ReactionMakeSound : public Reaction
{
public:
    ReactionMakeSound(QString mediaFilePath, int volume = 80);
    void react(GameObject *self, GameObject *target = nullptr) override;
private:
    QString mediaFilePath;
};

#endif // REACTIONMAKESOUND_H
