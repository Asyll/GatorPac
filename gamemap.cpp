#include "gamemap.h"
#include <iostream>

// PUBLIC Functions //
GameMap::GameMap()
{
    mapImage.load(":/Images/swampmap.png");

    makeMapPaths();
}

QRectF GameMap::boundingRect() const
{
    return QRect(0,0,560,620);
}

void GameMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,560,620,mapImage);

    for (QPoint point : dotLocations)
    {
        painter->drawPoint(point);
    }

    /* Draw debug paths
    for (QPoint point : moveablePath)
    {
        painter->drawPoint(point);
    }
    */
}

bool GameMap::canMove(QPoint point)
{
    for (int i = 0; i < moveablePath.size(); i++)
    {
        if (moveablePath[i] == point)
        {
            return true;
        }
    }
    return false;
}

// PRIVATE Functions //

// Creates all the moveable paths on the game map
void GameMap::makeMapPaths()
{
    // Horizontal paths
    // Top
    createDotPoints(10,10,230,10);
    createDotPoints(290,10,510,10);
    createDotPoints(10,90,510,90);
    createDotPoints(10,150,110,150);
    createDotPoints(170,150,230,150);
    createDotPoints(170,210,350,210);
    createDotPoints(290,150,350,150);
    createDotPoints(410,150,510,150);
    // Teleport Dots
    createDotPoints(0,270,170,270);
    createDotPoints(350,270,520,270);
    // Bottom
    createDotPoints(170,330,350,330);
    createDotPoints(10,390,230,390);
    createDotPoints(290,390,510,390);
    createDotPoints(10,450,50,450);
    createDotPoints(110,450,410,450);
    createDotPoints(470,450,510,450);
    createDotPoints(10,510,110,510);
    createDotPoints(170,510,230,510);
    createDotPoints(290,510,350,510);
    createDotPoints(410,510,510,510);
    createDotPoints(10,570,510,570);

    // Verticle Dots
    // Left
    createDotPoints(10,10,10,150);
    createDotPoints(10,390,10,450);
    createDotPoints(10,510,10,570);
    createDotPoints(50,450,50,510);
    createDotPoints(110,10,110,510);
    createDotPoints(170,90,170,150);
    createDotPoints(170,210,170,390);
    createDotPoints(170,450,170,510);
    createDotPoints(230,10,230,90);
    createDotPoints(230,150,230,210);
    createDotPoints(230,390,230,450);
    createDotPoints(230,510,230,570);

    // Right
    createDotPoints(290,10,290,90);
    createDotPoints(290,150,290,210);
    createDotPoints(290,390,290,450);
    createDotPoints(290,510,290,570);
    createDotPoints(350,90,350,150);
    createDotPoints(350,210,350,390);
    createDotPoints(350,450,350,510);
    createDotPoints(410,10,410,510);
    createDotPoints(470,450,470,510);
    createDotPoints(510,10,510,150);
    createDotPoints(510,390,510,450);
    createDotPoints(510,510,510,570);
















    // Horizontal paths
    // Top
    createPathPoints(10,10,230,10);
    createPathPoints(290,10,510,10);
    createPathPoints(10,90,510,90);
    createPathPoints(10,150,110,150);
    createPathPoints(170,150,230,150);
    createPathPoints(170,210,350,210);
    createPathPoints(290,150,350,150);
    createPathPoints(410,150,510,150);
    // Teleport paths
    createPathPoints(0,270,170,270);
    createPathPoints(350,270,520,270);
    // Bottom
    createPathPoints(170,330,350,330);
    createPathPoints(10,390,230,390);
    createPathPoints(290,390,510,390);
    createPathPoints(10,450,50,450);
    createPathPoints(110,450,410,450);
    createPathPoints(470,450,510,450);
    createPathPoints(10,510,110,510);
    createPathPoints(170,510,230,510);
    createPathPoints(290,510,350,510);
    createPathPoints(410,510,510,510);
    createPathPoints(10,570,510,570);

    // Verticle paths
    // Left
    createPathPoints(10,10,10,150);
    createPathPoints(10,390,10,450);
    createPathPoints(10,510,10,570);
    createPathPoints(50,450,50,510);
    createPathPoints(110,10,110,510);
    createPathPoints(170,90,170,150);
    createPathPoints(170,210,170,390);
    createPathPoints(170,450,170,510);
    createPathPoints(230,10,230,90);
    createPathPoints(230,150,230,210);
    createPathPoints(230,390,230,450);
    createPathPoints(230,510,230,570);

    // Right
    createPathPoints(290,10,290,90);
    createPathPoints(290,150,290,210);
    createPathPoints(290,390,290,450);
    createPathPoints(290,510,290,570);
    createPathPoints(350,90,350,150);
    createPathPoints(350,210,350,390);
    createPathPoints(350,450,350,510);
    createPathPoints(410,10,410,510);
    createPathPoints(470,450,470,510);
    createPathPoints(510,10,510,150);
    createPathPoints(510,390,510,450);
    createPathPoints(510,510,510,570);
}
void GameMap::createDotPoints(int startx, int starty, int endx, int endy)
{
    QPoint point;
    const int DIVISOR = 20;
    int numOfDots = 0;
    int x = startx;
    int y = starty;

    // If the line is horizontal
    if (starty == endy)
    {
        // If line is given from left to right
        if (startx < endx)
        {
            numOfDots = ((endx - startx) / DIVISOR) + 1;

            for (int i = 0; i < numOfDots ; i++)
            {
                point.setX(x);
                point.setY(starty);
                if (!dotLocations.contains(point))
                {
                    dotLocations.append(point);
                }

                x += DIVISOR;
            }
        }
        else
        {
             numOfDots = ((startx - endx) / DIVISOR) + 1;
            for (int i = 0; i < numOfDots; i++)
            {
                point.setX(x);
                point.setY(starty);
                if (!dotLocations.contains(point))
                {
                    dotLocations.append(point);
                }
                x -= DIVISOR;
            }
        }
    }
    else
    {
        // If line is given bottom to top
        if (starty < endy)
        {
            numOfDots = ((endy - starty) / DIVISOR) + 1;
            for (int i = 0; i < numOfDots; i++)
            {
                point.setY(y);
                point.setX(startx);
                if (!dotLocations.contains(point))
                {
                    dotLocations.append(point);
                }
                y += DIVISOR;
            }
        }
        else
        {
            numOfDots = ((starty - endy) / DIVISOR) + 1;
            for (int i = 0; i < numOfDots; i++)
            {
                point.setY(y);
                point.setX(startx);
                if (!dotLocations.contains(point))
                {
                    dotLocations.append(point);
                }
                y -= DIVISOR;
            }
        }
    }
}

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
