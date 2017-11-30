#include "Dots.h"
#include <iostream>

Dots::Dots(const QVector<QPoint>* points):
    dotW(40),
    dotH(40)
{
    setPoints(points);

    dotImg.load("://Images/timdots.png");
}

QRectF Dots::boundingRect() const
{
    return QRect(0,0,dotW,dotH);
}

void Dots::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for (QPoint point : points)
    {
        painter->drawPixmap(point.x(), point.y(), dotW, dotH, dotImg);
    }
}

void Dots::setPoints(const QVector<QPoint>* points)
{
    if (!points->isEmpty())
    {
        this->points = *points;
    }
}
