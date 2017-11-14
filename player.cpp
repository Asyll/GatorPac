#include "player.h"

Player::Player(int posx, int posy, int speed = 0) :
    charW(40),
    charH(40)
{
    this->posx = posx;
    this->posy = posy;
    this->speed = speed;
    moving = false;
    forward.load("://Images/Characters/gator_forward.png");
    reverse.load("://Images/Characters/gator_reverse.png");
    up.load("://Images/Characters/gator_forward_up.png");
    down.load("://Images/Characters/gator_forward_down.png");

}

QRectF Player::boundingRect() const
{
    return QRect(0,0,charW,charH);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    switch(direction)
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

int Player::getSpeed() const
{
    return speed;
}

void Player::setDirection(Direction direction)
{
    this->direction = direction;
}
