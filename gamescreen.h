#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
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
    void resizeEvent(QResizeEvent *);

public:
    explicit GameScreen(QWidget *parent = 0);
    ~GameScreen();
};

#endif // GAMESCREEN_H
