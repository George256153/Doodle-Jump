#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , score(0)
    , score2(0)
    , gameStatus(GameStatus::ShowingMenu)
    , player(nullptr)
    , player2(nullptr)
    , stairManager(nullptr)
{
    setWindowTitle("Doodle Jump");
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setFocusPolicy(Qt::StrongFocus);

    playButton = createButton(60, 250, QPixmap(":/dataset/images/extra/button_play.png"));
    multiPlayerButton = createButton(100, 370, QPixmap(":/dataset/images/extra/button_multiplayer.png"));
    resumeButton = createButton(60, 500, QPixmap(":/dataset/images/extra/button_resume.png"));
    menuButton = createButton(60, 700, QPixmap(":/dataset/images/extra/button_menu.png"));

    logo = QPixmap(":/dataset/images/extra/logo.png");
    ufo = QPixmap(":/dataset/images/extra/UFO.png");

    connect(playButton, &QPushButton::clicked, this, &MainWindow::initGame);
    connect(multiPlayerButton, &QPushButton::clicked, this, &MainWindow::initMultiplayerGame);
    connect(resumeButton, &QPushButton::clicked, this, &MainWindow::resumeGame);
    connect(menuButton, &QPushButton::clicked, this, &MainWindow::showMenu);
    
    playButton->setVisible(true);
    resumeButton->setVisible(false);
    menuButton->setVisible(false);
}

MainWindow::~MainWindow()
{
    deleteAllPointers();
}

void MainWindow::initGame()
{
    gameStatus = GameStatus::Running;

    deleteAllPointers();

    score = 0;
    score2 = 0;
    player = new Player(this, PLAYER_INIT_X, PLAYER_INIT_Y, PLAYER_WIDTH, PLAYER_HEIGHT);
    player->setProfile(":/dataset/images/doodleR.png");

    stairManager = new StairManager(this);
    connect(player, &Player::exceedsTopBoundaryBy, stairManager, &StairManager::viewDown);
    connect(player, &Player::reachBottomBoundary, this, &MainWindow::gameOver);
    connect(player, &Player::OutofHp, this, &MainWindow::gameOver);

    timerId = startTimer(GAME_TIMER_INTERVAL);

    playButton->setVisible(false);
    multiPlayerButton->setVisible(false);
    resumeButton->setVisible(false);
    menuButton->setVisible(false);
}

void MainWindow::initMultiplayerGame()
{
    gameStatus = GameStatus::Running;

    score = 0;
    score2 = 0;
    player = new Player(this, PLAYER_INIT_X + 50, PLAYER_INIT_Y, PLAYER_WIDTH, PLAYER_HEIGHT);
    player->setProfile(":/dataset/images/doodleR.png");

    player2 = new Player(this, PLAYER_INIT_X - 50, PLAYER_INIT_Y, PLAYER_WIDTH, PLAYER_HEIGHT);
    player2->setProfile(":/dataset/images/extra/doodleR2.png");
    player2->setProfileLeftPath(":/dataset/images/extra/doodleL2.png");
    player2->setProfileRightPath(":/dataset/images/extra/doodleR2.png");

    stairManager = new StairManager(this, false, false);

    for (auto p : QVector<Player*>({player, player2}))
    {
        connect(p, &Player::exceedsTopBoundaryBy, stairManager, &StairManager::viewDown);
        connect(p, &Player::reachBottomBoundary, this, &MainWindow::gameOver);
//        connect(p, &Player::OutofHp, this, &MainWindow::gameOver);
    }

    connect(player, &Player::exceedsTopBoundaryBy, player2, &Player::moveDown);
    connect(player2, &Player::exceedsTopBoundaryBy, player, &Player::moveDown);

    timerId = startTimer(GAME_TIMER_INTERVAL);

    playButton->setVisible(false);
    multiPlayerButton->setVisible(false);
    resumeButton->setVisible(false);
    menuButton->setVisible(false);
}

void MainWindow::pauseGame()
{
    gameStatus = GameStatus::Paused;
    killTimer(timerId);
    
    playButton->setVisible(false);
    multiPlayerButton->setVisible(false);
    resumeButton->setVisible(true);
    menuButton->setVisible(true);
}

void MainWindow::resumeGame()
{
    gameStatus = GameStatus::Running;
    timerId = startTimer(GAME_TIMER_INTERVAL);

    playButton->setVisible(false);
    multiPlayerButton->setVisible(false);
    resumeButton->setVisible(false);
    menuButton->setVisible(false);
}

void MainWindow::showMenu()
{
    gameStatus = GameStatus::ShowingMenu;

    playButton->setVisible(true);
    multiPlayerButton->setVisible(true);
    resumeButton->setVisible(false);
    menuButton->setVisible(false);
}

void MainWindow::gameOver()
{
    gameStatus = GameStatus::Gameover;
    killTimer(timerId);

    REACTION_SOUND_FALLDOWN.react(nullptr);

    playButton->setVisible(false);
    multiPlayerButton->setVisible(false);
    resumeButton->setVisible(false);
    menuButton->setVisible(true);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    player->update();
    emit stairManager->makeDetectionTo(player);
    for (int i = 0; i < player->bullets.size(); i++)
    {
        emit stairManager->makeDetectionTo(player->bullets[i]);
    }

    if (player2)
    {
        player2->update();
        emit stairManager->makeDetectionTo(player2);
    }

//    qDebug() << "before stairManager update";
    emit stairManager->update();
//    qDebug() << "after stairManager update";
    update();
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    /* Painter setup */
    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::black);

    QFont font;
    font.setPixelSize(20);
    font.setBold(true);

    painter.setPen(pen);
    painter.setFont(font);

    painter.drawPixmap(0, 0, QPixmap(":/dataset/images/background.png"));

    switch (gameStatus) {
    case GameStatus::ShowingMenu:
        painter.drawPixmap(40, 50, logo);
        painter.drawPixmap(350, 200, ufo);
        painter.drawPixmap(50 - 15, 800 - PLAYER_HEIGHT - 10, QPixmap(":/dataset/images/extra/shielded.png").scaled(105, 105, Qt::KeepAspectRatio));
        painter.drawPixmap(50, 800 - PLAYER_HEIGHT, QPixmap(":/dataset/images/doodleR.png"));
        painter.drawPixmap(360, 830 - PLAYER_HEIGHT, QPixmap(":/dataset/images/doodleSpring/doodleSpringR.png").scaled(120, 120, Qt::KeepAspectRatio));
        painter.drawPixmap(200, 800 - PLAYER_HEIGHT, QPixmap(":/dataset/images/extra/doodleL2.png"));
        painter.drawPixmap(40, 800, QPixmap(":/dataset/images/stair-basic.png"));
        painter.drawPixmap(100, 870, QPixmap(":/dataset/images/extra/stair-thorn.png"));
        painter.drawPixmap(50 + STAIR_WIDTH, 800, QPixmap(":/dataset/images/stair-darkblue.png"));
        painter.drawPixmap(350, 550, QPixmap(":/dataset/images/blackhole.png"));

        painter.drawPixmap(90, 670, QPixmap(":/dataset/images/extra/stair-countdown1.png"));
        painter.drawPixmap(170, 580, QPixmap(":/dataset/images/extra/stair-countdown2.png"));
        painter.drawPixmap(120, 540, QPixmap(":/dataset/images/extra/stair-countdown3.png"));
        
        break;

    case GameStatus::Running:
        /* Paint stairs */
        stairManager->paintStairs(&painter);

        /* Paint player and scores */
        if (player)
        {
            player->paint(&painter);

            for (int i = 0; i < player->bullets.size(); i++)
            {
                player->bullets[i]->paint(&painter);
            }

            qreal newScore = player->getBestHeight() + stairManager->getViewMovement();
            if (newScore > score) score = newScore;

            if (!player2)
            {
                painter.drawText(50, 30, QString("Score: %1").arg(score));
//                painter.drawText(300, 30, QString("HP: %1").arg(player->getHp()));
                painter.drawText(300, 30, QString("HP:"));
                for (int i = 0; i < player->getHp(); i++)
                {
                    painter.drawPixmap(340 + (35 * i), 10,
                                       QPixmap(":/dataset/images/extra/heart.png").scaled(30, 30, Qt::KeepAspectRatio)
                                       );
                }
            }
            else
            {
                painter.drawText(250, 30, QString("(Yellow) Score: %1").arg(score));
            }
        }

        if (player2)
        {
            player2->paint(&painter);

            for (int i = 0; i < player2->bullets.size(); i++)
            {
                player2->bullets[i]->paint(&painter);
            }

            qreal newScore2 = player2->getBestHeight() + stairManager->getViewMovement();
            if (newScore2 > score2) score2 = newScore2;

            painter.drawText(30, 30, QString("(Blue) Score: %1").arg(score2));
        }
        break;

    case GameStatus::Gameover:
        if (!player2)
        {
            painter.drawText(50, 30, QString("Score: %1").arg(score));
//            painter.drawText(250, 30, QString("HP: %1").arg(player->getHp()));
            painter.drawText(300, 30, QString("HP:"));
            for (int i = 0; i < player->getHp(); i++)
            {
                painter.drawPixmap(340 + (35 * i), 10,
                                   QPixmap(":/dataset/images/extra/heart.png").scaled(30, 30, Qt::KeepAspectRatio)
                                   );
            }
        }
        else
        {
            painter.drawText(250, 30, QString("(Yellow) Score: %1").arg(score));
            painter.drawText(30, 30, QString("(Blue) Score: %1").arg(score2));
            painter.drawText(100, 300, QString("%1-Doodler wins!").arg(
                                 (player->bottom() > WINDOW_HEIGHT) ? "Blue" : "Yellow"
                                 ));
        }

        break;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    switch (gameStatus) {
    case GameStatus::Running:
        if (event->x() > 0 && event->x() < WINDOW_WIDTH && event->y() > 0 && event->y() < WINDOW_HEIGHT)
        {
            player->shoot(event->pos());
        }
        break;
    default:
        break;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (gameStatus) {
    case GameStatus::Running:
        if (event->key() == Qt::Key_Left)
        {
            player->direction = Direction::Left;
            player->moveLeft(player->left() - PLAYER_KEY_MOVE);
        }
        else if (event->key() == Qt::Key_Right)
        {
            player->direction = Direction::Right;
            player->moveLeft(player->left() + PLAYER_KEY_MOVE);
        }

        // player 2
        if (player2)
        {
            if (event->key() == Qt::Key_A)
            {
                player2->direction = Direction::Left;
                player2->moveLeft(player2->left() - PLAYER_KEY_MOVE);
            }
            else if (event->key() == Qt::Key_D)
            {
                player2->direction = Direction::Right;
                player2->moveLeft(player2->left() + PLAYER_KEY_MOVE);
            }
        }

        if (event->key() == Qt::Key_Escape)
        {
            pauseGame();
        }
        update();
        break;

    case GameStatus::Paused:
        break;
//    case GameStatus::Finished:
//        break;
    }

}

QPushButton *MainWindow::createButton(int x, int y, const QPixmap& iconImage)
{
    QPushButton *btn = new QPushButton(this);
    btn->setIcon(QIcon(iconImage));
    btn->setIconSize(iconImage.rect().size());
    btn->setFixedSize(iconImage.rect().size());
    btn->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    btn->move(x, y);

    return btn;
}

void MainWindow::deleteAllPointers()
{
    if (player) delete player;
    player = nullptr;

    if (player2) delete player2;
    player2 = nullptr;

    if(stairManager) delete stairManager;
    stairManager = nullptr;
}
