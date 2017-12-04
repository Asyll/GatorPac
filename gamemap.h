/* This class creates and holds the moveable paths for the game
 * as well as generates the locations of the dots. */

#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QVector>
#include "dots.h"

class GameMap : public QGraphicsItem
{
public:
    GameMap();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool canMove(QPoint);                               // Helps check if an Entity can move within the moveable path

    const QVector<QPoint>* getDotVector();              // Returns a QVector of QPoints used to set up the dots of the map by Dots class


private:

    QPixmap mapImage;
    QVector<QPoint> moveablePath;
    QVector<QPoint> dotLocations;

    void generatePath(int,int,int,int);
    void generateDot(int, int, int, int);
    void makeMapPaths();
    void makeMapDots();

};

#endif // GAMEMAP_H
