/* This class represents the player (gator). */

#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
public:
    Player(int posx,int posy,int speed);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int getLives() const;                               // Returns lives of Player
    void setLives(int lives);                           // Sets lives of Player

    void setDirection(Direction dir);                   // Sets current direcetion of Player
    void setNextDirection(Direction dir);               // Sets next direction Player will move

private:
    QPixmap forward, reverse, up, down;                 // Images for each direction

    int lives;                                          // # of lives Player has
};

#endif // PLAYER_H
