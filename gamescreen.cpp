#include "gamescreen.h"
#include "ui_gamescreen.h"

GameScreen::GameScreen(QWidget *parent) : QWidget(parent), ui(new Ui::GameScreen)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,560,620);

    QGraphicsView *gameView = ui->gameView;
    gameView->setScene(scene);
    gameView->setRenderHint(QPainter::Antialiasing);
    gameView->setSceneRect(scene->sceneRect());

    ui->retryLabel->setVisible(false);
    ui->retryButton->setVisible(false);
    ui->quitButton->setVisible(false);
    ui->resumeButton->setVisible(false);
    ui->pauseButton->setVisible(false);
    ui->scoreLabel2->setVisible(false);
    ui->scoreValue2->setVisible(false);
    ui->winLabel->setVisible(false);




    // Create map
    gameMap = new GameMap();
    scene->addItem(gameMap);

    // Create dots
    dots = new Dots(gameMap->getDotVector());
    scene->addItem(dots);




    // Initialize game updater timer (30 fps)
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updater()));
    timer->start(1000/30);

    // Initialize FRIGHTENED mode timer (10 seconds)
    frightTimer = new QTimer(this);
    frightTimer->setInterval(10000);
    frightTimer->setSingleShot(true);
    connect(frightTimer, SIGNAL(timeout()), this, SLOT(end_fright()));

    // Initialize LSU timer (4 seconds)
    lsuReleaseTimer = new QTimer(this);
    lsuReleaseTimer->setInterval(4000);
    lsuReleaseTimer->setSingleShot(true);
    connect(lsuReleaseTimer, SIGNAL(timeout()), this, SLOT(lsuAvailable()));
    lsuReleaseTimer->start();

    // Initialize Kentucky timer (10 seconds)
    kentuckyReleaseTimer = new QTimer(this);
    kentuckyReleaseTimer->setInterval(10000);
    kentuckyReleaseTimer->setSingleShot(true);
    connect(kentuckyReleaseTimer, SIGNAL(timeout()), this, SLOT(kentuckyAvailable()));
    kentuckyReleaseTimer->start();




    // Initialize player
    gator = new Player(260,450,5);
    gator->setZValue(4);
    scene->addItem(gator);

    // Initialize FSU
    fsu = new Enemy(260,210,5,"fsu", gameMap, gator, EnemyType::RED);
    fsu->setZValue(5);
    scene->addItem(fsu);

    // Initialize LSU
    lsu = new Enemy(220,270,5,"lsu", gameMap, gator, EnemyType::BLUE);
    lsu->setZValue(5);
    scene->addItem(lsu);

    // Initialize Georgia
    georgia = new Enemy(260,270,5,"georgia", gameMap, gator, EnemyType::PINK);
    georgia->setZValue(5);
    scene->addItem(georgia);

    // Initialize Kentucky
    kentucky = new Enemy(300,270,5,"kentucky", gameMap, gator, EnemyType::ORANGE);
    kentucky->setZValue(5);
    scene->addItem(kentucky);




    // Initialize music
    playlist = new QMediaPlaylist();
    wakaPlaylist = new QMediaPlaylist();

    wakaSound = new QMediaPlayer();
    basicSounds = new QMediaPlayer();
    frightenSound = new QMediaPlayer();
    deathMusic = new QMediaPlayer();
    winMusic = new QMediaPlayer();
    backgroundMusic = new QMediaPlayer();


    // Game attributes
    fsuCounter = 0;
    georgiaCounter = 0;
    lsuCounter = 0;
    kentuckyCounter = 0;

    score = 0;

    mascotPoints = 200;

    won = false;
    yesBtnClicked = false;
    canReleaseLSU = false;
    canReleaseKentucky = false;

    currentTmpDir = Direction::NONE;
    nextTmpDir= Direction::NONE;


    playBackgroundMusic();
    playWakaSound();
}

GameScreen::~GameScreen()
{
    delete ui;
    delete scene;
    delete gameMap;
    delete timer;
    delete frightTimer;
    delete lsuReleaseTimer;
    delete kentuckyReleaseTimer;
    delete playlist;
    delete wakaPlaylist;
    delete wakaSound;
    delete basicSounds;
    delete frightenSound;
    delete deathMusic;
    delete winMusic;
    delete backgroundMusic;
    delete gator;
    delete fsu;
    delete lsu;
    delete georgia;
    delete kentucky;
    delete dots;
}


// MUSIC

void GameScreen::playBackgroundMusic()
{
    playlist->clear();
    playlist->addMedia(QUrl("qrc:/Audio/GameScreenMusic.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    backgroundMusic->setPlaylist(playlist);
    backgroundMusic->setVolume(50);
    backgroundMusic->play();
}

void GameScreen::playWakaSound()
{
    wakaPlaylist->clear();
    wakaPlaylist->addMedia(QUrl("qrc:/Audio/PacmanChomp.mp3"));
    wakaPlaylist->setPlaybackMode(QMediaPlaylist::Loop);

    wakaSound->setPlaylist(wakaPlaylist);
    wakaSound->setVolume(0);
    wakaSound->play();
}

void GameScreen::playFrightenMusic()
{
    frightenSound->setMedia(QUrl("qrc:/Audio/sonicDrowning.mp3"));
    if (frightenSound->state() == QMediaPlayer::PlayingState) {
        frightenSound->setPosition(0);
    }
    else if (frightenSound->state() == QMediaPlayer::StoppedState) {
        frightenSound->setVolume(40);
        frightenSound->play();
    }
    backgroundMusic->setVolume(0);

}

void GameScreen::playDeathMusic()
{
    playlist->clear();
    playlist->addMedia(QUrl("qrc:/Audio/FinalDeathMusic.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    deathMusic->setPlaylist(playlist);
    deathMusic->play();
}

void GameScreen::playWinMusic()
{
    playlist->clear();
    playlist->addMedia(QUrl("qrc:/Audio/September.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    winMusic->setPlaylist(playlist);
    winMusic->play();
}

void GameScreen::triggerWaka()
{
    wakaSound->setVolume(30);
    QTimer::singleShot(613, this, SLOT(wakaOff()));
}



// MOVEMENT

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

    //?
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
        //starts movement for FSU
        if (!fsu->isInitiated() && fsu->getMode() != Movement::FRIGHTENED)
            fsuInitSeq();

        fsu->move();
    }

    releaseGeorgia();
    if (georgia->isReleased())
    {
        //starts movement for Georgia
        if (!georgia->isInitiated() && georgia->getMode() != Movement::FRIGHTENED)
            georgiaInitSeq();

        georgia->move();
    }

    if(canReleaseLSU) //checks if LSU can be released then releases them if possible
    {
        releaseLSU();
    }
    if (lsu->isReleased())
    {
        //starts movement for LSU
        if (!lsu->isInitiated() && lsu->getMode() != Movement::FRIGHTENED)
            lsuInitSeq();

        lsu->move();
    }

    if (canReleaseKentucky) //checks if Kentucky can be released then releases them if possible
    {
        releaseKentucky();
    }
    if (kentucky->isReleased())
    {
        //starts movement for Kentucky
        if (!kentucky->isInitiated() && kentucky->getMode() != Movement::FRIGHTENED)
            kentuckyInitSeq();

        kentucky->move();
    }
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
        default:
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
        default:
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
        default:
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
        default:
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



// INTERACTIONS

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
    if (enemy->getMode() == Movement::FRIGHTENED) //if player collides with ghost in frightened mode, ghost goes to spawn box
    {

        score += mascotPoints;
        if (mascotPoints < 1600)
        {
            mascotPoints *= 2;
        }
        enemy->resetOrientation();
        enemy->setDefaultPosition();
    }
    else if (gator->getLives() > 1) //if player collides with ghost in normal mode, player loses a life if they have more than one
    {
        mascotPoints = 200;
        lostLife();
    }
    else //ends game when player collides with ghost, having only one life left
    {
        mascotPoints = 200;
        gator->setLives(0);
        won = false;
        gameOver();
    }
}



// OTHER

void GameScreen::lostLife()
{
    basicSounds->setMedia(QUrl("qrc:/Audio/pacmanDeath.mp3"));
    if (basicSounds->state() == QMediaPlayer::PlayingState) {
        basicSounds->setPosition(0);
    }
    else if (basicSounds->state() == QMediaPlayer::StoppedState) {
        basicSounds->setVolume(40);
        basicSounds->play();
    }

    if (frightenSound->state() == QMediaPlayer::PlayingState) {
            frightenSound->setVolume(0);
            backgroundMusic->setVolume(40);
        }

    gator->setLives(gator->getLives() - 1);

    resetCharacters();
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
    //ui->pauseButton->setVisible(true);
    ui->scoreLabel->setVisible(true);
    ui->scoreValue->setVisible(true);

    resetCharacters();

    gator->setLives(3);
    score = 0;
    mascotPoints = 200;

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
    if (frightenSound->state() != QMediaPlayer::PlayingState) {
        frightenSound->setVolume(40);
    }
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

void GameScreen::winGame() {
    frightenSound->setVolume(0);
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
    //ui->pauseButton->setVisible(false);
    //ui->resumeButton->setVisible(false);
    ui->scoreLabel->setVisible(false);
    ui->scoreValue->setVisible(false);
}

void GameScreen::gameOver() {
    frightenSound->setVolume(0);
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
    //ui->pauseButton->setVisible(false);
    //ui->resumeButton->setVisible(false);
    ui->scoreLabel->setVisible(false);
    ui->scoreValue->setVisible(false);
}

void GameScreen::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Space: //pressing space mutes the game
        if (ui->muteButton->isVisible() == true) {
            on_muteButton_clicked();
        }
        else {
            on_musicButton_clicked();
        }
        break;
    case Qt::Key_A: //pressing the 'A' key moves the player to the left
        if (!gator->isMoving())
        {
            currentTmpDir = Direction::LEFT;
        }
        else
        {
            nextTmpDir = Direction::LEFT;
        }
        break;
    case Qt::Key_D: //pressing the 'D' key moves the player to the right
        if (!gator->isMoving())
        {
            currentTmpDir = Direction::RIGHT;
        }
        else
        {
            nextTmpDir = Direction::RIGHT;
        }
        break;
    case Qt::Key_W: //pressing the 'W' key moves the player upwards
        if (!gator->isMoving())
        {
            currentTmpDir = Direction::UP;
        }
        else
        {
            nextTmpDir = Direction::UP;
        }
        break;
    case Qt::Key_S: //pressing the 'S' key moves the player downwards
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



// SLOTS

void GameScreen::updater() {
    /* For debugging character position:
     * - unhide xPos and yPos
     * - uncomment the display functions */
    ui->xPos->hide();
    ui->yPos->hide();
    //ui->xPos->display(gator->getPosx());
    //ui->yPos->display(gator->getPosy());

    //if player wins game display the wins screen
    if (won == true) {
        winGame();
    }

    playerMove();
    enemiesMove();

    ui->lifeCount->display(gator->getLives());
    ui->scoreValue->display(score);

    ghostCollision();

    //player wins game when all dots are eaten
    if (dots->points.isEmpty()) {
        won = true;
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
                triggerWaka();
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

void GameScreen::on_musicButton_clicked()
{
    if (dots->points.isEmpty()) {
        playWinMusic();
    }
    else if (gator->getLives() == 0 && !won) {
        playDeathMusic();
    }
    else {
        if (frightenSound->state() != QMediaPlayer::PlayingState) {
                playBackgroundMusic();
            }

    }
    ui->musicButton->setVisible(false);
    ui->muteButton->setVisible(true);
}

void GameScreen::on_muteButton_clicked()
{
    if (frightenSound->state() != QMediaPlayer::PlayingState || ui->retryLabel->isVisible() == true) {
        playlist->clear();
    }
    ui->muteButton->setVisible(false);
    ui->musicButton->setVisible(true);
}

void GameScreen::on_retryButton_clicked()
{
    yesBtnClicked = true;
    won = false;
    resetGame();
}

void GameScreen::on_quitButton_clicked()
{
    exit(0);
}

void GameScreen::lsuAvailable()
{
    canReleaseLSU = true;
}

void GameScreen::kentuckyAvailable()
{
    canReleaseKentucky = true;
}

void GameScreen::wakaOff()
{
    wakaSound->setVolume(0);
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

    backgroundMusic->setVolume(50);
    mascotPoints = 200;
}
