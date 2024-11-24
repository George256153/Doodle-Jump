#ifndef REACTIONPLAYERBUFFEDJUMPHEIGHT_H
#define REACTIONPLAYERBUFFEDJUMPHEIGHT_H

#include "reaction.h"
#include "player.h"
#include <QObject>
#include <QTimer>

class ReactionPlayerBuffedJumpHeight : public QObject, public Reaction
{
    Q_OBJECT

public:
    ReactionPlayerBuffedJumpHeight();

    // Reaction interface
public:
    void react(GameObject *self, GameObject *target) override;

public slots:
    void resetPlayerJumpHeight();

private:
    Player *player;
    QTimer *timer;
};

#endif // REACTIONPLAYERBUFFEDJUMPHEIGHT_H
