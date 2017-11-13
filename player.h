#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QPainter>

// Indicates player direction
enum Direction {UP, RIGHT, DOWN, LEFT, NONE};

class Player : public QGraphicsItem
{
public:
    Player(int,int,int);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool moving;
    Direction currentDirection, nextDirection;

    // Position in pixels
    int posx, posy;

    int getSpeed() const;

private:
    QPixmap forward;
    int speed;

    // Image dimension in pixels
    const int charW, charH;
};

#endif // PLAYER_H
