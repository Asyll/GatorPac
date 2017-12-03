#include "Dots.h"
#include <iostream>

//class that implements the dots on the map for gatorpac to eat

Dots::Dots(const QVector<QPoint>* points):
    dotW(40), //uses 40 as dot's width
    dotH(40), //uses 40 as dot's height
    maxDots(points->length())
{
    //loads the two different types of dots
    setPoints(points);

    dotImg.load("://Images/timdots.png");
    largeDotImg.load("://Images/gabedots.png");
}

//sets up the bounding rectangle for the dots
QRectF Dots::boundingRect() const
{
    return QRect(0,0,dotW,dotH);
}

//method that paints both large and small dots on the gamemap
void Dots::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for (QPoint point : points)
    {
        //paints large dots at 4 specific positions
        if ((point.x() == 10 && point.y() == 50)    ||
            (point.x() == 510 && point.y() == 50)   ||
            (point.x() == 10 && point.y() == 450)   ||
            (point.x() == 510 && point.y() == 450)   )
        {
            painter->drawPixmap(point.x(), point.y(), dotW, dotH, largeDotImg);
        }
        else
        {
            //paints small dots in the rest of the slots
            painter->drawPixmap(point.x(), point.y(), dotW, dotH, dotImg);
        }
    }
}

//?
void Dots::setPoints(const QVector<QPoint>* points)
{
    this->points.clear();
    if (!points->isEmpty())
    {
        this->points = *points;
    }
}
