#include "enemy.h"
#include <iostream>

Enemy::Enemy(int posx, int posy, int speed, QString name, GameMap *gameMap, Player* gator, EnemyType type) :
    Entity::Entity(posx, posy, speed)
{
    this->name = name;
    this->gameMap = gameMap;
    this->gator = gator;
    this->type = type;
    this->released = false;
    this->initiated = false;

    setScatterPoint();

    resetOrientation();
    setDefaultPosition();

    // Load images for different directions & frightened mode
    forward.load("://Images/Characters/" + name + "_forward.png");
    reverse.load("://Images/Characters/" + name + "_reverse.png");
    up.load("://Images/Characters/" + name + "_forward_up.png");
    down.load("://Images/Characters/" + name + "_forward_down.png");
    frightMeat.load("://Images/Characters/frightMeat.png");
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (mode == Movement::FRIGHTENED)
    {
        painter->drawPixmap(posx,posy,charW,charW,frightMeat);
    }
    else
    {
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

void Enemy::setSpeed(int speed)
{
    if (speed == 2 || speed == 5)
    {
        while ((posx % speed) != 0 || ((posy % speed) != 0))    // To avoid leaving path bounds
        {
            move();
        }
        this->speed = speed;
    }
}

bool Enemy::isReleased() const
{
    return released;
}

void Enemy::setReleased(bool value)
{
    released = value;
}

bool Enemy::isInitiated() const
{
    return initiated;
}

void Enemy::setInitiated(bool value)
{
    initiated = value;
}

Movement Enemy::getMode() const
{
    return mode;
}

void Enemy::setMode(const Movement mode)
{
    // Changes movement mode and speed pertaining to that mode

    if (mode == Movement::FRIGHTENED)   // Enemy moves slower in frightened mode (Speed = 2)
    {
        setSpeed(2);
    }
    else                                // Regular speed (Speed = 5)
    {
        setSpeed(5);
    }
    this->mode = mode;
}

void Enemy::setScatterPoint()
{
    // Each GhostType has a default scatter position

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

void Enemy::resetOrientation()
{
    // By default Enemy faces right
    facingDirection = Direction::RIGHT;
    direction = Direction::RIGHT;
    nextDirection = Direction::NONE;        // Default NONE since Enemy has not decided on next movement at this point

    setMode(Movement::CHASE);               // Default movement mode for Enemy
}

void Enemy::setDefaultPosition()
{
    released = false;                       // Default x and y position is inside the box, therefore it is not released
    setPosx(defaultPosx);
    setPosy(defaultPosy);
}

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


// Movement mechanics

void Enemy::chase()
{
    /* Will change directions based on Player position, without evr going backwards.
     * There is also implementation for when Enemy moves inside tube, since it moves
     * slower when doing so. */
    QPoint point;

    // Determines the next direction Enemy will move
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
    else    // When a wall is encountered
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
            else    // Will go either way if Player is infront of Enemy
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
            else    // Will go either way if Player is infront of Enemy
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

    // Switch to the to the next direction if Enemy is able to move in said direction
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


    // Actual movement: Changes Enemy position depending on currently set direction
    switch (direction)
    {
    case LEFT:
        point.setX(posx - speed);
        point.setY(posy);
        facingDirection = direction;

        if (posx < 90 && posy == 270)           // Going through left tube
        {
            posx -= 2;
            moving = true;
            if (posx <= 0)
            {
                posx = 520;
            }
        }
        else if (posx > 430 && posy == 270)     // Going through right tube
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

        if (posx > 430 && posy == 270)          // Going through left tube
        {
            posx += 2;
            moving = true;
            if (posx >= 520)
            {
                posx = 0;
            }
        }
        else if (posx < 90 && posy == 270)      // Going through right tube
        {
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

void Enemy::scatter()
{
    /* Follows the CHASE mechanics for the most part, except it uses
     * the set scatter position as a target. */
    QPoint point;

    if (moving)
    {
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

void Enemy::frightened()
{
    /* Follows the CHASE mechanics for the most part, except it first
     * selects a pseudorandom direction that is used as the next
     * direction Enemy will follow. */
    QPoint point;

    // Sets a pseudorandom next direction
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
