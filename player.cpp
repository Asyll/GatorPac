#include "player.h"

Player::Player()
{
    forward.load("://Images/Characters/Gator/gator_forward.png");
}

QRectF Player::boundingRect() const
{
    return QRect(0,0,50,50);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,50,50,forward);
}
