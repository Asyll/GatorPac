#include "player.h"
#include <iostream>

//class for the player (gatorpac)

//defines attributes for the player
Player::Player(int posx, int posy, int speed_) :
    speed(speed_),
    charW(40), //uses 40 for player's width
    charH(40)  //uses 40 for player's height
{
    this->posx = posx;
    this->posy = posy;
    defaultPosx = posx;
    defaultPosy = posy;
    this->facingDirection = Direction::RIGHT;

    lives = 3;
    moving = false;

    forward.load("://Images/Characters/gator_forward.png");
    reverse.load("://Images/Characters/gator_reverse.png");
    up.load("://Images/Characters/gator_forward_up.png");
    down.load("://Images/Characters/gator_forward_down.png");

}

//creates bounding rectangle for the player
QRectF Player::boundingRect() const
{
    return QRect(0,0,charW,charH);
}

//paints the player into the game for each direction it could be facing
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

//gets player's speed
int Player::getSpeed() const
{
    return speed;
}

//gets player's x-position
int Player::getPosx() const
{
    return posx;
}

//sets player's x-position
void Player::setPosx(int x)
{
    if (x >= 0 && x <= 520)
    {
        posx = x;
    }
}

//gets player's y-position
int Player::getPosy() const
{
    return posy;
}

//sets player's y-position
void Player::setPosy(int y)
{
    if (y >= 10 && y <= 570)
    {
        posy = y;
    }
}

//checks whether the player is moving
bool Player::isMoving() const
{
    return moving;
}

//sets player's movement speed
void Player::setMoving(bool value)
{
    moving = value;
}

//gets the ammount of lives the player has left
int Player::getLives() const
{
    return lives;
}

//sets the player's lives
void Player::setLives(int lives)
{
    if (lives >= 0 || lives <= 3)
    {
        this->lives = lives;
    }
}

//resets the the player's orientation to its default
void Player::resetOrientation()
{
    facingDirection = Direction::RIGHT;
    direction = Direction::NONE;
    nextDirection = Direction::NONE;
}

//sets the direction the player is facing
void Player::setDirection(Direction dir)
{
    facingDirection = dir;
}

//sets the next direction the player will face
void Player::setNextDirection(Direction dir)
{
    nextDirection = dir;
}

//sets the default x and y position for the player
void Player::setDefaultPosition()
{
    posx = defaultPosx;
    posy = defaultPosy;
}
