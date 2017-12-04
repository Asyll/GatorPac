#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QThread>
#include <QString>
#include <QSound>
#include <cmath>
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

    QTimer *timer;                                          // Timer for updating game frames (30 fps)
    QTimer *frightTimer;                                    // Timer for ending FRIGHTENED mode
    QTimer *lsuReleaseTimer;                                // Timer to release LSU Enemy from the box
    QTimer *kentuckyReleaseTimer;                           // Timer to release Kentucky Enemy from the box

    QMediaPlaylist *playlist;                               // Playlist for playing game background music, win music and death music
    QMediaPlaylist *wakaPlaylist;                           // Seperate playlist to play background music and "waka" sound simultaenously

    QMediaPlayer *wakaSound;                                // Player for each sound
    QMediaPlayer *basicSounds;
    QMediaPlayer *frightenSound;
    QMediaPlayer *deathMusic;
    QMediaPlayer *winMusic;
    QMediaPlayer *backgroundMusic;

    Player *gator;                                          // Player
    Enemy *fsu;                                             // Florida State University
    Enemy *lsu;                                             // Louisiana State University
    Enemy *georgia;                                         // University of Georgia
    Enemy *kentucky;                                        // University of Kentucky

    Dots *dots;

    Direction currentTmpDir;                                // Temporary current Player direction
    Direction nextTmpDir;                                   // Temporary next Player direction

    int score;                                              // Game score
    bool won;
    bool yesBtnClicked;
    bool canReleaseLSU;
    bool canReleaseKentucky;

    int fsuCounter;                                         // Used for timing initial mode changes
    int georgiaCounter;
    int lsuCounter;
    int kentuckyCounter;
    int mascotPoints;



    // MUSIC

    void playBackgroundMusic();                             // Play indicated sound
    void playWakaSound();
    void playFrightenMusic();
    void playDeathMusic();
    void playWinMusic();

    void triggerWaka();                                     // Triggers the waka sound



    // MOVEMENT

    void playerMove();                                      // Player movement mechanics
    void enemiesMove();                                     // Enemy general movement controls

    void fsuInitSeq();                                      // Initial movement sequences for each Enemy
    void georgiaInitSeq();
    void lsuInitSeq();
    void kentuckyInitSeq();

    void releaseFSU();                                      // Releases Enemy from the box
    void releaseGeorgia();
    void releaseLSU();
    void releaseKentucky();



    // INTERACTIONS

    void ghostCollision();                                  // Checks for collision between Player and Enemies
    void collideWith(Enemy *enemy);                         // Handles collision between Player and given Enemy
    void dotCollision();                                    // Checks for collision between Player and Dots


    // OTHER

    void lostLife();                                        // Handles when Player loses a life
    void resetGame();                                       // Restarts game
    void resetCharacters();                                 // Resets all Entities (characters) to original position and conditions

    void winGame();                                         // Win sequence
    void gameOver();                                        // Game Over sequence

    void keyPressEvent(QKeyEvent *event);



    // SLOTS
private slots:
    void updater();                                         // Game updater

    void on_musicButton_clicked();
    void on_muteButton_clicked();
    void on_retryButton_clicked();
    void on_quitButton_clicked();

    void lsuAvailable();                                    // Allows LSU to be released
    void kentuckyAvailable();                               // Alows Kentucky to be released
    void wakaOff();
    void end_fright();                                      // Ends FRIGHTENED mode
};

#endif // GAMESCREEN_H
