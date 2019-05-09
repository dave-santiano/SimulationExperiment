#pragma once
#include "ofMain.h"
#include "Box2D.h"
#include "SimulationUtilities.h"
#include "Entity.h"


class Plant : public Entity
{
public:
    Plant();
    Plant(float x, float y, float _r, float _g, float _b, float length, b2World* world);
    ~Plant();



    void update();
    void draw();
    void drawDebugInfo();
    void assignJoints(b2Body* bodyA, b2Body* bodyB, b2World* world);
    void checkCollision(Entity* other) override;
    void testFoo();

    b2Body* plantHead;
    vector<b2Body*> plant;

private:
    b2World* world;
    b2BodyDef plantHeadDef;
    b2FixtureDef plantHeadFixtureDef;
    float xSegmentDimension;
    float ySegmentDimension;

    float xCollision;
    float yCollision;
    
    float plantLength;

    b2Vec2 positionMeters;
    ofTrueTypeFont debugFont;

    float r;
    float g;
    float b;
    float maxSpeed;
    float density;
    float friction;

    ofImage head;

    vector<float> sinValues;
    vector<float> cosValues;


    b2BodyDef plantBodyDef;
    b2FixtureDef plantBodyFixtureDef;

    b2PolygonShape staticBox;
    b2PolygonShape dynamicBox;

    b2Body* plantRoot;
    b2BodyDef plantRootDef;
    b2FixtureDef plantRootFixtureDef;


    b2Body* jointA;
    b2Body* jointB;

    b2RevoluteJointDef jointDef;
    b2RevoluteJoint* joint;


    


};

