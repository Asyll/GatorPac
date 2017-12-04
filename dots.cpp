#include "Dots.h"

Dots::Dots(const QVector<QPoint>* points) :
    maxDots(points->length())
{
    setPoints(points);

    // Load dot images
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
        // Location for power dots (large dots)
        if ((point.x() == 10 && point.y() == 50)    ||
            (point.x() == 510 && point.y() == 50)   ||
            (point.x() == 10 && point.y() == 450)   ||
            (point.x() == 510 && point.y() == 450)   )
        {
            painter->drawPixmap(point.x(), point.y(), dotW, dotH, largeDotImg);
        }
        // Regular dots
        else
        {
            painter->drawPixmap(point.x(), point.y(), dotW, dotH, dotImg);
        }
    }
}

void Dots::setPoints(const QVector<QPoint>* points)
{
    this->points.clear();       // Clears current points to reset map
    if (!points->isEmpty())
    {
        this->points = *points;
    }
}
