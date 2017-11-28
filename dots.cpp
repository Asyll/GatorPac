#include "dots.h"
#include <QGraphicsItem>
#include <QPainter>



Dots::Dots(int posx, int posy):
    dotH(20),
    dotW(20)
{
    this->posx = posx;
    this->posy = posy;
    dot.load("://Images/timdots.png");
}
void Dots::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(posx, posy, dotW, dotH, dot);
}

QRectF Dots::boundingRect() const
{
    return QRect(0,0,dotW,dotH);
}

int Dots::getPosx() const
{
    return posx;
}

void Dots::setPosx(int x)
{
    if (x >= 0 && x <= 520)
    {
        posx = x;
    }
}

int Dots::getPosy() const
{
    return posy;
}

void Dots::setPosy(int y)
{
    if (y >= 10 && y <= 570)
    {
        posy = y;
    }
}


