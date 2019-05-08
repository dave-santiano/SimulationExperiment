#pragma once
#include "ofMain.h"
#include "Box2D/Box2D.h"
#include "Entity.h"

class SimContactListener : public b2ContactListener
{
public:
    void BeginContact(b2Contact* contact) override
    {
        //b2Fixture* fixtureA = contact->GetFixtureA();
        //b2Fixture* fixtureB = contact->GetFixtureB();
        //b2Body* body1 = fixtureA->GetBody(); 
        //b2Body* body2 = fixtureB->GetBody();

        Entity* bodyAUserData = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
        Entity* bodyBUserData = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();
        //std::cout << typeid(bodyAUserData).name() << std::endl;
        //std::cout << typeid(bodyBUserData).name() << std::endl;
        //bodyAUserData->checkCollision(bodyBUserData);
        if (bodyAUserData != NULL && bodyBUserData != NULL) {
            if (typeid(bodyAUserData).name() == typeid(bodyBUserData).name()) {
                bodyAUserData->checkCollision(bodyBUserData);
                //std::cout << "entity interaction detected" << std::endl;
            }
        }

        //std::cout << "started";
        //if ((void*)body1->GetUserData() == "food") { 
        //    std::cout << "food found" << std::endl;
        //}

    }
    void EndContact(b2Contact* contact) override
    {
        //std::cout << "ended\n";
    }
};

