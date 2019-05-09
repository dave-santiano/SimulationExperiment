#include "Plant.h"



Plant::Plant()
{



}


Plant::Plant(float x, float y, float _r, float _g, float _b, float length, b2World * world)
{
    world = world;
    xSegmentDimension = 15.0f;
    ySegmentDimension = 15.0f;
    debugFont.load("runescape_uf.ttf", 10);
    head.loadImage("smile.png");
    positionMeters = SimulationUtilities::pixelsToMeters(x, y);


    xCollision = SimulationUtilities::pixelsToMeters(xSegmentDimension);
    yCollision = SimulationUtilities::pixelsToMeters(ySegmentDimension);

    staticBox.SetAsBox(xCollision, yCollision);
    dynamicBox.SetAsBox(xCollision, yCollision);

    plantLength = length;

    maxSpeed = ofRandom(1.0f, 10.0f);

    r = _r;
    g = _g;
    b = _b;

    plantRootDef.type = b2_staticBody;
    plantRootDef.position.Set(positionMeters.x, positionMeters.y);

    plantRoot = world->CreateBody(&plantRootDef);

    plantRootFixtureDef.shape = &staticBox;
    plantRootFixtureDef.filter.groupIndex = -1;
    plantRoot->CreateFixture(&plantRootFixtureDef);

    plant.push_back(plantRoot);

    jointA = plantRoot;

    for (int i = 0; i < plantLength; i++) {
        b2Body* stemNode;
        b2BodyDef stemNodeDef;
        b2FixtureDef stemNodeFixtureDef;

        stemNodeDef.type = b2_dynamicBody;
        stemNodeDef.position.Set(jointA->GetPosition().x, jointA->GetPosition().y - 0.1f);
        stemNode = world->CreateBody(&stemNodeDef);

        stemNodeFixtureDef.shape = &dynamicBox;
        stemNodeFixtureDef.density = 1.0f;
        stemNodeFixtureDef.friction = 0.3f;
        stemNodeFixtureDef.filter.groupIndex = -1;
        stemNode->CreateFixture(&stemNodeFixtureDef);
        plant.push_back(stemNode);
        jointB = stemNode;
        assignJoints(jointA, jointB, world);
        jointA = stemNode;
    }
    plantHeadDef.type = b2_dynamicBody;
    plantHeadDef.position.Set(jointA->GetPosition().x, jointA->GetPosition().y - 0.1f);

    plantHead = world->CreateBody(&plantHeadDef);

    plant.push_back(plantHead);
    plantHeadFixtureDef.shape = &dynamicBox;
    plantHeadFixtureDef.filter.groupIndex = -1;
    plantHead->CreateFixture(&plantHeadFixtureDef);

    assignJoints(jointA, plantHead, world);



}

void Plant::testFoo()
{
    plantRoot->SetUserData(this);
    plantHead->SetUserData(this);
    float increment = (2 * PI) / 80;

    for (float i = 0; i < 2 * PI; i += increment) {
        sinValues.push_back(sin(i));
        cosValues.push_back(cos(i));
    }
}


void Plant::update()
{
    //b2Vec2 velocity = plantHead ->GetLinearVelocity();
    //if (velocity.Length() < maxSpeed) {
    //    for (int i = 0; i < sinValues.size(); i++) {
    //        plantHead->ApplyForce(b2Vec2(sinValues[i] * 20.0f, cosValues[i] * 20.0f), plantHead->GetWorldCenter(), true);
    //    }
    //}
    plantHead->ApplyLinearImpulse(b2Vec2(ofRandom(-1, 1), ofRandom(2, -5)), plantHead->GetWorldCenter(), true);

}

void Plant::draw()
{
    ofSetColor(r, g, b, 255);

    for (int i = 0; i < plant.size(); i++) {
        b2Vec2 position = plant[i]->GetPosition();
        b2Vec2 convertedPosition = SimulationUtilities::metersToPixels(position);

        if (i > 0) {
            b2Vec2 secondPosition = plant[i - 1]->GetPosition();
            b2Vec2 secondConvertedPosition = SimulationUtilities::metersToPixels(secondPosition);
            ofDrawLine(convertedPosition.x, convertedPosition.y, secondConvertedPosition.x, secondConvertedPosition.y);
            ofSetLineWidth(7.0f);
        }

        if (i == plant.size() - 1) {
            b2Vec2 secondPosition = plant[plant.size() - 1]->GetPosition();
            b2Vec2 secondConvertedPosition = SimulationUtilities::metersToPixels(secondPosition);
            ofDrawEllipse(convertedPosition.x, convertedPosition.y, xSegmentDimension - 5, ySegmentDimension - 5);
            //head.draw(convertedPosition.x, convertedPosition.y, xSegmentDimension, ySegmentDimension);
            ofDrawLine(convertedPosition.x, convertedPosition.y, secondConvertedPosition.x, secondConvertedPosition.y);
        }
    }
}

void Plant::drawDebugInfo()
{
}

void Plant::assignJoints(b2Body * bodyA, b2Body * bodyB, b2World * world)
{
    jointDef.bodyA = bodyA;
    jointDef.bodyB = bodyB;
    jointDef.collideConnected = false;
    //jointDef.enableLimit = false;

    jointDef.localAnchorA.Set(-0.30, -0.30);
    jointDef.localAnchorB.Set(0.30, 0.30);
    joint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

}


Plant::~Plant()
{
    //world->DestroyBody(plantHead);
}

void Plant::checkCollision(Entity * other)
{
}

