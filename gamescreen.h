#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QMediaPlayer>
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

    QMediaPlayer * finalDeathMusic = new QMediaPlayer;
    //void start();
    void playDeathMusic();

    int score;
    int lives = 3;

private:
    Ui::GameScreen *ui;
    QGraphicsScene *scene;
    GameMap *gameMap;
    Player *gator;
    Enemy *lsu;
    Enemy *fsu;
    Enemy *georgia;
    Enemy *kentucky;

    //QTimer *timer;

public slots:
    void updater();

protected:
    void keyPressEvent(QKeyEvent *event);

};

#endif // GAMESCREEN_H
