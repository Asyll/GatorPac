#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QThread>
#include <QtWidgets>
#include <cmath>
#include "titlescreen.h"
#include "player.h"
#include <iostream>

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
    ui->retryButton->setVisible(false);
    ui->quitButton->setVisible(false);
    ui->resumeButton->setVisible(false);
    ui->scoreLabel2->setVisible(false);
    ui->scoreValue2->setVisible(false);
    ui->winLabel->setVisible(false);
    wakaSound->setMedia(QUrl("qrc:/Audio/PacmanChomp.mp3"));

    // Default Player(260,450,5)
    gator = new Player(260,450,5);
    gator->setZValue(4);
    scene->addItem(gator);

    currentTmpDir = Direction::NONE;
    nextTmpDir= Direction::NONE;



    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updater()));
    timer->start(1000/30);

    frightTimer = new QTimer(this);
    frightTimer->setInterval(10000);
    frightTimer->setSingleShot(true);
    connect(frightTimer, SIGNAL(timeout()), this, SLOT(end_fright()));

    lsuReleaseTimer = new QTimer(this);
    lsuReleaseTimer->setInterval(4000);
    lsuReleaseTimer->setSingleShot(true);
    connect(lsuReleaseTimer, SIGNAL(timeout()), this, SLOT(lsuAvailable()));
    lsuReleaseTimer->start();

    kentuckyReleaseTimer = new QTimer(this);
    kentuckyReleaseTimer->setInterval(10000);
    kentuckyReleaseTimer->setSingleShot(true);
    connect(kentuckyReleaseTimer, SIGNAL(timeout()), this, SLOT(kentuckyAvailable()));
    kentuckyReleaseTimer->start();



    fsu = new Enemy(260,210,5,"fsu", gameMap, gator, GhostType::RED);
    fsu->setZValue(5);
    scene->addItem(fsu);

    georgia = new Enemy(260,270,5,"georgia", gameMap, gator, GhostType::PINK);
    georgia->setZValue(5);
    scene->addItem(georgia);

    lsu = new Enemy(220,270,5,"lsu", gameMap, gator, GhostType::BLUE);
    lsu->setZValue(5);
    scene->addItem(lsu);

    kentucky = new Enemy(300,270,5,"kentucky", gameMap, gator, GhostType::ORANGE);
    kentucky->setZValue(5);
    scene->addItem(kentucky);



    dots = new Dots(gameMap->getDotVector());
    scene->addItem(dots);



    fsuCounter = 0;
    georgiaCounter = 0;
    lsuCounter = 0;
    kentuckyCounter = 0;

    canReleaseLSU = false;
    canReleaseKentucky = false;

    score = 0;
    mascotPoints = 200;


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

    deathMusic->setPlaylist(playlist);
    deathMusic->play();
}

void GameScreen::playWinMusic() {

    playlist->clear();
    playlist->addMedia(QUrl("qrc:/Audio/September.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    winMusic->setPlaylist(playlist);
    winMusic->play();
}

void GameScreen::playBackgroundMusic()
{
    playlist->clear();
    playlist->addMedia(QUrl("qrc:/Audio/GameScreenMusic.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    backgroundMusic->setPlaylist(playlist);
    backgroundMusic->setVolume(30);
    backgroundMusic->play();
}

void GameScreen::playFrightenMusic() {
    frightenSound->setMedia(QUrl("qrc:/Audio/sonicDrowning.mp3"));
    if (frightenSound->state() == QMediaPlayer::PlayingState) {
        frightenSound->setPosition(0);
    }
    else if (frightenSound->state() == QMediaPlayer::StoppedState) {
        frightenSound->play();
    }
    backgroundMusic->setVolume(0);
}

void GameScreen::on_musicButton_clicked() {
    if (dots->points.isEmpty()) {
        playWinMusic();
    }
    else if (gator->getLives() == 0 && !win) {
        playDeathMusic();
    }
    else {
        playBackgroundMusic();
    }
    ui->musicButton->setVisible(false);
    ui->muteButton->setVisible(true);
}

void GameScreen::on_muteButton_clicked() {
    playlist->clear();
    ui->muteButton->setVisible(false);
    ui->musicButton->setVisible(true);
}

void GameScreen::on_pauseButton_clicked() {
    if (ui->retryButton->isVisible() == true) {
        return;
    }
    else {
        timer->stop();
        ui->resumeButton->setVisible(true);
        ui->pauseButton->setVisible(false);
    }
}

void GameScreen::on_resumeButton_clicked() {
    if (ui->retryButton->isVisible() == true) {
        return;
    }
    else {
        timer->start();
        ui->resumeButton->setVisible(false);
        ui->pauseButton->setVisible(true);
    }
}

void GameScreen::lsuAvailable()
{
    canReleaseLSU = true;
}

void GameScreen::kentuckyAvailable()
{
    canReleaseKentucky = true;
}

void GameScreen::end_fright()
{
    if (fsu->isReleased())
        fsu->setMode(Movement::CHASE);

    if (georgia->isReleased())
        georgia->setMode(Movement::CHASE);

    if (lsu->isReleased())
        lsu->setMode(Movement::CHASE);

    if (kentucky->isReleased())
        kentucky->setMode(Movement::CHASE);

    backgroundMusic->setVolume(30);
}

void GameScreen::resetGame()
{
    ui->retryLabel->setVisible(false);
    ui->retryButton->setVisible(false);
    ui->quitButton->setVisible(false);
    ui->scoreLabel2->setVisible(false);
    ui->scoreValue2->setVisible(false);
    ui->winLabel->setVisible(false);
    ui->AwayLabel->setVisible(true);
    ui->awayScore->setVisible(true);
    ui->gameView->setVisible(true);
    ui->lifeCount->setVisible(true);
    ui->LifeLabel->setVisible(true);
    ui->pauseButton->setVisible(true);
    ui->scoreLabel->setVisible(true);
    ui->scoreValue->setVisible(true);

    resetCharacters();

    gator->setLives(3);
    score = 0;

    fsu->setInitiated(false);
    georgia->setReleased(false);
    georgia->setInitiated(false);
    lsu->setReleased(false);
    lsu->setInitiated(false);
    kentucky->setReleased(false);
    kentucky->setInitiated(false);
    fsuCounter = 0;
    georgiaCounter = 0;
    lsuCounter = 0;
    kentuckyCounter = 0;

    dots->setPoints(gameMap->getDotVector());

    playBackgroundMusic();
    yesBtnClicked = false;
    timer->start();
}

void GameScreen::resetCharacters()
{
    fsu->setDefaultPosition();
    fsu->resetOrientation();

    georgia->setDefaultPosition();
    georgia->resetOrientation();

    lsu->setDefaultPosition();
    lsu->resetOrientation();
    canReleaseLSU = false;
    lsuReleaseTimer->start();

    kentucky->setDefaultPosition();
    kentucky->resetOrientation();
    canReleaseKentucky = false;
    kentuckyReleaseTimer->start();

    gator->setDefaultPosition();
    gator->resetOrientation();
}

void GameScreen::lostLife() {

    basicSounds->setMedia(QUrl("qrc:/Audio/pacmanDeath.mp3"));
    if (basicSounds->state() == QMediaPlayer::PlayingState) {
        basicSounds->setPosition(0);
    }
    else if (basicSounds->state() == QMediaPlayer::StoppedState) {
        basicSounds->setVolume(40);
        basicSounds->play();
    }

    gator->setLives(gator->getLives() - 1);

    resetCharacters();
}

void GameScreen::waka() {
    if (wakaSound->state() == QMediaPlayer::StoppedState) {
        wakaSound->setPosition(0);
        wakaSound->play();
    }
}

void GameScreen::winGame() {
    playWinMusic();

    ui->lifeCount->display(gator->getLives());
    timer->stop();
    ui->winLabel->setVisible(true);
    ui->retryButton->setVisible(true);
    ui->quitButton->setVisible(true);
    ui->scoreLabel2->setVisible(true);
    ui->scoreValue2->setVisible(true);
    ui->scoreValue2->display(score);
    ui->AwayLabel->setVisible(false);
    ui->awayScore->setVisible(false);
    ui->gameView->setVisible(false);
    ui->lifeCount->setVisible(false);
    ui->LifeLabel->setVisible(false);
    ui->pauseButton->setVisible(false);
    ui->resumeButton->setVisible(false);
    ui->scoreLabel->setVisible(false);
    ui->scoreValue->setVisible(false);
}

void GameScreen::gameOver() {
    playDeathMusic();

    ui->lifeCount->display(gator->getLives());
    timer->stop();
    ui->retryLabel->setVisible(true);
    ui->retryButton->setVisible(true);
    ui->quitButton->setVisible(true);
    ui->scoreLabel2->setVisible(true);
    ui->scoreValue2->setVisible(true);

    ui->scoreValue2->display(score);

    ui->AwayLabel->setVisible(false);
    ui->awayScore->setVisible(false);
    ui->gameView->setVisible(false);
    ui->lifeCount->setVisible(false);
    ui->LifeLabel->setVisible(false);
    ui->pauseButton->setVisible(false);
    ui->resumeButton->setVisible(false);
    ui->scoreLabel->setVisible(false);
    ui->scoreValue->setVisible(false);
}

void GameScreen::fsuInitSeq()
{
    // Counter measured in seconds * 30
    if (fsuCounter <= 2400)
    {
        switch(fsuCounter)
        {
        case 0:
            fsu->setMode(Movement::SCATTER);
            break;
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
        fsuCounter ++;
    }
    else
    {
        fsu->setInitiated(true);
    }
}

void GameScreen::georgiaInitSeq()
{
    // Counter measured in seconds * 30
    if (georgiaCounter <= 2400)
    {
        switch(georgiaCounter)
        {
        case 0:
            georgia->setMode(Movement::SCATTER);
            break;
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
        georgiaCounter ++;
    }
    else
    {
        georgia->setInitiated(true);
    }
}

void GameScreen::lsuInitSeq()
{
    // Counter measured in seconds * 30
    if (lsuCounter <= 2400)
    {
        switch(lsuCounter)
        {
        case 0:
            lsu->setMode(Movement::SCATTER);
            break;
        case 150:
            lsu->setMode(Movement::CHASE);
            break;
        case 750:
            lsu->setMode(Movement::SCATTER);
            break;
        case 900:
            lsu->setMode(Movement::CHASE);
            break;
        case 1500:
            lsu->setMode(Movement::SCATTER);
            break;
        case 1650:
            lsu->setMode(Movement::CHASE);
            break;
        case 2250:
            lsu->setMode(Movement::SCATTER);
            break;
        case 2400:
            lsu->setMode(Movement::CHASE);
            break;
        }
        lsuCounter ++;
    }
    else
    {
        lsu->setInitiated(true);
    }
}

void GameScreen::kentuckyInitSeq()
{
    // Counter measured in seconds * 30
    if (kentuckyCounter <= 2400)
    {
        switch(kentuckyCounter)
        {
        case 0:
            kentucky->setMode(Movement::SCATTER);
            break;
        case 150:
            kentucky->setMode(Movement::CHASE);
            break;
        case 750:
            kentucky->setMode(Movement::SCATTER);
            break;
        case 900:
            kentucky->setMode(Movement::CHASE);
            break;
        case 1500:
            kentucky->setMode(Movement::SCATTER);
            break;
        case 1650:
            kentucky->setMode(Movement::CHASE);
            break;
        case 2250:
            kentucky->setMode(Movement::SCATTER);
            break;
        case 2400:
            kentucky->setMode(Movement::CHASE);
            break;
        }
        kentuckyCounter ++;
    }
    else
    {
        kentucky->setInitiated(true);
    }
}

void GameScreen::releaseFSU()
{
    if (fsu->getPosy() > 210 && fsu->getPosy() <= 270 && fsu->getPosx() == 260)
    {
        fsu->setPosy(fsu->getPosy() - 2);
    }
    else
    {
        fsu->setReleased(true);
    }
}

void GameScreen::releaseGeorgia()
{
    if (georgia->getPosy() > 210 && georgia->getPosy() <= 270 && georgia->getPosx() == 260)
    {
        georgia->setPosy(georgia->getPosy() - 5);
    }
    else
    {
        georgia->setReleased(true);
    }
}

void GameScreen::releaseLSU()
{
    if (lsu->getPosy() == 270 && lsu->getPosx() >= 220 && lsu->getPosx() < 260)
    {
        lsu->setPosx(lsu->getPosx() + 2);
    }
    else if (lsu->getPosy() > 210 && lsu->getPosy() <= 270 && lsu->getPosx() == 260)
    {
        lsu->setPosy(lsu->getPosy() - 2);
    }
    else
    {
        lsu->setReleased(true);
    }
}

void GameScreen::releaseKentucky()
{
    if (kentucky->getPosy() == 270 && kentucky->getPosx() > 260 && kentucky->getPosx() <= 300)
    {
        kentucky->setPosx(kentucky->getPosx() - 2);
    }
    else if (kentucky->getPosy() > 210 && kentucky->getPosy() <= 270 && kentucky->getPosx() == 260)
    {
        kentucky->setPosy(kentucky->getPosy() - 2);
    }
    else
    {
        kentucky->setReleased(true);
    }
}

void GameScreen::on_retryButton_clicked() {
    yesBtnClicked = true;
    win = false;
    resetGame();
}

void GameScreen::on_quitButton_clicked() {
    exit(0);
}

void GameScreen::ghostCollision() {

    if((abs(gator->getPosx() - fsu->getPosx()) <= 20) && (abs(gator->getPosy() - fsu->getPosy()) <= 20)) {
        collideWith(fsu);
    }
    else if ((abs(gator->getPosx() - georgia->getPosx()) <= 20) && (abs(gator->getPosy() - georgia->getPosy()) <= 20)) {
       collideWith(georgia);
    }
    else if ((abs(gator->getPosx() - lsu->getPosx()) <= 20) && (abs(gator->getPosy() - lsu->getPosy()) <= 20)) {
       collideWith(lsu);
    }
    else if ((abs(gator->getPosx() - kentucky->getPosx()) <= 20) && (abs(gator->getPosy() - kentucky->getPosy()) <= 20)) {
        collideWith(kentucky);
    }
}

void GameScreen::collideWith(Enemy *enemy)
{
    if (enemy->getMode() == Movement::FRIGHTENED)
    {

        score += mascotPoints;
        if (mascotPoints < 1600)
        {
            mascotPoints *= 2;
        }
        enemy->resetOrientation();
        enemy->setDefaultPosition();
    }
    else if (gator->getLives() > 1)
    {
        mascotPoints = 200;
        lostLife();
    }
    else
    {
        mascotPoints = 200;
        gator->setLives(0);
        win = false;
        gameOver();
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

    if (win == true) {
        winGame();
    }

    playerMove();
    enemiesMove();

    ui->lifeCount->display(gator->getLives());
    ui->scoreValue->display(score);

    ghostCollision();

    if (dots->points.isEmpty()) {
        win = true;
    }
    else
    {
        int pointsIndex = 0;
        for(QPoint point : dots->points)
        {
            if (gator->getPosx() == point.x() && gator->getPosy() == point.y()) {
                if ((point.x() == 10 && point.y() == 50) ||
                    (point.x() == 510 && point.y() == 50) ||
                    (point.x() == 10 && point.y() == 450) ||
                    (point.x() == 510 && point.y() == 450)) {
                    score += 50;

                    fsu->setMode(Movement::FRIGHTENED);
                    georgia->setMode(Movement::FRIGHTENED);
                    lsu->setMode(Movement::FRIGHTENED);
                    kentucky->setMode(Movement::FRIGHTENED);


                    frightTimer->start();
                    playFrightenMusic();
                }
                else {
                    score += 10;
                }
                dots->points.remove(pointsIndex);
                waka();
            }
            pointsIndex++;
        }
    }

    scene->update();
    gator->update();
    fsu->update();
    georgia->update();
    lsu->update();
    kentucky->update();
    dots->update();
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
            gator->setNextDirection(Direction::NONE);
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
            gator->setNextDirection(Direction::NONE);
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
            gator->setNextDirection(Direction::NONE);
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
            gator->setNextDirection(Direction::NONE);
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

void GameScreen::enemiesMove()
{
    releaseFSU();
    if (fsu->isReleased())
    {
        if (!fsu->isInitiated() && fsu->getMode() != Movement::FRIGHTENED)
            fsuInitSeq();

        fsu->move();
    }

    releaseGeorgia();
    if (georgia->isReleased())
    {
        if (!georgia->isInitiated() && georgia->getMode() != Movement::FRIGHTENED)
            georgiaInitSeq();

        georgia->move();
    }

    if(canReleaseLSU)
    {
        releaseLSU();
    }
    if (lsu->isReleased())
    {
        if (!lsu->isInitiated() && lsu->getMode() != Movement::FRIGHTENED)
            lsuInitSeq();

        lsu->move();
    }

    if (canReleaseKentucky)
    {
        releaseKentucky();
    }
    if (kentucky->isReleased())
    {
        if (!kentucky->isInitiated() && kentucky->getMode() != Movement::FRIGHTENED)
            kentuckyInitSeq();

        kentucky->move();
    }
}

void GameScreen::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Space:
        if (ui->pauseButton->isVisible() == true) {
            on_pauseButton_clicked();
        }
        else {
            on_resumeButton_clicked();
        }
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
