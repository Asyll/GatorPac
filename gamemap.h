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
    bool canMove(QPoint);


private:
    QPixmap mapImage;
    void createPathPoints(int,int,int,int);
    void createDotPoints(int, int, int, int);
    QVector<QPoint> moveablePath;
    QVector<QPoint> dotLocations;
    void makeMapPaths();


};

#endif // GAMEMAP_H
