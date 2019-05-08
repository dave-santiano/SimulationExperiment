#pragma once
#include "ofMain.h"
#include "Box2D/Box2D.h"
#include "SimulationUtilities.h"
#include "WormBeing.h"
#include "Entity.h"

class Food : public Entity
{
public:
    Food(float x, float y);
    ~Food();
    void spawn(b2World* world);
    void draw();
    void update();
    void checkCollision(Entity* other) override;
    float x;
    float y;
    b2Vec2 positionPixels;
    b2Vec2 positionMeters;
private:
    float size;
    float sizeInMeters;
    b2BodyDef foodBodyDef;
    b2Body* foodBody;
    b2FixtureDef foodBodyFixtureDef;
    b2PolygonShape foodBox;


};

