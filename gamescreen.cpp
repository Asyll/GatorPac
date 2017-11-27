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

    // Default Player(260,450,5)
    gator = new Player(260,450,5);
    scene->addItem(gator);

    currentTmpDir = Direction::NONE;
    nextTmpDir= Direction::NONE;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updater()));
    timer->start(1000/30);

    fsu = new Enemy(260,210,5,"fsu", gameMap, gator, GhostType::RED);
    scene->addItem(fsu);

    georgia = new Enemy(260,270,5,"georgia", gameMap, gator, GhostType::PINK);
    scene->addItem(georgia);

    lsu = new Enemy(220,270,5,"lsu", gameMap, gator, GhostType::BLUE);
    scene->addItem(lsu);

    kentucky = new Enemy(300,270,5,"kentucky", gameMap, gator, GhostType::ORANGE);
    scene->addItem(kentucky);


    fsuCounter = 0;
    georgiaCounter = 0;
    lsuCounter = 0;
    kentuckyCounter = 0;

    score = 0;


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
    playlist->clear();
    playlist= new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/Audio/GameScreenMusic.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(30);
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

void GameScreen::on_pauseButton_clicked() {
    QString pauseBtn = ui->pauseButton->text();
    if (pauseBtn == "Pause") {
        timer->stop();
        ui->pauseButton->setText("Resume");
    }
    else {
        timer->start();
        ui->pauseButton->setText("Pause");
    }
}

void GameScreen::lostLife() {
    if (yesBtnClicked) {
        gator->setLives(3);
        score = 0;
        timer->start();
        ui->retryLabel->setVisible(false);
        ui->yesButton->setVisible(false);
        ui->noButton->setVisible(false);
        playBackgroundMusic();
        yesBtnClicked = false;
    }
    else {
        basicSounds->setMedia(QUrl("qrc:/Audio/pacmanDeath.wav"));
        if (basicSounds->state() == QMediaPlayer::PlayingState) {
            basicSounds->setPosition(0);
        }
        else if (basicSounds->state() == QMediaPlayer::StoppedState) {
            basicSounds->setVolume(40);
            basicSounds->play();
        }
        gator->setLives(gator->getLives() - 1);
    }

    fsu->setPosx(260);
    fsu->setPosy(210);
    georgia->setPosx(260);
    georgia->setPosy(270);
    lsu->setPosx(220);
    lsu->setPosy(270);
    kentucky->setPosx(300);
    kentucky->setPosy(270);
    gator->setPosx(260);
    gator->setPosy(450);


}

void GameScreen::gameOver() {
    playDeathMusic();

    score = ui->scoreValue->value();
    retryString = QString(" Score: ") + QString::number(score) + QString(" Would you like to retry?");

    ui->lifeCount->display(gator->getLives());
    timer->stop();
    ui->retryLabel->setVisible(true);
    ui->retryLabel->setText(retryString);
    ui->yesButton->setVisible(true);
    ui->noButton->setVisible(true);
}

void GameScreen::fsuInitSeq()
{
    // Counter measured in seconds * 30
    if (fsuCounter <= 2400)
    {
        fsuCounter ++;
        switch(fsuCounter)
        {
        case 150:
            fsu->setMode(Movement::CHASE);
            break;
        case 750:
            fsu->setMode(Movement::SCATTER);
            break;
        case 900:
            fsu->setMode(Movement::CHASE);
            break;
        case 1500:
            fsu->setMode(Movement::SCATTER);
            break;
        case 1650:
            fsu->setMode(Movement::CHASE);
            break;
        case 2250:
            fsu->setMode(Movement::SCATTER);
            break;
        case 2400:
            fsu->setMode(Movement::CHASE);
            break;
        }
    }
    else
    {
        fsu->initiate();
    }
}

void GameScreen::georgiaInitSeq()
{
    // Counter measured in seconds * 30
    if (georgiaCounter <= 2400)
    {
        georgiaCounter ++;
        switch(georgiaCounter)
        {
        case 150:
            georgia->setMode(Movement::CHASE);
            break;
        case 750:
            georgia->setMode(Movement::SCATTER);
            break;
        case 900:
            georgia->setMode(Movement::CHASE);
            break;
        case 1500:
            georgia->setMode(Movement::SCATTER);
            break;
        case 1650:
            georgia->setMode(Movement::CHASE);
            break;
        case 2250:
            georgia->setMode(Movement::SCATTER);
            break;
        case 2400:
            georgia->setMode(Movement::CHASE);
            break;
        }
    }
    else
    {
        georgia->initiate();
    }
}

void GameScreen::releaseGeorgia()
{
    if (georgia->getPosy() > 210 && georgia->getPosy() <= 270 && georgia->getPosx() == 260)
    {
        georgia->setPosy(georgia->getPosy() - 2);
    }
    else
    {
        georgia->setReleased(true);
    }
}

void GameScreen::on_yesButton_clicked() {
    yesBtnClicked = true;
    lostLife();
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
    else if ((abs(gator->getPosx() - georgia->getPosx()) <= 20) && (abs(gator->getPosy() - georgia->getPosy()) <= 20)) {
        if (gator->getLives() > 1) {
            lostLife();
        }
        else {
            gator->setLives(0);
            win = false;
            gameOver();
        }
    }
    else if ((abs(gator->getPosx() - lsu->getPosx()) <= 20) && (abs(gator->getPosy() - lsu->getPosy()) <= 20)) {
        if (gator->getLives() > 1) {
            lostLife();
        }
        else {
            gator->setLives(0);
            win = false;
            gameOver();
        }
    }
    else if ((abs(gator->getPosx() - kentucky->getPosx()) <= 20) && (abs(gator->getPosy() - kentucky->getPosy()) <= 20)) {
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
    // For debuggin character position:
    // - unhide xPos and yPos
    // - uncomment the display functions
    ui->xPos->hide();
    ui->yPos->hide();
    //ui->xPos->display(gator->getPosx());
    //ui->yPos->display(gator->getPosy());

    playerMove();

    if (!fsu->isInitiated())
        fsuInitSeq();

    fsu->move();

    releaseGeorgia();
    if (georgia->isReleased())
    {
        if (!georgia->isInitiated())
            georgiaInitSeq();

        georgia->move();
    }

    score++;
    ui->lifeCount->display(gator->getLives());
    ui->scoreValue->display(score);

    ghostCollision();

    scene->update(gameMap->boundingRect());
    gator->update();
    fsu->update();
    georgia->update();

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
    case Qt::Key_Space:
        on_pauseButton_clicked();
        break;
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
