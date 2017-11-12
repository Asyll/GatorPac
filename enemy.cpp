#include "enemy.h"

Enemy::Enemy(int posx, int posy, QString name) :
    charW(40),
    charH(40)
{
    this->posx = posx;
    this->posy = posy;
    this->name = name;

    QString imageLocation = "://Images/Characters/" + name + "_forward.png";
    forward.load(imageLocation);
}

QRectF Enemy::boundingRect() const
{
    return QRect(0,0,charW,charH);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(posx,posy,charW,charH,forward);
}
