#pragma once
#include "ofMain.h"
#include "Box2D/Box2D.h"
#include "SimulationUtilities.h"
#include "Entity.h"
#include "Food.h"

class WormBeing : public Entity
{
public:
    WormBeing();
    ~WormBeing();
    void spawn(b2World* world);
    void update();
    void draw();
    void randomBehavior();
    void assignJoints(b2Body* bodyA, b2Body* bodyB, b2World* world);
    void drawDebugInfo();
    void eat();
    void checkCollision(Entity* other) override;

    void internalClock();

    b2Body* wormHead;
    b2PolygonShape dynamicBox;
    //b2RopeJointDef jointDef;
    //b2RopeJoint* joint;
    b2RevoluteJointDef jointDef;
    b2RevoluteJoint* joint;
    string dream;
    string name;

private:

    float lap;
    float interval;

    ofImage head;


    float r;
    float g;
    float b;
    ofTrueTypeFont debugFont;
    float hungerLevel;

    float maxSpeed;
    int bodyLength;
    b2Vec2 initPosition;
    float density;
    float friction;

    float xSegmentDimension;
    float ySegmentDimension;

    float xHeadDimension;
    float yHeadDimension;

    float xCollision;
    float yCollision;

    vector<b2Body*> wormSegments;

    b2Body* jointA;
    b2Body* jointB;

    b2BodyDef wormBodyDef;
    b2BodyDef wormBodyDef2;
    b2FixtureDef wormBodyFixtureDef;
    b2FixtureDef wormBodyFixtureDef2;

    b2BodyDef wormHeadDef;
    b2FixtureDef wormHeadFixtureDef;


                        
};

