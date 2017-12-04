#include "gamemap.h"

GameMap::GameMap()
{
    // Load map layout background
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

    /* Draws debug dot points
    for (QPoint point : dotLocations)
    {
        painter->drawPoint(point);
    }
    */

    /* Draws debug paths
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

const QVector<QPoint>* GameMap::getDotVector()
{
    // Will only create the dots once called
    makeMapDots();
    return &dotLocations;
}

void GameMap::makeMapPaths()
{
    // Horizontal paths
    // Top side
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
    // Bottom side
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
    // Left side
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

    // Right side
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

void GameMap::makeMapDots()
{
    // Horizontal dots
    // Top side
    generateDot(10,10,230,10);
    generateDot(290,10,510,10);
    generateDot(10,90,510,90);
    generateDot(10,150,110,150);
    generateDot(170,150,230,150);
    generateDot(290,150,350,150);
    generateDot(410,150,510,150);
    // Bottom side
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
    // Left side
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

    // Right side
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

/* Start and End position must be given in pixels with
 * 0, 0 being the top left of the window.
 * Cannot give diagnonal segments. */
void GameMap::generateDot(int startx, int starty, int endx, int endy)
{
    QPoint point;
    const int DIVISOR = 20;
    int numOfDots = 0;
    int x = startx;
    int y = starty;

    if (starty == endy)                                                 // If the line is horizontal
    {
        if (startx < endx)                                              // If line is given from left to right
        {
            numOfDots = ((endx - startx) / DIVISOR) + 1;                // Calculate how many dots will be in this section

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
        else                                                            // If line is given from right to left
        {
            numOfDots = ((startx - endx) / DIVISOR) + 1;                // Calculate how many dots will be in this section

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
    else                                                                // If the line is vertical
    {
        // If line is given bottom to top
        if (starty < endy)                                              // If line is given bottom to top
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
        else                                                            // If line is given top to bottom
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

/* Start and End position must be given in pixels with
 * 0, 0 being the top left of the window.
 * Cannot give diagnonal segments. */
void GameMap::generatePath(int startx, int starty, int endx, int endy)
{
    QPoint point;

    if (starty == endy)                                                 // If the line is horizontal
    {
        if (startx < endx)                                              // If line is given from left to right
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
        else                                                            // If the line is given from right to left
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
    else                                                                // If the line is vertical
    {
        if (starty < endy)                                              // If line is given bottom to top
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
        else                                                            // If the line is given top to bottom
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
