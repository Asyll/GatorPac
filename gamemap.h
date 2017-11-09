#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QVector>

class GameMap : public QGraphicsItem
{
private:
    QPixmap mapImage;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
    GameMap();
    QRectF boundingRect() const;
};

#endif // GAMEMAP_H
