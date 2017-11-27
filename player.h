#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include "gamemap.h"
#include "direction.h"

class Player : public QGraphicsItem
{
public:
    Player(int posx,int posy,int speed_);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getSpeed() const;

    int getPosx() const;
    void setPosx(int x);

    int getPosy() const;
    void setPosy(int y);

    bool isMoving() const;
    void setMoving(bool value);

    int getLives() const;
    void setLives(int lives);

    void resetOrientation();

    void setDirection(Direction dir);

    void setNextDirection(Direction dir);

private:
    QPixmap forward, reverse, up, down;
    const int speed;
    Direction direction, nextDirection, facingDirection;
    bool moving;

    // Position in pixels
    int posx, posy;
    // Image dimension in pixels
    const int charW, charH;

    int lives;
};

#endif // PLAYER_H
