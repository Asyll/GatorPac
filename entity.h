/* A base class for Enemy and Player that holds position, speed and
 * helps reset them. */

#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsItem>
#include <QPainter>

enum Direction {UP, RIGHT, DOWN, LEFT, NONE};

class Entity : public QGraphicsItem
{
public:
    Entity(int posx, int posy, int speed);
    QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) = 0;

    int getPosx() const;
    void setPosx(int x);

    int getPosy() const;
    void setPosy(int y);

    bool isMoving() const;
    void setMoving(bool value);

    virtual void resetOrientation();                    // Sets the default directions
    virtual void setDefaultPosition();                  // Returns entity to initial position

    int getSpeed() const;

protected:
    Direction direction, nextDirection, facingDirection;

    int posx, posy;                                     // Position (in pixels)
    const int defaultPosx, defaultPosy;                 // Used to reset entity's position
    int speed;                                          // # of pixels entity moves per frame
    bool moving;                                        // Determines whether the entity is moving

    int charW = 40;                                     // Dimension of entity (in pixels)
    int charH = 40;                                     // Dimension of entity (in pixels)

};

#endif // ENTITY_H
