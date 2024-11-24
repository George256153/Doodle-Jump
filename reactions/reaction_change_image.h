#ifndef REACTIONCHANGEIMAGE_H
#define REACTIONCHANGEIMAGE_H

#include "reaction.h"
#include "player.h"
#include <QObject>
#include <QTimer>
#include <QPixmap>
#include <QList>

enum Reactor {
    Self,
    Target
};

enum CounterEndEvent {
    Remove,
    Repetition
};

class ReactionChangeImage : public QObject, public Reaction
{
    Q_OBJECT

public:
    ReactionChangeImage(Reactor reactor, CounterEndEvent counterEndEvent, qreal interval);
    virtual ~ReactionChangeImage();
    void react(GameObject *self, GameObject *target) override;

    QList<QString> imagePaths;
    QList<QPair<QString, QString>> imagePathsForPlayer;

private slots:
    void changeImage();

private:
    QTimer *timer;
    Reactor reactor;
    CounterEndEvent counterEndEvent;
    GameObject *imageChanger;
    int counter;
};

#endif // REACTIONCHANGEIMAGE_H
