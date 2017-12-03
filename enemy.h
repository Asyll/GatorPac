#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include "player.h"
#include "gamemap.h"
#include "direction.h"

enum Movement {CHASE, SCATTER, FRIGHTENED};
enum GhostType {RED, PINK, BLUE, ORANGE};

class Enemy : public QGraphicsItem
{
public:
    Enemy(int posx, int posy, int speed, QString name, GameMap *gameMap, Player* gator, GhostType type);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void move();
    void resetOrientation();
    void setDefaultPosition();

    int getSpeed() const;
    void setSpeed(int speed);

    int getPosx() const;
    void setPosx(int x);

    int getPosy() const;
    void setPosy(int y);

    bool isMoving() const;
    void setMoving(bool value);

    void setMode(const Movement mode);
    Movement getMode() const;

    bool isReleased() const;
    void setReleased(bool value);

    bool isInitiated() const;
    void setInitiated(bool value);


private:
    QPixmap forward, reverse, up, down;
//    QPixmap forwardScared, reverseScared, upScared, downScared;
    QPixmap frightMeat;
    Direction direction, nextDirection, facingDirection;

    GhostType type;
    Movement mode;
    GameMap *gameMap;
    Player *gator;

    bool moving;
    bool released;
    bool initiated;
    int speed;

    // String used to find the pertaining image
    QString name;

    // Position in pixels
    int posx, posy;
    const int defaultPosx, defaultPosy;

    // Image dimension in pixels
    const int charW, charH;

    // Scatter position in pixels
    int scatx, scaty;

    // Different enemy movement styles
    void chase();
    void scatter();
    void frightened();

    void setScatterPoint();

};

#endif // ENEMY_H
