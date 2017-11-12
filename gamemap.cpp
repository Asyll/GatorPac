#include "gamemap.h"

// PUBLIC Functions //
GameMap::GameMap()
{
    mapImage.load(":/Images/swampmap.png");

    createPathPoints(110,450,410,450);
}

QRectF GameMap::boundingRect() const
{
    return QRect(0,0,560,620);
}

void GameMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,560,620,mapImage);
}

bool GameMap::canMove(QPoint point)
{
    for (int i = 0; i < moveablePath.length(); i++)
    {
        if (moveablePath[i] == point)
        {
            return true;
        }
    }
    return false;
}

// PRIVATE Functions //

// Creates the points on which characters will move
void GameMap::createPathPoints(int startx, int starty, int endx, int endy)
{
    QPoint point;
    // If the line is horizontal
    if (starty == endy)
    {
        // If line is given from left to right
        if (startx < endx)
        {
            for (int x = startx; x <= endx; x++)
            {
                point.setX(x);
                point.setY(starty);
                if (!moveablePath.contains(point))
                {
                    moveablePath.append(point);
                }
            }
        }
        else
        {
            for (int x = startx; x >= startx; x--)
            {
                point.setX(x);
                point.setY(starty);
                if (!moveablePath.contains(point))
                {
                    moveablePath.append(point);
                }
            }
        }
    }
    else
    {
        // If line is given bottom to top
        if (starty < endy)
        {
            for (int y = starty; y <= endy; y++)
            {
                point.setY(y);
                point.setX(startx);
                if (!moveablePath.contains(point))
                {
                    moveablePath.append(point);
                }
            }
        }
        else
        {
            for (int y = starty; y >= starty; y--)
            {
                point.setY(y);
                point.setX(startx);
                if (!moveablePath.contains(point))
                {
                    moveablePath.append(point);
                }
            }
        }
    }
}
