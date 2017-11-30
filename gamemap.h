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

    const QVector<QPoint>* getDotVector();


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
