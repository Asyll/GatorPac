#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include "gamemap.h"

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

public:
    explicit GameScreen(QWidget *parent = 0);
    QMediaPlayer * finalDeathMusic = new QMediaPlayer;
    ~GameScreen();
};

#endif // GAMESCREEN_H
