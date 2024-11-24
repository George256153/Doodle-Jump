#include "player.h"

Player::Player(QObject *parent, qreal x, qreal y, qreal width, qreal height)
    : GameObject(parent, x, y, width, height)
    , direction(Direction::Right)
    , playerState(PlayerState::Jumping)
    , defaultJumpHeight(PLAYER_BASIC_JUMP_HEIGHT)
    , hp(3)
    , bestHeight(0)
    , coolingDownToAttack(false)
    , shielded(false)
{
    mover = new Mover();
    mover->setBoundary(0, WINDOW_HEIGHT, 0, WINDOW_WIDTH);
    mover->setBoundaryReaction(BoundaryReaction::passThrough, BoundaryReaction::none);

    profileLeftPath = ":/dataset/images/doodleL.png";
    profileRightPath = ":/dataset/images/doodleR.png";

    jump(PLAYER_BASIC_JUMP_HEIGHT); // start jumping!

    shieldImage = new QPixmap(":/dataset/images/extra/shielded.png");
    *shieldImage = shieldImage->scaled(105, 105, Qt::KeepAspectRatio);
}

Player::~Player()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]) delete bullets[i];
        bullets[i] = nullptr;
    }
}

void Player::shoot(QPoint shooted)
{
    Bullet *bullet = new Bullet(this, center().x(), center().y());
    connect(this, &Player::exceedsTopBoundaryBy, bullet, &Bullet::moveDown);

    bullet->emitTo(shooted);

    bullets.push_back(bullet);

    REACTION_SOUND_SHOOT.react(nullptr, nullptr);
}

void Player::initYAccleration() // reset velocity and acceleration due to the given height
{
    qreal numTimeout = PLAYER_JUMP_TIME / GAME_TIMER_INTERVAL;                                  // t: required number of timeouts
    mover->setAcceleration(0, 2.0 * PLAYER_BASIC_JUMP_HEIGHT / (numTimeout * numTimeout) );     // S = 1/2 * a * t^2
}

void Player::setShielded()
{
    shielded = true;
}


void Player::resetShielded()
{
    shielded = false;
}

void Player::resetShieldedAfter(int msec)
{
    QTimer *shieldTimer = new QTimer();
    shieldTimer->singleShot(msec, this, &Player::resetShielded);
}

void Player::setProfileRightPath(const QString &newProfileRightPath)
{
    profileRightPath = newProfileRightPath;
}

void Player::setProfileLeftPath(const QString &newProfileLeftPath)
{
    profileLeftPath = newProfileLeftPath;
}

void Player::jump(qreal jumpHeight) // reset velocity and acceleration due to the given height
{
    if (mover->yAcc() == 0) initYAccleration();

    qreal requiredTime = qSqrt(2.0 * jumpHeight / mover->yAcc()); // compute `t` (required number of timeouts) by `S = 1/2 * a * t^2`
    mover->setVelocity(0, - mover->yAcc() * requiredTime);       // compute `v` by `v = - a * t`
}

void Player::resetCoolingDownToAttackAfter(int msec)
{
    QTimer *coolDownTimer = new QTimer();
    coolDownTimer->singleShot(msec, this, SLOT(resetCoolingDownToAttack()));
//    delete coolDownTimer;
}

void Player::resetCoolingDownToAttack()
{
    coolingDownToAttack = false;
}

void Player::update()
{
    /* check if start dropping */
    if (mover->yVel() <= 0)
    {
        qreal nextYVel = mover->yVel() + mover->yAcc();
        if (nextYVel > 0)
        {
            //qDebug() << Q_FUNC_INFO << "start dropping";
            emit startDropping();
            if (playerState == PlayerState::Flying)
            {
                playerState = PlayerState::Jumping;
                setProfileLeftPath(":/dataset/images/doodleL.png");
                setProfileRightPath(":/dataset/images/doodleR.png");
            }
        }
    }

    /* check if next y is less than a half of the window height */
    qreal nextY = top() + mover->yVel();
    if (nextY <= WINDOW_HEIGHT / 2)                 /* if nextY is higher than half of the window height*/
    {
        moveTop(WINDOW_HEIGHT / 2);
        mover->setVelocity(mover->xVel(), mover->yVel() + mover->yAcc()); // update velocity
        emit exceedsTopBoundaryBy(WINDOW_HEIGHT / 2 - nextY);
    }
    else GameObject::update();

    /* update score */
    int currentHeight = WINDOW_HEIGHT - bottom();
    if (currentHeight > bestHeight) bestHeight = currentHeight;

    /* Rebounce when reaching the bottom of the screen */
    if (bottom() > WINDOW_HEIGHT)
    {
        if (IS_DEBUG)
        {
            moveBottom(WINDOW_HEIGHT);
            jump(PLAYER_BASIC_JUMP_HEIGHT);
        }
        else
        {
            emit reachBottomBoundary();
        }
    }

    /* change profile depends on the direction */
    switch (direction) {
    case Direction::Left:
        setProfile(profileLeftPath);
        break;
    case Direction::Right:
        setProfile(profileRightPath);
        break;
    default:
        break;
    }
}

/* getter and setter */

qreal Player::getBestHeight() const
{
    return bestHeight;
}

int Player::getHp() const
{
    return hp;
}

void Player::beAttacked()
{
    if (attackable())
    {
        hp--;
        coolingDownToAttack = true;
        resetCoolingDownToAttackAfter(3000);
        if (hp <= 0)
        {
            emit OutofHp();
        }
    }
    if (shielded) resetShielded();
}

bool Player::attackable()
{
    return (playerState == PlayerState::Jumping && !coolingDownToAttack && !shielded);
}

void Player::paint(QPainter *painter)
{
    if (shielded)
    {
        painter->drawPixmap(left() - 15, top()-10, *shieldImage);
    }
    GameObject::paint(painter);
}

void Player::moveLeft(qreal x)
{
    GameObject::moveLeft(x);
}

void Player::moveDown(qreal movement)
{
    GameObject::moveDown(movement);
    bestHeight -= movement;
}
