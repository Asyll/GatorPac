/* This class represents all dots (small and large) on the map
 * that can be eaten. */

#ifndef DOTS_H
#define DOTS_H

#include <QGraphicsItem>
#include <QPainter>
#include <QVector>

class Dots : public QGraphicsItem
{
public:
    Dots(const QVector<QPoint>* points);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setPoints(const QVector<QPoint>* points);      // Takes a vector of QPoints to make the dots

    QVector<QPoint> points;

private:
    int dotW = 40;                                      // Dimension of Dots (in pixels)
    int dotH = 40;                                      // Dimension of Dots (in pixels)
    const int maxDots;                                  // Maximum # of dots on the map
    QPixmap dotImg, largeDotImg;                        // Images for regular dots and power dots

};

#endif // DOTS_H
