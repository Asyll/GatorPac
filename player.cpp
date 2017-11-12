#include "player.h"

Player::Player(int posx, int posy) :
    charW(40),
    charH(40)
{
    this->posx = posx;
    this->posy = posy;
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
