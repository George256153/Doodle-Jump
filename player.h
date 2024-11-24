#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QDebug>
#include <QSound>
#include <QTimerEvent>
#include <QPoint>
#include <QtMath>
#include <QLabel>
#include <QPixmap>

#include "constants.h"
#include "gameobject.h"
#include "bullet.h"
#include "reactions/reaction_make_sound.h"

enum class PlayerState {
    Flying,
    Jumping
};

enum class Direction {
    Left,
    Right
};

class Player : public GameObject
{
    Q_OBJECT

public:
    explicit Player(QObject *parent = nullptr, qreal x = 0, qreal y = 0, qreal width = 0, qreal height = 0);
    virtual ~Player();

    qreal getBestHeight() const;

    int getHp() const;
    void beAttacked();
    bool attackable();

    void shoot(QPoint shooted);
    void paint(QPainter *painter) override;

    void moveLeft(qreal x);

    void setProfileLeftPath(const QString &newProfileLeftPath);
    void setProfileRightPath(const QString &newProfileRightPath);

    QVector<Bullet*> bullets;
    Direction direction;
    PlayerState playerState;
    qreal defaultJumpHeight;

    void setShielded();

signals:
    void exceedsTopBoundaryBy(qreal velocity);
    void startDropping();
    void changeProfile();
    void reachBottomBoundary();
    void OutofHp();

public slots:
    void update() override;
    void moveDown(qreal movement) override;
    void jump(qreal jumpHeight = PLAYER_BASIC_JUMP_HEIGHT);
    void resetCoolingDownToAttackAfter(int msec);
    void resetCoolingDownToAttack();
    void resetShielded();
    void resetShieldedAfter(int msec);

private:
    void initYAccleration();

    int hp;
    qreal bestHeight;
    bool coolingDownToAttack;
    bool shielded;

    ReactionMakeSound REACTION_SOUND_SHOOT = ReactionMakeSound("./dataset/sounds/shoot.wav");

    QString profileLeftPath;
    QString profileRightPath;

    QPixmap *shieldImage;
};

#endif // PLAYER_H
