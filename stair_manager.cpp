#include "stair_manager.h"
#include "rule_instances.h"

StairManager::StairManager(QObject *parent, bool hasItems, bool hasMonsters)
    : QObject(parent)
    , hasItems(hasItems)
    , hasMonsters(hasMonsters)
    , viewMovement(0)
{
    maintainedIndices = QVector<int>(MantainedCategory::numMaintainedCategory, 1); // the 0-th stair must be basic stair and not replacable
    addStairsUntil(WINDOW_HEIGHT * 2);
}

void StairManager::addStairsUntil(qreal targetAltitude)
{
    // the lowest stair must be a basic stair with fixed size
    if (stairs.size() == 0)
    {
        Detector* firstStair = createBasicStair(200, WINDOW_HEIGHT - STAIR_HEIGHT - 40);
//        Detector* firstStair = createCountdowStair(200, WINDOW_HEIGHT - STAIR_HEIGHT - 40);
        stairs.push_back( {firstStair, StairCategory::Basic} );

    }
    // add stairs until the altitude of the highest stair is larger than the target altitude
    qreal highestAltitude = WINDOW_HEIGHT - stairs.back().first->top() + viewMovement;
    while (highestAltitude < targetAltitude)
    {
        qreal nextStairAltidude = highestAltitude + 60 + (rand() % 210);
        qreal nextStairLeft = rand() % (WINDOW_WIDTH - STAIR_WIDTH);

        if (stairs.size()) maintainStairsUntil(nextStairAltidude);

        qreal nextStairTop = WINDOW_HEIGHT - (nextStairAltidude - viewMovement);
        stairs.push_back( {createBasicStair(nextStairLeft, nextStairTop), StairCategory::Basic} );
        highestAltitude = nextStairAltidude;
    }
}

void StairManager::maintainStairsUntil(qreal nextStairAltitude)
{
    /* maintain the apperance of H-moving stair */
    maintainAppearance(nextStairAltitude, MantainedCategory::HorizontalMoving, H_MOVE_STAIR_UNLOCK_ALTITUDE, H_MOVE_STAIR_APPEAR_INTERVAL);

    /* maintain the apperance of V-moving stair */
    maintainAppearance(nextStairAltitude, MantainedCategory::VerticalMoving, V_MOVE_STAIR_UNLOCK_ALTITUDE, V_MOVE_STAIR_APPEAR_INTERVAL);

    /* maintain the apperance of broken stair */
    maintainAppearance(nextStairAltitude, MantainedCategory::Broken, BROKEN_STAIR_UNLOCK_ALTITUDE, BROKEN_STAIR_APPEAR_INTERVAL);

    /* maintain the apperance of Disappearing stair */
    maintainAppearance(nextStairAltitude, MantainedCategory::Disappearing, DISAPPEARING_STAIR_UNLOCK_ALTITUDE, DISAPPEARING_STAIR_APPEAR_INTERVAL);

    /* maintain the apperance of Thorn stair */
    maintainAppearance(nextStairAltitude, MantainedCategory::Thorn, THORN_STAIR_UNLOCK_ALTITUDE, THORN_STAIR_APPEAR_INTERVAL);

    /* maintain the apperance of Countdown stair */
    maintainAppearance(nextStairAltitude, MantainedCategory::Countdown, COUNTDOWN_STAIR_UNLOCK_ALTITUDE, COUNTDOWN_STAIR_APPEAR_INTERVAL);

    /* maintain the apperance of item */
    if (hasItems) maintainAppearance(nextStairAltitude, MantainedCategory::Item, ITEM_UNLOCK_ALTITUDE, ITEM_APPEAR_INTERVAL);

    /* maintain the apperance of monster */
    if (hasMonsters) maintainAppearance(nextStairAltitude, MantainedCategory::Monster, MONSTER_UNLOCK_ALTITUDE, MONSTER_APPEAR_INTERVAL);
}

void StairManager::maintainAppearance(qreal nextStairAltitude, int maintainedCategory, qreal unlockAltitude, qreal appearingPeriod)
{
    qreal highestAltitude = (stairs.size() ? WINDOW_HEIGHT - stairs.back().first->top() + viewMovement : 0);
    if (highestAltitude < unlockAltitude && nextStairAltitude >= unlockAltitude)
    {
        maintainedIndices[maintainedCategory] = stairs.size();
    }
    else if (highestAltitude >= unlockAltitude && nextStairAltitude >= unlockAltitude
             && qFloor( (highestAltitude - unlockAltitude) / appearingPeriod )
             != qFloor( (nextStairAltitude - unlockAltitude) / appearingPeriod ))
    {
        int replacedIdx;
        Detector* replacedStair;
        bool isDeleteReplacedStair = true;
        qreal prevStairTop;
        qreal nextStairTop;

        do {
            replacedIdx = maintainedIndices[maintainedCategory]
                        + rand() % (stairs.size() - 1 - maintainedIndices[maintainedCategory]);
        } while(stairs[replacedIdx].second != StairCategory::Basic || (!stairs[replacedIdx].first));

        replacedStair = stairs[replacedIdx].first; // be replaced

        switch (maintainedCategory) {
        case MantainedCategory::Broken:
//            prevStairTop = (stairs[replacedIdx - 1].first ? stairs[replacedIdx - 1].first->top() : 0);
//            nextStairTop = (stairs[replacedIdx + 1].first ? stairs[replacedIdx + 1].first->top() : 0);
            prevStairTop = stairs[replacedIdx - 1].first->top();
            nextStairTop = stairs[replacedIdx + 1].first->top();
            if (prevStairTop - nextStairTop > PLAYER_BASIC_JUMP_HEIGHT)
            {
                stairs[replacedIdx].first->moveTop(prevStairTop - 250);
                qreal brokenStairLeft = rand() % (WINDOW_WIDTH - STAIR_WIDTH);
                // insert Broken stair
                stairs.insert(
                    replacedIdx,
                    {createBrokenStair(brokenStairLeft, prevStairTop - 100) , maintainedCategory}
                );
                isDeleteReplacedStair = false;
            }
            else
            {
                stairs[replacedIdx].first = createBrokenStair(stairs[replacedIdx].first->left(), stairs[replacedIdx].first->top());
                stairs[replacedIdx].second = maintainedCategory;
            }
            break;

        case MantainedCategory::HorizontalMoving:
            stairs[replacedIdx].first = createHorizontalMoveStair(stairs[replacedIdx].first->left(), stairs[replacedIdx].first->top());
            stairs[replacedIdx].second = maintainedCategory;
            break;

        case MantainedCategory::VerticalMoving:
            if (replacedIdx < stairs.size())
            {
                stairs[replacedIdx].first = createVerticalMoveStair(stairs[replacedIdx].first->left(), stairs[replacedIdx].first->top());
                stairs[replacedIdx].second = maintainedCategory;

                for (int i = replacedIdx + 1; (i < replacedIdx + 4) && (i < stairs.size()); i++)
                {
                    qreal randomBias = rand() % 80;
                    if(stairs[i].first)
                    {
                        if ( (stairs[i].first->left() >= stairs[replacedIdx].first->left()
                              && stairs[i].first->left() <= stairs[replacedIdx].first->right())
                             || (stairs[i].first->right() >= stairs[replacedIdx].first->left()
                                 && stairs[i].first->right() <= stairs[replacedIdx].first->right()) )
                        {
                            stairs[i].first->moveLeft(randomBias + 10 +
                                ((stairs[replacedIdx].first->left() < WINDOW_WIDTH / 2 - STAIR_WIDTH) ? WINDOW_WIDTH / 2 : 0)
                            );
                        }
                    }
                }
            }
            break;

        case MantainedCategory::Disappearing:
            stairs[replacedIdx].first = createDisappearingStair(stairs[replacedIdx].first->left(), stairs[replacedIdx].first->top());
            stairs[replacedIdx].second = maintainedCategory;
            break;

        case MantainedCategory::Thorn:
            stairs[replacedIdx].first = createThornStair(stairs[replacedIdx].first->left(), stairs[replacedIdx].first->top());
            stairs[replacedIdx].second = maintainedCategory;
            break;

        case MantainedCategory::Countdown:
            stairs[replacedIdx].first = createCountdowStair(stairs[replacedIdx].first->left(), stairs[replacedIdx].first->top());
            stairs[replacedIdx].second = maintainedCategory;
            break;

        case MantainedCategory::Item:
            if (stairs[replacedIdx].second == MantainedCategory::Basic
                || stairs[replacedIdx].second == MantainedCategory::HorizontalMoving
                || stairs[replacedIdx].second == MantainedCategory::VerticalMoving)
            {
                if (!stairs[replacedIdx].first->hasPassenger())
                {
                    Detector *item = getRandomItem(replacedIdx);
                    item->mover = stairs[replacedIdx].first->mover;
                    stairs[replacedIdx].first->setPassenger(item);
                }
            }
            isDeleteReplacedStair = false;
            break;

        case MantainedCategory::Monster:
            if (stairs[replacedIdx].second == MantainedCategory::Basic
                || stairs[replacedIdx].second == MantainedCategory::HorizontalMoving
                || stairs[replacedIdx].second == MantainedCategory::VerticalMoving)
            {
                if (!stairs[replacedIdx].first->hasPassenger())
                {
                    Detector *monster = createMonsterOn(stairs[replacedIdx].first);
                    monster->mover = stairs[replacedIdx].first->mover;
                    stairs[replacedIdx].first->setPassenger(monster);
                }
            }
            isDeleteReplacedStair = false;
            break;

        default:
            break;
        }

        if (isDeleteReplacedStair && replacedStair)
        {
            delete replacedStair;
            replacedStair = nullptr;
        }

        maintainedIndices[maintainedCategory] = stairs.size();
//        maintainedIndices[maintainedCategory] = replacedIdx + 1;
    }
}

Detector* StairManager::getRandomItem(int replacedIdx)
{
    if (!stairs[replacedIdx].first) return nullptr;

    Detector *item = nullptr;
    qreal altitude = WINDOW_HEIGHT - stairs[replacedIdx].first->top() + viewMovement;
    int numItemChoices;
    if (altitude < 4000) numItemChoices = 1;        // 3000~4000: only spring
    else if (altitude < 5000) numItemChoices = 2;   // 4000: add shield
    else if (altitude < 6000) numItemChoices = 3;   // 5000: add springshoes
    else if (altitude < 7500) numItemChoices = 4;   // 6000: add trampoline
    else if (altitude < 9000) numItemChoices = 5;   // 7500: add blackhole
    else if (altitude < 12000) numItemChoices = 6;  // 9000: add propeller-hat,
    else numItemChoices = 7;                        // 12000: add jet-pack

    int itemChoice = -1;
    int randomChoice;
    for (size_t i = 0; i < 2; i++)
    {
        randomChoice = rand() % numItemChoices;
        if (randomChoice > itemChoice) itemChoice = randomChoice; // choose the bigger one
    }

    switch (itemChoice) {
    case 0:
        item = createSpring(stairs[replacedIdx].first->left() + 10, stairs[replacedIdx].first->top() - SPRING_HEIGHT);
        break;
    case 1:
        item = createShield(stairs[replacedIdx].first->left() + 10, stairs[replacedIdx].first->top() - SHIELD_HEIGHT);
        break;
    case 2:
        item = createSpringShoes(stairs[replacedIdx].first->left() + 10, stairs[replacedIdx].first->top() - SPRING_SHOES_HEIGHT);
        break;
    case 3:
        item = createTrampoline(stairs[replacedIdx].first->left() + 10, stairs[replacedIdx].first->top() - TRAMPOLINE_HEIGHT);
        break;
    case 4:
        if (stairs[replacedIdx].first->left() > WINDOW_WIDTH / 2)
        {
            item = createBlackHole(stairs[replacedIdx].first->left() - 200, stairs[replacedIdx].first->top() - 100);
        }
        else
        {
            item = createBlackHole(stairs[replacedIdx].first->right() + 150, stairs[replacedIdx].first->top() - 100);
        }

        break;
    case 5:
        item = createPropellerHat(stairs[replacedIdx].first->left() + 10, stairs[replacedIdx].first->top() - PROPELLER_HAT_HEIGHT);
        break;
    case 6:
        item = createJetpack(stairs[replacedIdx].first->left() + 10, stairs[replacedIdx].first->top() - JETPACK_HEIGHT);
        break;
    default:
        break;
    }
    return item;
}

void StairManager::setViewMovement(qreal newViewMovement)
{
    viewMovement = newViewMovement;
}

void StairManager::paintStairs(QPainter *painter)
{
//    qDebug() << "start painting";
    for (int i = 0; i < stairs.size(); i++)
    {
//        qDebug() << "start paint" << i;
        if (stairs[i].first)
        {
            stairs[i].first->paint(painter);
        }
//        qDebug() << "end paint" << i;
    }
//    qDebug() << "end painting";
}

Detector* StairManager::createSelfDeletingDetector(qreal left, qreal top, qreal width, qreal height)
{
    Detector *detector = new Detector(this, left, top, width, height);
//    detector->addRule(&DETECTION_BELOW_WINDOW, &REACTION_SELF_DELETE, typeid(Player).name());   // self-deleting
    connect(this, &StairManager::makeDetectionTo, detector, &Detector::detectTo);               // detecting
    return detector;
}

Detector* StairManager::createStair(qreal left, qreal top, qreal width, qreal height)
{
    Detector *stair = createSelfDeletingDetector(left, top, width, height);
    stair->addRule(&DETECTION_LANDING, &REACTION_PLAYERJUMP, typeid(Player).name());
    stair->addRule(&DETECTION_LANDING, &REACTION_SOUND_JUMP, typeid(Player).name());
    return stair;
}

Detector* StairManager::createBasicStair(qreal left, qreal top)
{
    Detector *stair = createStair(left, top);
    stair->setProfile(":/dataset/images/stair-basic.png");
    return stair;
}

Detector *StairManager::createDisappearingStair(qreal left, qreal top)
{
    Detector *stair = createStair(left, top);
    stair->setProfile(":/dataset/images/stair-disapear.png");
    stair->addRule(&DETECTION_LANDING, &REACTION_DISAPPEAR, typeid(Player).name());

    return stair;
}

Detector *StairManager::createHorizontalMoveStair(qreal left, qreal top)
{
    Detector *stair = createStair(left, top);
    stair->setProfile(":/dataset/images/stair-blue.png");

    stair->mover = new Mover(0.1, 0, 0, 0);
    stair->mover->setBoundary(0, WINDOW_HEIGHT, 0, WINDOW_WIDTH);
    stair->mover->setBoundaryReaction(BoundaryReaction::rebound, BoundaryReaction::none);
    connect(this, &StairManager::update, stair, &Detector::update);

    return stair;
}

Detector *StairManager::createVerticalMoveStair(qreal left, qreal top)
{
    Detector *stair = createStair(left, top);
    stair->setProfile(":/dataset/images/stair-darkblue.png");

    stair->mover = new Mover(0, -0.1, 0, 0);
    stair->mover->setBoundary(stair->top() - 200, stair->bottom(), 0, WINDOW_WIDTH);
    stair->mover->setBoundaryReaction(BoundaryReaction::none, BoundaryReaction::rebound);
    connect(this, &StairManager::update, stair, &Detector::update);

    return stair;
}

Detector *StairManager::createThornStair(qreal left, qreal top)
{
    Detector *stair = createStair(left, top, THORN_STAIR_WIDTH, THORN_STAIR_HEIGHT);
    stair->setProfile(":/dataset/images/extra/stair-thorn.png");
    stair->addRule(&DETECTION_LANDING, &REACTION_PLAYER_BE_ATTACKED, typeid(Player).name());

    return stair;
}

Detector *StairManager::createCountdowStair(qreal left, qreal top)
{
    Detector *stair = createStair(left, top, STAIR_WIDTH, STAIR_HEIGHT);
    stair->setProfile(":/dataset/images/extra/stair-countdown1.png");
    ReactionChangeImage *reactionChangeImage = new ReactionChangeImage(Self, Remove, 1000);
    reactionChangeImage->imagePaths << ":/dataset/images/extra/stair-countdown2.png";
    reactionChangeImage->imagePaths << ":/dataset/images/extra/stair-countdown3.png";
    stair->addRule(&DETECTION_ENTER_WINDOW, reactionChangeImage, typeid(Player).name());

    reactionList.push_back(reactionChangeImage);

    return stair;
}

Detector *StairManager::createBrokenStair(qreal left, qreal top, qreal width, qreal height)
{
    Detector *stair = createSelfDeletingDetector(left, top, width, height);
    stair->setProfile(":/dataset/images/stair-broken1.png");

    // add reaction rule (change image)
    ReactionChangeImage *reactionChangeImage = new ReactionChangeImage(Self, Remove, 300);
    reactionChangeImage->imagePaths << ":/dataset/images/stair-broken2.png";
    reactionChangeImage->imagePaths << ":/dataset/images/stair-broken3.png";
    reactionChangeImage->imagePaths << ":/dataset/images/stair-broken4.png";
    stair->addRule(&DETECTION_LANDING, reactionChangeImage, typeid(Player).name());
    stair->addRule(&DETECTION_LANDING, &REACTION_SOUND_BREAK, typeid(Player).name());

    reactionList.push_back(reactionChangeImage);

    return stair;
}

Detector *StairManager::createSpring(qreal left, qreal top, qreal width, qreal height)
{
    Detector *spring = createSelfDeletingDetector(left, top, width, height);
    spring->setProfile(":/dataset/images/item-spring1.png");
    spring->addRule(&DETECTION_LANDING, &REACTION_JUMP_SPRING, typeid(Player).name());
    spring->addRule(&DETECTION_LANDING, &REACTION_SOUND_SPRING, typeid(Player).name());

    return spring;
}


Detector *StairManager::createTrampoline(qreal left, qreal top, qreal width, qreal height)
{
    Detector *trampoline = createSelfDeletingDetector(left, top, width, height);
    trampoline->setProfile(":/dataset/images/item-trampoline1.png");
    trampoline->addRule(&DETECTION_LANDING, &REACTION_JUMP_TRAMPOLINE, typeid(Player).name());
    trampoline->addRule(&DETECTION_LANDING, &REACTION_DISAPPEAR, typeid(Player).name());
    trampoline->addRule(&DETECTION_LANDING, &REACTION_SOUND_TRAMPOLINE, typeid(Player).name());

    connect(this, &StairManager::makeDetectionTo, trampoline, &Detector::detectTo);

    return trampoline;
}

Detector *StairManager::createPropellerHat(qreal left, qreal top, qreal width, qreal height)
{
    Detector *propellerHat = new Detector(this, left, top, width, height);
    propellerHat->setProfile(":/dataset/images/item-propeller-hat.png");
    propellerHat->addRule(&DETECTION_TOUCHING, &REACTION_JUMP_PROPELLER_HAT, typeid(Player).name());

    // add reaction rule (change image)
    ReactionChangeImage *reactionChangeImage = new ReactionChangeImage(Target, Repetition, 100);
    reactionChangeImage->imagePathsForPlayer
            << qMakePair(QString(":/dataset/images/doodleH/doodleH1.png"), QString(":/dataset/images/doodleH/doodleH1R.png"))
            << qMakePair(QString(":/dataset/images/doodleH/doodleH2.png"), QString(":/dataset/images/doodleH/doodleH2R.png"))
            << qMakePair(QString(":/dataset/images/doodleH/doodleH3.png"), QString(":/dataset/images/doodleH/doodleH3R.png"))
            << qMakePair(QString(":/dataset/images/doodleH/doodleH4.png"), QString(":/dataset/images/doodleH/doodleH4R.png"))
            ;

    propellerHat->addRule(&DETECTION_TOUCHING, reactionChangeImage, typeid(Player).name());
    propellerHat->addRule(&DETECTION_TOUCHING, &REACTION_DISAPPEAR, typeid(Player).name());
    propellerHat->addRule(&DETECTION_TOUCHING, &REACTION_PLAYER_SET_FLYING_STATE, typeid(Player).name());
    propellerHat->addRule(&DETECTION_TOUCHING, &REACTION_SOUND_PROPELLER, typeid(Player).name());

    connect(this, &StairManager::makeDetectionTo, propellerHat, &Detector::detectTo);

    return propellerHat;
}

Detector *StairManager::createJetpack(qreal left, qreal top, qreal width, qreal height)
{
    Detector *jetpack = new Detector(this, left, top, width, height);
    jetpack->setProfile(":/dataset/images/item-jetpack.png");
    jetpack->addRule(&DETECTION_TOUCHING, &REACTION_JUMP_JETPACK, typeid(Player).name());

    // add reaction rule (change image)
    ReactionChangeImage *reactionChangeImage = new ReactionChangeImage(Target, Repetition, 100);

    reactionChangeImage->imagePathsForPlayer
            << qMakePair(QString(":/dataset/images/doodleJ/doodleJ1.png"), QString(":/dataset/images/doodleJ/doodleJ1R.png"))
            << qMakePair(QString(":/dataset/images/doodleJ/doodleJ2.png"), QString(":/dataset/images/doodleJ/doodleJ2R.png"))
            << qMakePair(QString(":/dataset/images/doodleJ/doodleJ3.png"), QString(":/dataset/images/doodleJ/doodleJ3R.png"))
            << qMakePair(QString(":/dataset/images/doodleJ/doodleJ4.png"), QString(":/dataset/images/doodleJ/doodleJ4R.png"))
            << qMakePair(QString(":/dataset/images/doodleJ/doodleJ5.png"), QString(":/dataset/images/doodleJ/doodleJ5R.png"))
            ;

    jetpack->addRule(&DETECTION_TOUCHING, reactionChangeImage, typeid(Player).name());
    jetpack->addRule(&DETECTION_TOUCHING, &REACTION_DISAPPEAR, typeid(Player).name());
    jetpack->addRule(&DETECTION_TOUCHING, &REACTION_PLAYER_SET_FLYING_STATE, typeid(Player).name());
    jetpack->addRule(&DETECTION_TOUCHING, &REACTION_SOUND_ROCKET, typeid(Player).name());

    connect(this, &StairManager::makeDetectionTo, jetpack, &Detector::detectTo);

    return jetpack;
}


Detector *StairManager::createSpringShoes(qreal left, qreal top, qreal width, qreal height)
{
    Detector *springShoes = new Detector(this, left, top, width, height);
    springShoes->setProfile(":/dataset/images/extra/item-spring-shoes.png");

    // add reaction rule (change image)
    ReactionChangeImage *reactionChangeImage = new ReactionChangeImage(Target, Repetition, 10);

    reactionChangeImage->imagePathsForPlayer
            << qMakePair(QString(":/dataset/images/doodleSpring/doodleSpring.png"),
                         QString(":/dataset/images/doodleSpring/doodleSpringR.png"));

    springShoes->addRule(&DETECTION_TOUCHING, reactionChangeImage, typeid(Player).name());
    springShoes->addRule(&DETECTION_TOUCHING, &REACTION_DISAPPEAR, typeid(Player).name());
    springShoes->addRule(&DETECTION_TOUCHING, &REACTION_PLAYER_BUFFED_JUMP_HEIGHT, typeid(Player).name());

    connect(this, &StairManager::makeDetectionTo, springShoes, &Detector::detectTo);

    return springShoes;
}


Detector *StairManager::createShield(qreal left, qreal top, qreal width, qreal height)
{
    Detector *shield = new Detector(this, left, top, width, height);
    shield->setProfile(":/dataset/images/extra/item-shield.png");

    shield->addRule(&DETECTION_TOUCHING, &REACTION_DISAPPEAR, typeid(Player).name());
    shield->addRule(&DETECTION_TOUCHING, &REACTION_PLAYER_SHIELDED, typeid(Player).name());

    connect(this, &StairManager::makeDetectionTo, shield, &Detector::detectTo);

    return shield;
}

Detector *StairManager::createBlackHole(qreal left, qreal top, qreal width, qreal height)
{
    Detector *blackHole = new Detector(this, left, top, width, height);
    blackHole->setProfile(":/dataset/images/blackhole.png");

    blackHole->addRule(&DETECTION_TOUCHING, &REACTION_GAMEOVER, typeid(Player).name());

    connect(this, &StairManager::makeDetectionTo, blackHole, &Detector::detectTo);

    return blackHole;
}

Detector *StairManager::createMonsterOn(Detector *stair)
{
    Detector *monster;
    int monsterChoice = rand() % 4;
    switch (monsterChoice) {
    case 0:
        monster = new Detector(this, stair->left() - 5, stair->top() - 105, 168, 105);
        monster->setProfile(":/dataset/images/monster1.png");
        break;
    case 1:
        monster = new Detector(this, stair->left() - 5, stair->top() - 178, 128, 178);
        monster->setProfile(":/dataset/images/monster2.png");
        break;
    case 2:
        monster = new Detector(this, stair->left() - 5, stair->top() - 100, 160, 100);
        monster->setProfile(":/dataset/images/monster3.png");
        break;
    case 3:
        monster = new Detector(this, stair->left() - 5, stair->top() - 90, 160, 160);
        monster->setProfile(":/dataset/images/monster4.png");
        break;
    }

    monster->addRule(&DETECTION_LANDING, &REACTION_PLAYERJUMP, typeid(Player).name());
    monster->addRule(&DETECTION_LANDING, &REACTION_DISAPPEAR, typeid(Player).name());
    monster->addRule(&DETECTION_TOUCHING_WITHOUT_LANDING, &REACTION_PLAYER_BE_ATTACKED, typeid(Player).name());
    monster->addRule(&DETECTION_TOUCHING, &REACTION_DISAPPEAR, typeid(Bullet).name());
    // SOUND EFFECT
    monster->addRule(&DETECTION_LANDING, &REACTION_SOUND_JUMP_ON_MONSTER, typeid(Player).name());

    connect(this, &StairManager::makeDetectionTo, monster, &Detector::detectTo);
    return monster;
}

void StairManager::viewDown(qreal movement)
{
//    qDebug() << Q_FUNC_INFO << "start";
    for (int i = 0; i < stairs.size(); i++)
    {
        if(stairs[i].first)
        {
            if (stairs[i].first->top() - 200 > WINDOW_HEIGHT)
            {
                if (stairs[i].second != StairCategory::Broken && stairs[i].second != StairCategory::Countdown)
                {
//                    delete stairs[i].first;
//                    stairs[i].first = nullptr;
                }
            }
            else
            {
                stairs[i].first->moveDown(movement);
            }
        }
    }
    viewMovement += movement;
    addStairsUntil(viewMovement + 6000); // create more stairs
}

qreal StairManager::getViewMovement() const
{
    return viewMovement;
}

StairManager::~StairManager()
{
    while (stairs.size() > 0)
    {
        Detector *last = stairs[stairs.size() - 1].first;
        stairs.pop_back();
        if (last)
        {
            delete last;
            last = nullptr;
        }
    }
}
