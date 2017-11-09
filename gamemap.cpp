#include "gamemap.h"

GameMap::GameMap()
{
    mapImage.load(":/Images/swampmap.png");
}

QRectF GameMap::boundingRect() const
{
    return QRect(0,0,717,794);
}

void GameMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,717,794,mapImage);
}
