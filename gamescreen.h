#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include "gamemap.h"
#include "player.h"

namespace Ui {
class GameScreen;
}

class GameScreen : public QWidget
{
    Q_OBJECT
private:
    Ui::GameScreen *ui;
    QGraphicsScene *scene;
    GameMap *gameMap;

    Player *gator;

public:
    explicit GameScreen(QWidget *parent = 0);
    ~GameScreen();

    QMediaPlayer * finalDeathMusic = new QMediaPlayer;
    void playDeathMusic();
};

#endif // GAMESCREEN_H
