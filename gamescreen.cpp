#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QThread>
#include <QtWidgets>
#include <cmath>
#include "titlescreen.h"
#include "player.h"

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

    ui->retryLabel->setVisible(false);
    ui->yesButton->setVisible(false);
    ui->noButton->setVisible(false);

    // Default Player(260,450,3)
    gator = new Player(260,450,2);
    scene->addItem(gator);

    currentTmpDir = Direction::NONE;
    nextTmpDir= Direction::NONE;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updater()));
    timer->start(1000/30);


    score = 0;

    fsu = new Enemy(260,210,2,"fsu");
//    lsu = new Enemy(220,270,2,"lsu");
//    georgia = new Enemy(260,270,2,"georgia");
//    kentucky = new Enemy(300,270,2,"kentucky");
//    scene->addItem(lsu);
    scene->addItem(fsu);
//    scene->addItem(georgia);
//    scene->addItem(kentucky);

    playBackgroundMusic();

}

GameScreen::~GameScreen()
{
    delete ui;
}


/*Play 8 bit evil morty for the eventual death scene when we get there.
When all lives lost then stops other music and plays final music. */
void GameScreen::playDeathMusic()
{
    playlist->clear();
    playlist->addMedia(QUrl("qrc:/Audio/FinalDeathMusic.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();
}

void GameScreen::playWinMusic() {

    playlist->clear();
    playlist->addMedia(QUrl("qrc:/Audio/September.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();
}

void GameScreen::playBackgroundMusic()
{
    playlist= new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/Audio/GameScreenMusic.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();
}

void GameScreen::on_musicButton_clicked() {
    if (playlist->isEmpty()) {
        if (gator->getLives() == 0 && win) {
            playWinMusic();
        }
        else if (gator->getLives() == 0 && !win) {
            playDeathMusic();
        }
        else {
            playBackgroundMusic();
        }
        ui->musicButton->setText("Music Off");
    }
    else {
    playlist->clear();
    ui->musicButton->setText("Music On");
    }
}

void GameScreen::lostLife() {
    gator->setLives(gator->getLives() - 1);

    fsu->setPosx(260);
    fsu->setPosy(210);
    gator->setPosx(260);
    gator->setPosy(450);
}

void GameScreen::gameOver() {
    playDeathMusic();

    score = 5;
    retryString = QString("Score: ") + QString::number(score) + QString(" Would you like to retry?");

    ui->lifeCount->display(gator->getLives());
    timer->stop();
    ui->retryLabel->setVisible(true);
    ui->retryLabel->setText(retryString);
    ui->yesButton->setVisible(true);
    ui->noButton->setVisible(true);
}

void GameScreen::on_yesButton_clicked() {
    //reset
}

void GameScreen::on_noButton_clicked() {
    exit(0);
}

void GameScreen::ghostCollision() {

    if ((abs(gator->getPosx() - fsu->getPosx()) <= 20) && (abs(gator->getPosy() - fsu->getPosy()) <= 20)) {
        if (gator->getLives() > 1) {
            lostLife();
        }
        else {
            gator->setLives(0);
            win = false;
            gameOver();
        }
    }
}

void GameScreen::updater() {

    ui->lifeCount->display(gator->getLives());
    ui->scoreValue->display(score);
    ghostCollision();

    // Debug character position
    ui->xPos->hide();
    ui->yPos->hide();
    //ui->xPos->display(gator->getPosx());
    //ui->yPos->display(gator->getPosy());


    playerMove();
    fsu->chase(gator, gameMap);


    scene->update(gameMap->boundingRect());
    gator->update();
    fsu->update();

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
            point.setX(gator->getPosx() - speed);
            point.setY(gator->getPosy());
            if (gameMap->canMove(point))
            {
                currentTmpDir = nextTmpDir;
                nextTmpDir = Direction::NONE;
            }
            break;
        case RIGHT:
            point.setX(gator->getPosx() + speed);
            point.setY(gator->getPosy());
            if (gameMap->canMove(point))
            {
                currentTmpDir = nextTmpDir;
                nextTmpDir = Direction::NONE;
            }
            break;
        case UP:
            point.setX(gator->getPosx());
            point.setY(gator->getPosy() - speed);
            if (gameMap->canMove(point))
            {
                currentTmpDir = nextTmpDir;
                nextTmpDir = Direction::NONE;
            }
            break;
        case DOWN:
            point.setX(gator->getPosx());
            point.setY(gator->getPosy() + speed);
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
        point.setX(gator->getPosx() - speed);
        point.setY(gator->getPosy());
        if (gameMap->canMove(point))
        {
            gator->setPosx(gator->getPosx() - speed);
            gator->setMoving(true);
        }
        else
        {
            gator->setMoving(false);
        }
        break;
    case RIGHT:
        gator->setDirection(currentTmpDir);
        point.setX(gator->getPosx() + speed) ;
        point.setY(gator->getPosy());
        if (gameMap->canMove(point))
        {
            gator->setPosx(gator->getPosx() + speed);
            gator->setMoving(true);
        }
        else
        {
            gator->setMoving(false);
        }
        break;
    case UP:
        gator->setDirection(currentTmpDir);
        point.setX(gator->getPosx());
        point.setY(gator->getPosy() - speed);
        if (gameMap->canMove(point))
        {
            gator->setPosy(gator->getPosy() - speed);
            gator->setMoving(true);
        }
        else
        {
            gator->setMoving(false);
        }
        break;
    case DOWN:
        gator->setDirection(currentTmpDir);
        point.setX(gator->getPosx());
        point.setY(gator->getPosy() + speed);
        if (gameMap->canMove(point))
        {
            gator->setPosy(gator->getPosy() + speed);
            gator->setMoving(true);
        }
        else
        {
            gator->setMoving(false);
        }
        break;
    case NONE:
        break;
    }

    if (gator->getPosx() == 0)
    {
        gator->setPosx(520);
    }
    else if (gator->getPosx() == 520)
    {
        gator->setPosx(0);
    }
}

void GameScreen::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_A:
        if (!gator->isMoving())
        {
            currentTmpDir = Direction::LEFT;
        }
        else
        {
            nextTmpDir = Direction::LEFT;
        }
        break;
    case Qt::Key_D:
        if (!gator->isMoving())
        {
            currentTmpDir = Direction::RIGHT;
        }
        else
        {
            nextTmpDir = Direction::RIGHT;
        }
        break;
    case Qt::Key_W:
        if (!gator->isMoving())
        {
            currentTmpDir = Direction::UP;
        }
        else
        {
            nextTmpDir = Direction::UP;
        }
        break;
    case Qt::Key_S:
        if (!gator->isMoving())
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
