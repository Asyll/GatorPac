#ifndef DOTS_H
#define DOTS_H

#include <QPainter>
#include <QGraphicsItem>
#include <QVector>

class Dots : public QGraphicsItem
{
public:
    Dots(const QVector<QPoint>* points);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void setPoints(const QVector<QPoint>* points);

private:
    const int dotW, dotH;
    QPixmap dotImg;
    QVector<QPoint> points;

};

#endif // DOTS_H
