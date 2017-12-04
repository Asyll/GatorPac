/* This class represents the enemies (or ghosts) of the game and
 * includes their movement mechanics. */

#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include <QTimer>
#include "player.h"
#include "gamemap.h"

enum Movement {CHASE, SCATTER, FRIGHTENED};
enum EnemyType {RED, PINK, BLUE, ORANGE};

class Enemy : public Entity
{
public:
    Enemy(int posx, int posy, int speed, QString name, GameMap *gameMap, Player* gator, EnemyType type);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void move();                                        // Starts the correct movement mode

    void setSpeed(int speed);                           // Changes the Enemy speed (valid values = 2 , 5)

    void setMode(const Movement mode);                  // Changes to one of the three designated movements
    Movement getMode() const;                           // Gives the current movement mode

    bool isReleased() const;                            // Returs whether the Enemy has left the box
    void setReleased(bool value);                       // Used for indicating if the enemy is in the box

    bool isInitiated() const;                           // Returns whether the Enemy has finished the movement wave
    void setInitiated(bool value);                      // Used for indicating if the enemy has finished the movement wave

    void resetOrientation();                            // Sets the default directions
    void setDefaultPosition();                          // Returns entity to initial position

private:
    QPixmap forward, reverse, up, down, frightMeat;     // Images for each direction
    EnemyType type;
    Movement mode;
    GameMap *gameMap;                                   // Access to the Game Map
    Player *gator;                                      // Access to a Player instance
    QString name;                                       // String used to find the pertaining image of Enemy

    bool released;
    bool initiated;

    int scatx, scaty;                                   // Position where Enemy moves towards when in SCATTER mode

    // Different enemy movement modes
    void chase();                                       // Enemy will chase the Player
    void scatter();                                     // Enemy will go to its indicated scatter position
    void frightened();                                  // Enemy will be able to be eaten and moves pseudorandomly

    void setScatterPoint();                             // Sets the scatter points depending on the GhostType of Enemy
};

#endif // ENEMY_H
