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
    QMediaPlaylist *playlist = new QMediaPlaylist();
    QMediaPlayer *wakaSound = new QMediaPlayer;
    QMediaPlayer *basicSounds = new QMediaPlayer;
    QMediaPlayer *finalDeathMusic = new QMediaPlayer;
    QMediaPlayer *finalWinMusic = new QMediaPlayer;

    Player *gator;
    Enemy *lsu;
    Enemy *fsu;
    Enemy *georgia;
    Enemy *kentucky;

    Dots *dots;

    int score;
    bool win = false;
    bool yesBtnClicked = false;
    bool frighten = false;
    bool canReleaseLSU = false;
    bool canReleaseKentucky = false;

    Direction currentTmpDir;
    Direction nextTmpDir;


    void playBackgroundMusic();
    void playGatorWaka();
    //void start();
    void playDeathMusic();
    void playWinMusic();

    void playerMove();
    void lostLife();
    void waka();
    void ghostCollision();
    void gameOver();
    void winGame();
    void resetGame();
    void resetCharacterPositions();

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
    void on_yesButton_clicked();
    void on_noButton_clicked();
    void on_pauseButton_clicked();
    void on_resumeButton_clicked();
    void lsuAvailable();
    void kentuckyAvailable();
    void end_fright();
};

#endif // GAMESCREEN_H
