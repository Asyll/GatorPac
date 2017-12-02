#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include "direction.h"

class Player : public QGraphicsItem
{
public:
    Player(int posx,int posy,int speed_);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getSpeed() const;

    int getPosx() const; //gets x-position for player
    void setPosx(int x); //sets x-position for player

    int getPosy() const; //gets y-position for player
    void setPosy(int y); //sets y-position for player

    bool isMoving() const; //checks if player is moving
    void setMoving(bool value); //sets whether player is moving or not

    int getLives() const; //gets the total lives that the player has
    void setLives(int lives); //sets the lives for the player

    void resetOrientation(); //resets the orientation for the player
    void setDefaultPosition(); //sets the default position for the player

    void setDirection(Direction dir); //sets direcetion of the player

    void setNextDirection(Direction dir); //sets the next direction for the player

private:
    QPixmap forward, reverse, up, down;
    const int speed;
    Direction direction, nextDirection, facingDirection;
    bool moving;

    // Position in pixels
    int posx, posy;
    int defaultPosx, defaultPosy;

    // Image dimension in pixels
    const int charW, charH;

    int lives;
};

#endif // PLAYER_H
