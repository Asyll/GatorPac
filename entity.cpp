#include "entity.h"

Entity::Entity(int posx, int posy, int speed) :
    defaultPosx(posx),
    defaultPosy(posy)
{
    this->posx = posx;
    this->posy = posy;
    this->speed = speed;

    setMoving(false);

    resetOrientation();
}

QRectF Entity::boundingRect() const
{
    return QRect(0,0,charW,charH);
}

int Entity::getPosx() const
{
    return posx;
}

void Entity::setPosx(int x)
{
    posx = x;
}

int Entity::getPosy() const
{
    return posy;
}

void Entity::setPosy(int y)
{
    posy = y;
}

int Entity::getSpeed() const
{
    return speed;
}

bool Entity::isMoving() const
{
    return moving;
}

void Entity::setMoving(bool value)
{
    moving = value;
}

void Entity::resetOrientation()
{
    // By default any Entity faces right
    facingDirection = Direction::RIGHT;
    direction = Direction::NONE;
    nextDirection = Direction::NONE;        // Default NONE since Entity has not decided on next movement at this point
}

void Entity::setDefaultPosition()
{
    setPosx(defaultPosx);
    setPosy(defaultPosy);
}

