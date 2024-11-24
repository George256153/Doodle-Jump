#include "reaction_change_image.h"

ReactionChangeImage::ReactionChangeImage(Reactor reactor, CounterEndEvent counterEndEvent, qreal interval)
    : reactor(reactor)
    , counterEndEvent(counterEndEvent)
    , counter(0)
{
    timer = new QTimer();
    if (timer) timer->setInterval(interval);
}

ReactionChangeImage::~ReactionChangeImage()
{
    if (timer)
    {
        delete timer;
        timer = nullptr;
    }
}


void ReactionChangeImage::react(GameObject *self, GameObject *target)
{
    if (reactor == Self) imageChanger = self;
    else if (reactor == Target) imageChanger = target;
    else return;

    if (!imageChanger) return;

//    if (counterEndEvent == Remove)
//    {
//        if (imageChanger) imageChanger->setBottomRight({0, 0}); // move away to avoid detection
//    }

    if (!timer->isActive())
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(changeImage()));
        if (reactor == Target && counterEndEvent == Repetition)
        {
            Player* player = dynamic_cast<Player*>(target);
            emit player->changeProfile();
            connect(player, SIGNAL(startDropping()), timer, SLOT(stop()));
            connect(player, SIGNAL(changeProfile()), timer, SLOT(stop()));
        }
        counter = 0;
        timer->start();
    }
}

void ReactionChangeImage::changeImage()
{
    if (!imageChanger) return;

    Player* player = dynamic_cast<Player*>(imageChanger);
    if (player)
    {
        if (counter < imagePathsForPlayer.size())
        {
            player->setProfileLeftPath(imagePathsForPlayer[counter].first);
            player->setProfileRightPath(imagePathsForPlayer[counter].second);
            counter++;
        }
        else if (counterEndEvent == Remove)
        {
            imageChanger->moveBottomRight( {0, 0} );
            timer->stop();
        }
        else if (counterEndEvent == Repetition)
        {
            counter = 0;
        }
    }
    else
    {
        if (counter < imagePaths.size())
        {
            if (imageChanger) imageChanger->setProfile(imagePaths[counter]);
            counter++;
        }
        else if (counterEndEvent == Remove)
        {
            timer->stop();
//            if (imageChanger) imageChanger->moveTopLeft({WINDOW_WIDTH, WINDOW_HEIGHT});
            if (imageChanger) imageChanger->moveBottomRight({0, 0});
        }
        else if (counterEndEvent == Repetition)
        {
            counter = 0;
        }
    }
}
