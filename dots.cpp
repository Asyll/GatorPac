#include "dots.h"
#include <QGraphicsItem>
#include <QPainter>



dots::dots(int posx, int posy)
{
    this->posx = posx;
    this->posy =posy;
    dot.load("://Images/timdots.png");
}
void dots::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(posx, posy, 20, 20, dot);
}

int dots::setposx(){

}
int dots::setposy(){

}
bool dots::visible(){
    //for setting dot invisible when collided with gator
}
