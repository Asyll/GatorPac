#include "player.h"
#include <iostream>

Player::Player(int posx, int posy, int speed) :
    Entity::Entity(posx, posy, speed)
{
    lives = 3;

    // Load images for different directions
    forward.load("://Images/Characters/gator_forward.png");
    reverse.load("://Images/Characters/gator_reverse.png");
    up.load("://Images/Characters/gator_forward_up.png");
    down.load("://Images/Characters/gator_forward_down.png");
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    switch(facingDirection)
    {
    case LEFT:
        painter->drawPixmap(posx,posy,charW,charW,reverse);
        break;
    case RIGHT:
        painter->drawPixmap(posx,posy,charW,charW,forward);
        break;
    case UP:
        painter->drawPixmap(posx,posy,charW,charW,up);
        break;
    case DOWN:
        painter->drawPixmap(posx,posy,charW,charW,down);
        break;
    case NONE:
        painter->drawPixmap(posx,posy,charW,charW,forward);
        break;
    }
}

int Player::getLives() const
{
    return lives;
}

void Player::setLives(int lives)
{
    if (lives >= 0 || lives <= 3)
    {
        this->lives = lives;
    }
}

void Player::setDirection(Direction dir)
{
    facingDirection = dir;
}

void Player::setNextDirection(Direction dir)
{
    nextDirection = dir;
}
