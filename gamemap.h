#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QVector>

class GameMap : public QGraphicsItem
{
public:
    GameMap();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPixmap mapImage;

};

#endif // GAMEMAP_H
