#pragma once
#include "ofMain.h"
#include "Box2D/Box2D.h"
#include "SimulationUtilities.h"
#include "Entity.h"

class RingBeing : public Entity
{
public:
    RingBeing();
    ~RingBeing();
    void spawn(b2World* world);
    void update();
    void draw();
    void drawDebugInfo();
    void randomBehavior();
    void assignJoints(b2Body* bodyA, b2Body* bodyB, b2World* world);
    void checkCollision(Entity* other) override;
    b2Body* ringHead;
    b2Body* ringBody;
    b2Body* ringBody2;
    b2PolygonShape dynamicBox;
    b2RevoluteJointDef jointDef;
    b2RevoluteJoint* joint;

private:
    float r;
    float g;
    float b;
    string dream;
    string name;
    ofTrueTypeFont debugFont;
    float maxSpeed;
    int bodyLength;
    b2Vec2 initPosition;
    float density;
    float friction;

    float xSegmentDimension;
    float ySegmentDimension;

    float xCollision;
    float yCollision;

    vector<b2Body*> ringSegments;

    b2Body* jointA;
    b2Body* jointB;

    b2BodyDef ringBodyDef;
    b2BodyDef ringBodyDef2;
    b2FixtureDef ringBodyFixtureDef;
    b2FixtureDef ringBodyFixtureDef2;

    b2BodyDef ringHeadDef;
    b2FixtureDef ringHeadFixtureDef;



};

