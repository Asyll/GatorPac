#include "player.h"
#include <iostream>

Player::Player(int posx, int posy, int speed) :
    Entity::Entity(posx, posy, speed)
{
    lives = 3;

    // Load images for different directions
    forward.load("://Images/Characters/gator_forward.png");
    forward2.load("://Images/Characters/gator_forward2.png");
    reverse.load("://Images/Characters/gator_reverse.png");
    reverse2.load("://Images/Characters/gator_reverse2.png");
    up.load("://Images/Characters/gator_forward_up.png");
    up2.load("://Images/Characters/gator_forward_up2.png");
    down.load("://Images/Characters/gator_forward_down.png");
    down2.load("://Images/Characters/gator_forward_down2.png");
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    switch(facingDirection)
    {
    case LEFT:
        if (state > 2)
        {
            if (state > 4)
                state = 0;

            painter->drawPixmap(posx,posy,charW,charW,reverse2);
        }
        else
        {
            painter->drawPixmap(posx,posy,charW,charW,reverse);
        }
        break;
    case RIGHT:
        if (state > 2)
        {
            if (state > 4)
                state = 0;

            painter->drawPixmap(posx,posy,charW,charW,forward2);
        }
        else
        {
            painter->drawPixmap(posx,posy,charW,charW,forward);
        }
        break;
    case UP:
        if (state > 2)
        {
            if (state > 4)
                state = 0;

            painter->drawPixmap(posx,posy,charW,charW,up2);
        }
        else
        {
            painter->drawPixmap(posx,posy,charW,charW,up);
        }
        break;
    case DOWN:
        if (state > 2)
        {
            if (state > 4)
                state = 0;

            painter->drawPixmap(posx,posy,charW,charW,down2);
        }
        else
        {
            painter->drawPixmap(posx,posy,charW,charW,down);
        }
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
