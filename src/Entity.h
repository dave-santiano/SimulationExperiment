#pragma once
class Entity
{
public:
    Entity();
    ~Entity();

    virtual void Entity::checkCollision(Entity* other) = 0;

};

