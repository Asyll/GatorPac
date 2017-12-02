#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QString>
#include <QSound>
#include "gamemap.h"
#include "player.h"
#include "enemy.h"

namespace Ui {
class GameScreen;
}

class GameScreen : public QWidget
{
    Q_OBJECT
public:
    explicit GameScreen(QWidget *parent = 0);
    ~GameScreen();



private:
    Ui::GameScreen *ui;
    QGraphicsScene *scene;
    GameMap *gameMap;
    QTimer *timer;
    QTimer *frightTimer;
    QTimer *lsuReleaseTimer;
    QTimer *kentuckyReleaseTimer;
    QMediaPlaylist *playlist = new QMediaPlaylist();
    QMediaPlaylist *wakaPlaylist = new QMediaPlaylist();
    QMediaPlayer *wakaSound = new QMediaPlayer;
    QMediaPlayer *basicSounds = new QMediaPlayer;
    QMediaPlayer *frightenSound = new QMediaPlayer;
    QMediaPlayer *deathMusic = new QMediaPlayer;
    QMediaPlayer *winMusic = new QMediaPlayer;
    QMediaPlayer *backgroundMusic = new QMediaPlayer;

    Player *gator;
    Enemy *lsu;
    Enemy *fsu;
    Enemy *georgia;
    Enemy *kentucky;

    Dots *dots;

    int score;
    bool win = false;
    bool yesBtnClicked = false;
    bool canReleaseLSU = false;
    bool canReleaseKentucky = false;

    Direction currentTmpDir;
    Direction nextTmpDir;


    void playBackgroundMusic();
    void playWakaSound();
    void playGatorWaka();
    void playFrightenMusic();
    void playDeathMusic();
    void playWinMusic();

    void playerMove();
    void enemiesMove();
    void lostLife();
    void waka();
    void ghostCollision();
    void collideWith(Enemy *enemy);
    void gameOver();
    void winGame();
    void resetGame();
    void resetCharacters();

    void fsuInitSeq();
    void georgiaInitSeq();
    void lsuInitSeq();
    void kentuckyInitSeq();

    void releaseFSU();
    void releaseGeorgia();
    void releaseLSU();
    void releaseKentucky();

    void keyPressEvent(QKeyEvent *event);

    // Used for timing initial mode changes
    int fsuCounter;
    int georgiaCounter;
    int lsuCounter;
    int kentuckyCounter;
    int mascotPoints;

private slots:
    void updater();
    void on_musicButton_clicked();
    void on_muteButton_clicked();
    void on_retryButton_clicked();
    void on_quitButton_clicked();
    void on_pauseButton_clicked();
    void on_resumeButton_clicked();
    void lsuAvailable();
    void kentuckyAvailable();
    void wakaOff();
    void end_fright();
};

#endif // GAMESCREEN_H
