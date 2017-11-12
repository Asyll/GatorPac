#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QPainter>

class Enemy : public QGraphicsItem
{
public:
    Enemy(int, int, QString);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPixmap forward;

    // Position in pixels
    int posx, posy;
    // Image dimension in pixels
    const int charW, charH;
    // String used to find the pertaining image
    QString name;
};

#endif // ENEMY_H
