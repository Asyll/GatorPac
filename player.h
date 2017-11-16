#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QPainter>
#include "direction.h"

class Player : public QGraphicsItem
{
public:
    Player(int posx,int posy,int speed);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getSpeed() const;
    void setDirection(Direction direction);

    int getPosx() const;
    void setPosx(int x);

    int getPosy() const;
    void setPosy(int y);

    bool isMoving() const;
    void setMoving(bool value);

    int getLives() const;
    void setLives(int lives);

private:
    QPixmap forward, reverse, up, down;
    int speed;
    Direction direction;
    bool moving;

    // Position in pixels
    int posx, posy;
    // Image dimension in pixels
    const int charW, charH;

    int lives;
};

#endif // PLAYER_H
