#ifndef DOTS_H
#define DOTS_H#
#include "player.h"

class dots: public QGraphicsItem
{
public:
    dots(int posx, int posy);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int posx;
    int posy;
    QPixmap dot;


    int getPosx() const;
    void setPosx(int x);

    int getPosy() const;
    void setPosy(int y);

};

#endif // DOTS_H
