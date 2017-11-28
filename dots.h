#ifndef DOTS_H
#define DOTS_H#
#include "player.h"

class Dots: public QGraphicsItem
{
public:
    Dots(int posx, int posy);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    int posx;
    int posy;
    QPixmap dot;



    int getPosx() const;
    void setPosx(int x);

    int getPosy() const;
    void setPosy(int y);
    int dotW, dotH;

};

#endif // DOTS_H
