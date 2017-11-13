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
}

QRectF Player::boundingRect() const
{
    return QRect(0,0,charW,charH);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(posx,posy,charW,charW,forward);
}

int Player::getSpeed() const
{
    return speed;
}
