#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QThread>
#include <QtWidgets>
#include "titlescreen.h"

// PUBLIC Functions //

GameScreen::GameScreen(QWidget *parent) : QWidget(parent), ui(new Ui::GameScreen)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,560,620);

    QGraphicsView *gameView = ui->gameView;
    gameView->setScene(scene);
    gameView->setRenderHint(QPainter::Antialiasing);
    gameView->setSceneRect(scene->sceneRect());

    gameMap = new GameMap();
    scene->addItem(gameMap);

    // Default Player(260,450,3)
    gator = new Player(10,10,3);
    scene->addItem(gator);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updater()));
    timer->start(1000/30);



    lives = 3;

    fsu = new Enemy(260,210,"fsu");
    lsu = new Enemy(220,270,"lsu");
    georgia = new Enemy(260,270,"georgia");
    kentucky = new Enemy(300,270,"kentucky");
    scene->addItem(lsu);
    scene->addItem(fsu);
    scene->addItem(georgia);
    scene->addItem(kentucky);

}

GameScreen::~GameScreen()
{
    delete ui;
}


/*Play 8 bit evil morty for the eventual death scene when we get there.
When all lives lost then stops other music and plays final music. */
void GameScreen::playDeathMusic()
{
    finalDeathMusic->setMedia(QUrl("qrc:/Audio/FinalDeathMusic.mp3"));
    if (finalDeathMusic->state() == QMediaPlayer::PlayingState) {
        finalDeathMusic->setPosition(0);
    }
    else if (finalDeathMusic->state() == QMediaPlayer::StoppedState) {
        finalDeathMusic->play();
    }
}

void GameScreen::updater() {
    ui->lifeCount->display(lives);
    ui->scoreValue->display(score);

    playerMove();
    scene->update(gameMap->boundingRect());

    /*this loop is for collision test between GatorPac and the dots
        for() {



            basicSounds->setMedia(QUrl("qrc:/Audio/PacmanChomp.wav"));
            if (basicSounds->state() == QMediaPlayer::PlayingState) {
                basicSounds->setPosition(0);
            }
            else if (basicSounds->state() == QMediaPlayer::StoppedState) {
                basicSounds->play();
            }
        }
    */
}

void GameScreen::playerMove()
{
    QPoint point;
    const int speed = gator->getSpeed();

    if (currentTmpDir != nextTmpDir)
    {
        switch(nextTmpDir)
        {
        case LEFT:
            point.setX(gator->posx - speed);
            point.setY(gator->posy);
            if (gameMap->canMove(point))
            {
                currentTmpDir = nextTmpDir;
                nextTmpDir = Direction::NONE;
            }
            break;
        case RIGHT:
            point.setX(gator->posx + speed);
            point.setY(gator->posy);
            if (gameMap->canMove(point))
            {
                currentTmpDir = nextTmpDir;
                nextTmpDir = Direction::NONE;
            }
            break;
        case UP:
            point.setX(gator->posx);
            point.setY(gator->posy - speed);
            if (gameMap->canMove(point))
            {
                currentTmpDir = nextTmpDir;
                nextTmpDir = Direction::NONE;
            }
            break;
        case DOWN:
            point.setX(gator->posx);
            point.setY(gator->posy + speed);
            if (gameMap->canMove(point))
            {
                currentTmpDir = nextTmpDir;
                nextTmpDir = Direction::NONE;
            }
            break;
        case NONE:
            break;
        }
    }
    switch(currentTmpDir)
    {
    case LEFT:
        gator->setDirection(currentTmpDir);
        point.setX(gator->posx - speed);
        point.setY(gator->posy);
        if (gameMap->canMove(point))
        {
            gator->posx -= speed;
            gator->moving = true;
        }
        else
        {
            gator->moving = false;
        }
        break;
    case RIGHT:
        gator->setDirection(currentTmpDir);
        point.setX(gator->posx + speed);
        point.setY(gator->posy);
        if (gameMap->canMove(point))
        {
            gator->posx += speed;
            gator->moving = true;
        }
        else
        {
            gator->moving = false;
        }
        break;
    case UP:
        gator->setDirection(currentTmpDir);
        point.setX(gator->posx);
        point.setY(gator->posy - speed);
        if (gameMap->canMove(point))
        {
            gator->posy -= speed;
            gator->moving = true;
        }
        else
        {
            gator->moving = false;
        }
        break;
    case DOWN:
        gator->setDirection(currentTmpDir);
        point.setX(gator->posx);
        point.setY(gator->posy + speed);
        if (gameMap->canMove(point))
        {
            gator->posy += speed;
            gator->moving = true;
        }
        else
        {
            gator->moving = false;
        }
        break;
    case NONE:
        break;
    }
}

// PROTECTED Functions //

void GameScreen::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_A:
        if (!gator->moving)
        {
            currentTmpDir = Direction::LEFT;
        }
        else
        {
            nextTmpDir = Direction::LEFT;
        }
        break;
    case Qt::Key_D:
        if (!gator->moving)
        {
            currentTmpDir = Direction::RIGHT;
        }
        else
        {
            nextTmpDir = Direction::RIGHT;
        }
        break;
    case Qt::Key_W:
        if (!gator->moving)
        {
            currentTmpDir = Direction::UP;
        }
        else
        {
            nextTmpDir = Direction::UP;
        }
        break;
    case Qt::Key_S:
        if (!gator->moving)
        {
            currentTmpDir = Direction::DOWN;
        }
        else
        {
            nextTmpDir = Direction::DOWN;
        }
        break;
    }
}
