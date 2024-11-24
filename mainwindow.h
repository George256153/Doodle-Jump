#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimerEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QSound>
#include <QRectF>

#include "constants.h"
#include "gameobject.h"
#include "mover.h"
#include "player.h"
#include "detector.h"
#include "stair_manager.h"
#include "reactions/reaction_make_sound.h"

enum class GameStatus {
    ShowingMenu,
    Running,
//    RunningMultiplayer,
    Paused,
    Gameover
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void initGame();
    void initMultiplayerGame();
    void pauseGame();
    void resumeGame();
    void showMenu();
    void gameOver();

signals:
//    void gameStart();
//    void gameOver();

protected:
    void timerEvent(QTimerEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    qreal score;
    qreal score2;
    int timerId;

    Player *player;
    Player *player2;
    StairManager *stairManager;
    GameStatus gameStatus;

    QPushButton *playButton;
    QPushButton *multiPlayerButton;
    QPushButton *resumeButton;
    QPushButton *menuButton;

    QPixmap logo;
    QPixmap ufo;

    ReactionMakeSound REACTION_SOUND_FALLDOWN = ReactionMakeSound("./dataset/sounds/falldown.wav", 80);

    QPushButton* createButton(int x, int y, const QPixmap& iconImage);
    void deleteAllPointers();
};
#endif // MAINWINDOW_H
