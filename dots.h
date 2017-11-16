#ifndef DOTS_H
#define DOTS_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>


class dots: public QGraphicsItem
{
public:
    dots();

private:
    int posx;
    int posy;

};

#endif // DOTS_H
