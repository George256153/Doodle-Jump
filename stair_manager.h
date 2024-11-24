#ifndef STAIRMANAGER_H
#define STAIRMANAGER_H

#include <QObject>
#include <QPainter>
//#include <QRandomGenerator>

#include "constants.h"
#include "gameobject.h"
#include "player.h"
#include "bullet.h"
#include "detector.h"
#include "reactions/reaction_change_image.h"
#include "reactions/reaction_make_sound.h"

class StairCategory
{
public:
    enum stairCategory
    {
        Basic,
        Broken,
        HorizontalMoving,   // 6000
        Disappearing,       // 9000
        VerticalMoving,     // 12000 ?
        Thorn,
        Countdown,
        numStairCategory
    };
};

class MantainedCategory : public StairCategory
{
public:
    enum mantainedCategory
    {
        Item = StairCategory::stairCategory::numStairCategory + 1,
        Monster,
        numMaintainedCategory
    };
};

//enum ItemCategory {
//    Spring,
//    Trampoline,
//    PropellerHat,
//    JetPack
//};

class StairManager : public QObject
{
    Q_OBJECT
public:
    explicit StairManager(QObject *parent = nullptr, bool hasItems = true, bool hasMonsters = true);
    virtual ~StairManager();

    void paintStairs(QPainter *painter);
    qreal getViewMovement() const;
    void setViewMovement(qreal newViewMovement);

    QVector<QPair<Detector*, int>> stairs;
    bool hasItems;
    bool hasMonsters;

public slots:
    void viewDown(qreal movement);

signals:
    void makeDetectionTo(GameObject* detected);
    void update();

private:
    void addStairsUntil(qreal targetAltitude);
    void maintainStairsUntil(qreal nextStairAltitude);
    void maintainAppearance(qreal nextStairAltitude, int stairCategory, qreal unlockAltitude, qreal appearingPeriod);

    /* create stairs */
    Detector* createStair(qreal left, qreal top, qreal width = STAIR_WIDTH, qreal height = STAIR_HEIGHT);
    Detector* createBasicStair(qreal left, qreal top);
    Detector* createDisappearingStair(qreal left, qreal top);
    Detector* createHorizontalMoveStair(qreal left, qreal top);
    Detector* createBrokenStair(qreal left, qreal top, qreal width = STAIR_WIDTH, qreal height = STAIR_HEIGHT);
    // bonus
    Detector* createVerticalMoveStair(qreal left, qreal top);
    Detector* createThornStair(qreal left, qreal top);
    Detector* createCountdowStair(qreal left, qreal top);

    /* create items */
    Detector* createSpring(qreal left, qreal top, qreal width = SPRING_WIDTH, qreal height = SPRING_HEIGHT);
    Detector* createTrampoline(qreal left, qreal top, qreal width = TRAMPOLINE_WIDTH, qreal height = TRAMPOLINE_HEIGHT);
    Detector* createPropellerHat(qreal left, qreal top, qreal width = PROPELLER_HAT_WIDTH, qreal height = PROPELLER_HAT_HEIGHT);
    Detector* createJetpack(qreal left, qreal top, qreal width = JETPACK_WIDTH, qreal height = JETPACK_HEIGHT);
    // bonus
    Detector* createSpringShoes(qreal left, qreal top, qreal width = SPRING_SHOES_WIDTH, qreal height = SPRING_SHOES_HEIGHT);
    Detector* createShield(qreal left, qreal top, qreal width = SHIELD_WIDTH, qreal height = SHIELD_HEIGHT);
    Detector* createBlackHole(qreal left, qreal top, qreal width = 150, qreal height = 135);

    Detector* getRandomItem(int replacedIdx);

    /* create monster (uniformly random) */
    Detector* createMonsterOn(Detector *stair);

    // redundant
    Detector* createSelfDeletingDetector(qreal left, qreal top, qreal width, qreal height);
    QVector<Reaction*> reactionList;

    // private member
    qreal viewMovement;
    QVector<int> maintainedIndices;
};

#endif // STAIRMANAGER_H
