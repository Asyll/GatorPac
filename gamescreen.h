#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QMediaPlaylist>
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
    QMediaPlaylist *playlist = new QMediaPlaylist();
    QMediaPlayer *finalDeathMusic = new QMediaPlayer;
    QMediaPlayer *finalWinMusic = new QMediaPlayer;

    Player *gator;
    Enemy *lsu;
    Enemy *fsu;
    Enemy *georgia;
    Enemy *kentucky;

    int score;
    bool win = false;

    Direction currentTmpDir;
    Direction nextTmpDir;


    void playBackgroundMusic();
    void playGatorWaka();
    //void start();
    void playDeathMusic();
    void playWinMusic();

    void playerMove();
    void lostLife();
    void ghostCollision();
    void gameOver();


    void keyPressEvent(QKeyEvent *event);

private slots:
    void updater();
    void on_musicButton_clicked();

};

#endif // GAMESCREEN_H
