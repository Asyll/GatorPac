#include "gamemap.h"
#include <iostream>

//class that sets up the game map

//sets up the game map
GameMap::GameMap()
{
    mapImage.load(":/Images/swampmap.png"); //loads the game map from it's image

    makeMapPaths(); //sets up the paths for the game map.
}

//creates bounding rectangle for game map
QRectF GameMap::boundingRect() const
{
    return QRect(0,0,560,620);
}

//?
void GameMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,560,620,mapImage);

    /* Draw debug dot points
    for (QPoint point : dotLocations)
    {
        painter->drawPoint(point);
    }
    */

    /* Draw debug paths
    for (QPoint point : moveablePath)
    {
        painter->drawPoint(point);
    }
    */
}

//sets up the movement path for the game map
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

//sets up the dot positions for the game map
const QVector<QPoint>* GameMap::getDotVector()
{
    makeMapDots();
    return &dotLocations;
}

// Creates all the moveable paths on the game map
void GameMap::makeMapPaths()
{
    // Horizontal paths
    // Top
    generatePath(10,10,230,10);
    generatePath(290,10,510,10);
    generatePath(10,90,510,90);
    generatePath(10,150,110,150);
    generatePath(170,150,230,150);
    generatePath(170,210,350,210);
    generatePath(290,150,350,150);
    generatePath(410,150,510,150);
    // Teleport paths
    generatePath(0,270,170,270);
    generatePath(350,270,520,270);
    // Bottom
    generatePath(170,330,350,330);
    generatePath(10,390,230,390);
    generatePath(290,390,510,390);
    generatePath(10,450,50,450);
    generatePath(110,450,410,450);
    generatePath(470,450,510,450);
    generatePath(10,510,110,510);
    generatePath(170,510,230,510);
    generatePath(290,510,350,510);
    generatePath(410,510,510,510);
    generatePath(10,570,510,570);

    // Verticle paths
    // Left
    generatePath(10,10,10,150);
    generatePath(10,390,10,450);
    generatePath(10,510,10,570);
    generatePath(50,450,50,510);
    generatePath(110,10,110,510);
    generatePath(170,90,170,150);
    generatePath(170,210,170,390);
    generatePath(170,450,170,510);
    generatePath(230,10,230,90);
    generatePath(230,150,230,210);
    generatePath(230,390,230,450);
    generatePath(230,510,230,570);

    // Right
    generatePath(290,10,290,90);
    generatePath(290,150,290,210);
    generatePath(290,390,290,450);
    generatePath(290,510,290,570);
    generatePath(350,90,350,150);
    generatePath(350,210,350,390);
    generatePath(350,450,350,510);
    generatePath(410,10,410,510);
    generatePath(470,450,470,510);
    generatePath(510,10,510,150);
    generatePath(510,390,510,450);
    generatePath(510,510,510,570);
}

//sets where the dots are on the map
void GameMap::makeMapDots()
{
    // Horizontal dots
    // Top
    generateDot(10,10,230,10);
    generateDot(290,10,510,10);
    generateDot(10,90,510,90);
    generateDot(10,150,110,150);
    generateDot(170,150,230,150);
    generateDot(290,150,350,150);
    generateDot(410,150,510,150);
    // Bottom
    generateDot(10,390,230,390);
    generateDot(290,390,510,390);
    generateDot(10,450,50,450);
    generateDot(110,450,230,450);
    generateDot(290,450,410,450);
    generateDot(470,450,510,450);
    generateDot(10,510,110,510);
    generateDot(170,510,230,510);
    generateDot(290,510,350,510);
    generateDot(410,510,510,510);
    generateDot(10,570,510,570);

    // Verticle Dots
    // Left
    generateDot(10,10,10,150);
    generateDot(10,390,10,450);
    generateDot(10,510,10,570);
    generateDot(50,450,50,510);
    generateDot(110,10,110,510);
    generateDot(170,90,170,150);
    generateDot(170,450,170,510);
    generateDot(230,10,230,90);
    generateDot(230,390,230,450);
    generateDot(230,510,230,570);

    // Right
    generateDot(290,10,290,90);
    generateDot(290,390,290,450);
    generateDot(290,510,290,570);
    generateDot(350,90,350,150);
    generateDot(350,450,350,510);
    generateDot(410,10,410,510);
    generateDot(470,450,470,510);
    generateDot(510,10,510,150);
    generateDot(510,390,510,450);
    generateDot(510,510,510,570);
}

//generates dots for the game map
void GameMap::generateDot(int startx, int starty, int endx, int endy)
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
void GameMap::generatePath(int startx, int starty, int endx, int endy)
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
