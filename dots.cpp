#include "Dots.h"
#include <iostream>

Dots::Dots(const QVector<QPoint>* points):
    dotW(40),
    dotH(40),
    maxDots(points->length())
{
    setPoints(points);

    dotImg.load("://Images/timdots.png");
    largeDotImg.load("://Images/gabedots.png");
}

QRectF Dots::boundingRect() const
{
    return QRect(0,0,dotW,dotH);
}

void Dots::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for (QPoint point : points)
    {
        if ((point.x() == 10 && point.y() == 50)    ||
            (point.x() == 510 && point.y() == 50)   ||
            (point.x() == 10 && point.y() == 450)   ||
            (point.x() == 510 && point.y() == 450)   )
        {
            painter->drawPixmap(point.x(), point.y(), dotW, dotH, largeDotImg);
        }
        else
        {
            painter->drawPixmap(point.x(), point.y(), dotW, dotH, dotImg);
        }
    }
}

void Dots::setPoints(const QVector<QPoint>* points)
{
    this->points.clear();
    if (!points->isEmpty())
    {
        this->points = *points;
    }
}

int Dots::dotsConsumed()
{
    return maxDots - points.length();
}
