#include "enemy.h"
#include <iostream>

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

    setScatterPoint();

    resetOrientation();

    mode = Movement::SCATTER;
    released = false;
    initiated = false;

    forward.load("://Images/Characters/" + name + "_forward.png");
    reverse.load("://Images/Characters/" + name + "_reverse.png");
    up.load("://Images/Characters/" + name + "_forward_up.png");
    down.load("://Images/Characters/" + name + "_forward_down.png");
//    forwardScared.load("://Images/Characters/" + name + "_forward_scared.png");
//    reverseScared.load("://Images/Characters/" + name + "_reverse_scared.png");
//    upScared.load("://Images/Characters/" + name + "_forward_scared_up.png");
//    downScared.load("://Images/Characters/" + name + "_forward_scared_down.png");
    frightMeat.load("://Images/Characters/frightMeat.png");
}

QRectF Enemy::boundingRect() const
{
    return QRect(0,0,charW,charH);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (mode == Movement::FRIGHTENED)
    {
        switch(facingDirection)
        {
        case LEFT:
            painter->drawPixmap(posx,posy,charW,charW,frightMeat);
            break;
        case RIGHT:
            painter->drawPixmap(posx,posy,charW,charW,frightMeat);
            break;
        case UP:
            painter->drawPixmap(posx,posy,charW,charW,frightMeat);
            break;
        case DOWN:
            painter->drawPixmap(posx,posy,charW,charW,frightMeat);
            break;
        case NONE:
            painter->drawPixmap(posx,posy,charW,charW,frightMeat);
            break;
        }
    }
    else
    {
        switch(facingDirection)
        {
        case LEFT:
            painter->drawPixmap(posx,posy,charW,charW,reverse);
            break;
        case RIGHT:
            painter->drawPixmap(posx,posy,charW,charW,forward);
            break;
        case UP:
            painter->drawPixmap(posx,posy,charW,charW,up);
            break;
        case DOWN:
            painter->drawPixmap(posx,posy,charW,charW,down);
            break;
        case NONE:
            painter->drawPixmap(posx,posy,charW,charW,forward);
            break;
        }
    }
}

int Enemy::getSpeed() const
{
    return speed;
}

void Enemy::setSpeed(int speed)
{
    while ((posx % speed) != 0 || ((posy % speed) != 0))
    {
        move();
    }
    this->speed = speed;
}

int Enemy::getPosx() const
{
    return posx;
}

void Enemy::setPosx(int x)
{
    if (x >= 0 && x <= 520)
    {
        posx = x;
    }
}

int Enemy::getPosy() const
{
    return posy;
}

void Enemy::setPosy(int y)
{
    if (y >= 10 && y <= 570)
    {
        posy = y;
    }
}

bool Enemy::isMoving() const
{
    return moving;
}

void Enemy::setMoving(bool value)
{
    moving = value;
}

void Enemy::setMode(const Movement mode)
{
    if (mode == Movement::FRIGHTENED)
    {
        setSpeed(2);
    }
    else
    {
        setSpeed(5);
    }
    this->mode = mode;
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

void Enemy::resetOrientation()
{
    facingDirection = Direction::RIGHT;
    direction = Direction::RIGHT;
    nextDirection = Direction::NONE;

    mode = Movement::CHASE;
}

void Enemy::setDefaultPosition()
{
    released = false;
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

void Enemy::chase()
{
    QPoint point;

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

void Enemy::scatter()
{
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
