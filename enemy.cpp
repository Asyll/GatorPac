#include "enemy.h"
#include <iostream>

//class that implements the enemies

Enemy::Enemy(int posx, int posy, int speed, QString name, GameMap *gameMap, Player* gator, GhostType type) :
    charW(40),
    charH(40),
    defaultPosx(posx),
    defaultPosy(posy)
{
    this->posx = posx;
    this->posy = posy;
    this->name = name;
    this->speed = speed;
    this->gameMap = gameMap;
    this->gator = gator;
    this->type = type;

    setScatterPoint(); //calls ScatterPoint method

    resetOrientation(); //calls resetOrientation method

    mode = Movement::SCATTER;
    released = false;
    initiated = false;

    //loads images for each possible orientation in normal and frightened mode
    forward.load("://Images/Characters/" + name + "_forward.png");
    reverse.load("://Images/Characters/" + name + "_reverse.png");
    up.load("://Images/Characters/" + name + "_forward_up.png");
    down.load("://Images/Characters/" + name + "_forward_down.png");
    forwardScared.load("://Images/Characters/" + name + "_forward_scared.png");
    reverseScared.load("://Images/Characters/" + name + "_reverse_scared.png");
    upScared.load("://Images/Characters/" + name + "_forward_scared_up.png");
    downScared.load("://Images/Characters/" + name + "_forward_scared_down.png");
}

//defines bounding rectangle for enemy
QRectF Enemy::boundingRect() const
{
    return QRect(0,0,charW,charH);
}

//paints enemy's orientation for both normal and frightened mode
void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //paints enemy's oreintation when they are in frightened mode
    if (mode == Movement::FRIGHTENED)
    {
        switch(facingDirection)
        {
        case LEFT:
            painter->drawPixmap(posx,posy,charW,charW,reverseScared); // left orientation
            break;
        case RIGHT:
            painter->drawPixmap(posx,posy,charW,charW,forwardScared); //right orientation
            break;
        case UP:
            painter->drawPixmap(posx,posy,charW,charW,upScared); //up orientation
            break;
        case DOWN:
            painter->drawPixmap(posx,posy,charW,charW,downScared); //down orientation
            break;
        case NONE:
            painter->drawPixmap(posx,posy,charW,charW,forwardScared); //default orientation
            break;
        }
    }
    else
    {
        //paints enemy's orientation while in normal mode
        switch(facingDirection)
        {
        case LEFT:
            painter->drawPixmap(posx,posy,charW,charW,reverse); //left orientation
            break;
        case RIGHT:
            painter->drawPixmap(posx,posy,charW,charW,forward); //right orientation
            break;
        case UP:
            painter->drawPixmap(posx,posy,charW,charW,up); //up orientation
            break;
        case DOWN:
            painter->drawPixmap(posx,posy,charW,charW,down); //down orientation
            break;
        case NONE:
            painter->drawPixmap(posx,posy,charW,charW,forward); //default orientation
            break;
        }
    }
}

//gets enemy's speed
int Enemy::getSpeed() const
{
    return speed;
}

//sets enemy's speed
void Enemy::setSpeed(int speed)
{
    //prints to console the position and speed of enemy
    while ((posx % speed) != 0 || ((posy % speed) != 0))
    {
        move();
    }
    this->speed = speed;
}

//gets enemy's x-position
int Enemy::getPosx() const
{
    return posx;
}

//sets enemy's x-position
void Enemy::setPosx(int x)
{
    if (x >= 0 && x <= 520)
    {
        posx = x;
    }
}

//gets enemy's y-position
int Enemy::getPosy() const
{
    return posy;
}

//sets enemy's y-position
void Enemy::setPosy(int y)
{
    if (y >= 10 && y <= 570)
    {
        posy = y;
    }
}

//checks whether enemy is moving
bool Enemy::isMoving() const
{
    return moving;
}

//sets enemy's moving values
void Enemy::setMoving(bool value)
{
    moving = value;
}

//sets the enemy's speed for each movement mode (frightened or normal)
void Enemy::setMode(const Movement mode)
{
    if (mode == Movement::FRIGHTENED) //enemies move slower in frightened mode at speed 2
    {
        setSpeed(2);
    }
    else
    {
        setSpeed(5); //while not in frightened mode, enemies move at speed 5
    }
    this->mode = mode;
}

//checks if enemy is released from their box
bool Enemy::isReleased() const
{
    return released;
}

//sets whether enemy is released fromt heir box
void Enemy::setReleased(bool value)
{
    released = value;
}

//checks if enemy is intiated
bool Enemy::isInitiated() const
{
    return initiated;
}

//sets whether enemy is initiated
void Enemy::setInitiated(bool value)
{
    initiated = value;
}

//checks the enemy's movement mode
Movement Enemy::getMode() const
{
    return mode;
}

// Sets scatter point based on what ghost type the object is
void Enemy::setScatterPoint()
{
    switch(type)
    {
    case RED:
        scatx = 490;
        scaty = 0;
        break;
    case PINK:
        scatx = 30;
        scaty = 0;
        break;
    case BLUE:
        scatx = 520;
        scaty = 550;
        break;
    case ORANGE:
        scatx = 0;
        scaty = 550;
        break;
    }
}

//resets the enemy's orientation
void Enemy::resetOrientation()
{
    facingDirection = Direction::RIGHT;
    direction = Direction::RIGHT;
    nextDirection = Direction::NONE;

    mode = Movement::CHASE;
}

//sets the default position for the enemy
void Enemy::setDefaultPosition()
{
    released = false;
    setPosx(defaultPosx);
    setPosy(defaultPosy);
}

//changes enemy's movement based on what mode they are in
void Enemy::move()
{
    switch(mode)
    {
    case CHASE:
        chase();
        break;
    case SCATTER:
        scatter();
        break;
    case FRIGHTENED:
        frightened();
        break;
    }
}

//sets the movement patterns for the enemies while they are in chase mode
//enemies will try to chase gatorpac
void Enemy::chase()
{
    QPoint point;

    //compares the enemy's position with gatorpac's position
    //and determines the direction the enemy should move
    if (moving)
    {
        if (direction == Direction::RIGHT || direction == Direction::LEFT)
        {
            if (this->posy < gator->getPosy())
            {
                nextDirection = Direction::DOWN;
            }
            else if (this->posy > gator->getPosy())
            {
                nextDirection = Direction::UP;
            }
        }
        else if (direction == Direction::DOWN || direction == Direction::UP)
        {
            if (this->posx < gator->getPosx())
            {
                nextDirection = Direction::RIGHT;
            }
            else if (this->posx > gator->getPosx())
            {
                nextDirection = Direction::LEFT;
            }
        }
    }

    //compares the enemy's position with gatorpac's position
    //and determines the direction the enemy should move
    else
    {
        if (direction == Direction::RIGHT || direction == Direction::LEFT)
        {
            if (this->posy < gator->getPosy())
            {
                point.setX(posx);
                point.setY(posy + speed);
                if (gameMap->canMove(point))
                {
                    nextDirection = Direction::DOWN;
                }
                else
                {
                    nextDirection = Direction::UP;
                }
            }
            else if (this->posy > gator->getPosy())
            {
                point.setX(posx);
                point.setY(posy - speed);
                if (gameMap->canMove(point))
                {
                    nextDirection = Direction::UP;
                }
                else
                {
                    nextDirection = Direction::DOWN;
                }
            }
            else
            {
                point.setX(posx);
                point.setY(posy + speed);
                if (gameMap->canMove(point))
                {
                    nextDirection = Direction::DOWN;
                }
                else
                {
                    nextDirection = Direction::UP;
                }
            }
        }

        //compares the enemy's position with gatorpac's position
        //and determines the direction the enemy should move
        else if (direction == Direction::DOWN || direction == Direction::UP)
        {
            if (this->posx < gator->getPosx())
            {
                point.setX(posx + speed);
                point.setY(posy);
                if (gameMap->canMove(point))
                {
                    nextDirection = Direction::RIGHT;
                }
                else
                {
                    nextDirection = Direction::LEFT;
                }
            }
            else if (this->posx > gator->getPosx())
            {
                point.setX(posx - speed);
                point.setY(posy);
                if (gameMap->canMove(point))
                {
                    nextDirection = Direction::LEFT;
                }
                else
                {
                    nextDirection = Direction::RIGHT;
                }
            }
            else
            {
                point.setX(posx + speed);
                point.setY(posy);
                if (gameMap->canMove(point))
                {
                    nextDirection = Direction::RIGHT;
                }
                else
                {
                    nextDirection = Direction::LEFT;
                }
            }
        }
    }


    //if next direction does not equal current direction change the current
    //direction accordingly and check if that is valid.
    if (nextDirection != direction)
    {
        switch (nextDirection)
        {
        case LEFT:
            point.setX(posx - speed);
            point.setY(posy);
            if (gameMap->canMove(point))
            {
                direction = nextDirection;
                nextDirection = Direction::NONE;
            }
            break;
        case RIGHT:
            point.setX(posx + speed);
            point.setY(posy);
            if (gameMap->canMove(point))
            {
                direction = nextDirection;
                nextDirection = Direction::NONE;
            }
            break;
        case UP:
            point.setX(posx);
            point.setY(posy - speed);
            if (gameMap->canMove(point))
            {
                direction = nextDirection;
                nextDirection = Direction::NONE;
            }
            break;
        case DOWN:
            point.setX(posx);
            point.setY(posy + speed);
            if (gameMap->canMove(point))
            {
                direction = nextDirection;
                nextDirection = Direction::NONE;
            }
            break;
        }
    }

    //changes enemy direction based on edge of gamemap
    switch (direction)
    {
    case LEFT:
        point.setX(posx - speed);
        point.setY(posy);
        facingDirection = direction;

        if (posx < 90 && posy == 270)
        {
            posx -= 2;
            moving = true;
            if (posx <= 0)
            {
                posx = 520;
            }
        }
        else if (posx > 430 && posy == 270)
        {
            posx -= 2;
            moving = true;
        }
        else if (gameMap->canMove(point))
        {
            posx -= speed;
            moving = true;
        }
        else
        {
            moving = false;
        }
        break;
    case RIGHT:

        point.setX(posx + speed);
        point.setY(posy);
        facingDirection = direction;

        if (posx > 430 && posy == 270) {
            posx += 2;
            moving = true;
            if (posx >= 520)
            {
                posx = 0;
            }
        }
        else if (posx < 90 && posy == 270) {
            posx += 2;
            moving = true;
        }
        else if (gameMap->canMove(point))
        {
            posx += speed;
            moving = true;
        }
        else
        {
            moving = false;
        }
        break;
    case UP:
        point.setX(posx);
        point.setY(posy - speed);
        facingDirection = direction;

        if (gameMap->canMove(point))
        {
            posy -= speed;
            moving = true;
        }
        else
        {
            moving = false;
        }
        break;
    case DOWN:
        point.setX(posx);
        point.setY(posy + speed);
        facingDirection = direction;

        if (gameMap->canMove(point))
        {
            posy += speed;
            moving = true;
        }
        else
        {
            moving = false;
        }
        break;
    case NONE:
        break;
    }

}

//sets the movement patterns for the enemies while they are in scatter mode
//each enemy moves around a certain position
void Enemy::scatter()
{
    QPoint point;

    if (moving)
    {
        //compares enemy's current position with scatter positions and changes
        //direction accordingly
        if (direction == Direction::RIGHT || direction == Direction::LEFT)
        {
            if (this->posy < scaty)
            {
                nextDirection = Direction::DOWN;
            }
            else if (this->posy > scaty)
            {
                nextDirection = Direction::UP;
            }
        }
        else if (direction == Direction::DOWN || direction == Direction::UP)
        {
            if (this->posx < scatx)
            {
                nextDirection = Direction::RIGHT;
            }
            else if (this->posx > scatx)
            {
                nextDirection = Direction::LEFT;
            }
        }
    }
    else
    {
        //scatter for horizontal orientation
        if (direction == Direction::RIGHT || direction == Direction::LEFT)
        {
            if (this->posy < scaty)
            {
                point.setX(posx);
                point.setY(posy + speed);
                if (gameMap->canMove(point))
                {
                    nextDirection = Direction::DOWN;
                }
                else
                {
                    nextDirection = Direction::UP;
                }
            }
            else if (this->posy > scaty)
            {
                point.setX(posx);
                point.setY(posy - speed);
                if (gameMap->canMove(point))
                {
                    nextDirection = Direction::UP;
                }
                else
                {
                    nextDirection = Direction::DOWN;
                }
            }
            else
            {
                point.setX(posx);
                point.setY(posy + speed);
                if (gameMap->canMove(point))
                {
                    nextDirection = Direction::DOWN;
                }
                else
                {
                    nextDirection = Direction::UP;
                }
            }
        }

        //scatter for vertical orienation
        else if (direction == Direction::DOWN || direction == Direction::UP)
        {
            if (this->posx < scatx)
            {
                point.setX(posx + speed);
                point.setY(posy);
                if (gameMap->canMove(point))
                {
                    nextDirection = Direction::RIGHT;
                }
                else
                {
                    nextDirection = Direction::LEFT;
                }
            }
            else if (this->posx > scatx)
            {
                point.setX(posx - speed);
                point.setY(posy);
                if (gameMap->canMove(point))
                {
                    nextDirection = Direction::LEFT;
                }
                else
                {
                    nextDirection = Direction::RIGHT;
                }
            }
            else
            {
                point.setX(posx + speed);
                point.setY(posy);
                if (gameMap->canMove(point))
                {
                    nextDirection = Direction::RIGHT;
                }
                else
                {
                    nextDirection = Direction::DOWN;
                }
            }
        }
    }


    //if next direction does not equal current direction change the current
    //direction accordingly and check if that is valid.
    if (nextDirection != direction)
    {
        switch (nextDirection)
        {
        case LEFT:
            point.setX(posx - speed);
            point.setY(posy);
            if (gameMap->canMove(point))
            {
                direction = nextDirection;
                nextDirection = Direction::NONE;
            }
            break;
        case RIGHT:
            point.setX(posx + speed);
            point.setY(posy);
            if (gameMap->canMove(point))
            {
                direction = nextDirection;
                nextDirection = Direction::NONE;
            }
            break;
        case UP:
            point.setX(posx);
            point.setY(posy - speed);
            if (gameMap->canMove(point))
            {
                direction = nextDirection;
                nextDirection = Direction::NONE;
            }
            break;
        case DOWN:
            point.setX(posx);
            point.setY(posy + speed);
            if (gameMap->canMove(point))
            {
                direction = nextDirection;
                nextDirection = Direction::NONE;
            }
            break;
        }
    }

    //changes direction of enemy based on current direction
    switch (direction)
    {

    case LEFT:
        point.setX(posx - speed);
        point.setY(posy);
        facingDirection = direction;
        if (posx < 90 && posy == 270) {
            posx -= 2;
            moving = true;
            if (posx <= 0)
            {
                posx = 520;
            }
        }
        else if (posx > 430 && posy == 270) {
            posx -= 2;
            moving = true;
        }

        else if (gameMap->canMove(point))
        {
            posx -= speed;
            moving = true;
        }
        else
        {
            moving = false;
        }
        break;
    case RIGHT:
        point.setX(posx + speed);
        point.setY(posy);
        facingDirection = direction;

        if (posx > 430 && posy == 270) {
            posx += 2;
            moving = true;
            if (posx >= 520)
            {
                posx = 0;
            }
        }
        else if (posx < 90 && posy == 270) {
            posx += 2;
            moving = true;
        }
        else if (gameMap->canMove(point))
        {
            posx += speed;
            moving = true;
        }
        else
        {
            moving = false;
        }
        break;
    case UP:
        point.setX(posx);
        point.setY(posy - speed);
        facingDirection = direction;

        if (gameMap->canMove(point))
        {
            posy -= speed;
            moving = true;
        }
        else
        {
            moving = false;
        }
        break;
    case DOWN:
        point.setX(posx);
        point.setY(posy + speed);
        facingDirection = direction;

        if (gameMap->canMove(point))
        {
            posy += speed;
            moving = true;
        }
        else
        {
            moving = false;
        }
        break;
    case NONE:
        break;
    }
}

//sets the movement patterns for the enemies while they are in frightened mode
//enemy movement will be random
void Enemy::frightened()
{
    QPoint point;

    int ranDir = 0;
    if (!moving)
    {
        ranDir = qrand() % 3;
        switch(ranDir)
        {
        case 0: // RIGHT
            point.setX(posx + speed);
            point.setY(posy);
            nextDirection = Direction::RIGHT;
            break;
        case 1: // DOWN
            point.setX(posx);
            point.setY(posy + speed);
            nextDirection = Direction::DOWN;
            break;
        case 2: // LEFT
            point.setX(posx - speed);
            point.setY(posy);
            nextDirection = Direction::LEFT;
            break;
        case 3: // UP
            point.setX(posx);
            point.setY(posy - speed);
            nextDirection = Direction::UP;
            break;
        }
    }


    //if next direction does not equal current direction change the current
    //direction accordingly and check if that is valid.
    if (nextDirection != direction)
    {
        switch (nextDirection)
        {
        case LEFT:
            point.setX(posx - speed);
            point.setY(posy);
            if (gameMap->canMove(point))
            {
                direction = nextDirection;
                nextDirection = Direction::NONE;
            }
            break;
        case RIGHT:
            point.setX(posx + speed);
            point.setY(posy);
            if (gameMap->canMove(point))
            {
                direction = nextDirection;
                nextDirection = Direction::NONE;
            }
            break;
        case UP:
            point.setX(posx);
            point.setY(posy - speed);
            if (gameMap->canMove(point))
            {
                direction = nextDirection;
                nextDirection = Direction::NONE;
            }
            break;
        case DOWN:
            point.setX(posx);
            point.setY(posy + speed);
            if (gameMap->canMove(point))
            {
                direction = nextDirection;
                nextDirection = Direction::NONE;
            }
            break;
        }
    }

    //changes enemy orientation based on current direction
    switch (direction)
    {
    case LEFT:
        point.setX(posx - speed);
        point.setY(posy);
        facingDirection = direction;
        if (posx < 90 && posy == 270) {
            posx -= 2;
            moving = true;
            if (posx <= 0)
            {
                posx = 520;
            }
        }
        else if (posx > 430 && posy == 270) {
            posx -= 2;
            moving = true;
        }

        else if (gameMap->canMove(point))
        {
            posx -= speed;
            moving = true;
        }
        else
        {
            moving = false;
        }
        break;
    case RIGHT:
        point.setX(posx + speed);
        point.setY(posy);
        facingDirection = direction;

        if (posx > 430 && posy == 270) {
            posx += 2;
            moving = true;
            if (posx >= 520)
            {
                posx = 0;
            }
        }
        else if (posx < 90 && posy == 270) {
            posx += 2;
            moving = true;
        }
        else if (gameMap->canMove(point))
        {
            posx += speed;
            moving = true;
        }
        else
        {
            moving = false;
        }
        break;
    case UP:
        point.setX(posx);
        point.setY(posy - speed);
        facingDirection = direction;

        if (gameMap->canMove(point))
        {
            posy -= speed;
            moving = true;
        }
        else
        {
            moving = false;
        }
        break;
    case DOWN:
        point.setX(posx);
        point.setY(posy + speed);
        facingDirection = direction;

        if (gameMap->canMove(point))
        {
            posy += speed;
            moving = true;
        }
        else
        {
            moving = false;
        }
        break;
    case NONE:
        break;
    }
}
