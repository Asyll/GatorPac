#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QPainter>
#include "player.h"
#include "gamemap.h"
#include "direction.h"

class Enemy : public QGraphicsItem
{
public:
    Enemy(int posx, int posy, int speed, QString name);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // Different enemy movement styles
    void chase(Player *gator, GameMap *gameMap);

    int getSpeed() const;

    int getPosx() const;
    void setPosx(int x);

    int getPosy() const;
    void setPosy(int y);

    bool isMoving() const;
    void setMoving(bool value);

private:
    QPixmap forward, reverse, up, down;

    // String used to find the pertaining image
    QString name;

    int speed;
    Direction direction, nextDirection, facingDirection;
    bool moving;

    // Position in pixels
    int posx, posy;

    // Image dimension in pixels
    const int charW, charH;

};

#endif // ENEMY_H
