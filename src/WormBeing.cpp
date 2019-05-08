#include "WormBeing.h"

WormBeing::WormBeing() :
    bodyLength(20),
    initPosition(SimulationUtilities::pixelsToMeters(ofRandom(0,ofGetWidth()), ofRandom(0, ofGetHeight()))),
    density(1.0f),
    friction(0.3f)
{}

WormBeing::~WormBeing()
{
}

void WormBeing::spawn(b2World* world)
{
    dream = SimulationUtilities::dreams[(int)ofRandom(0, SimulationUtilities::dreams.size() - 1)];
    name = SimulationUtilities::names[(int)ofRandom(0, SimulationUtilities::names.size() - 1)];
    xSegmentDimension = 5.0f;
    ySegmentDimension = 5.0f;

    xHeadDimension = 7.0f;
    yHeadDimension = 7.0f;

    lap = 0;
    interval = 5000.0f;


    debugFont.load("runescape_uf.ttf", 10);
    head.loadImage("smile.png");

    maxSpeed = ofRandom(0.09f, 1.0f);

    hungerLevel = 100;

    r = ofRandom(150, 180);
    g = ofRandom(230, 255);
    b = ofRandom(150, 180);

    //Head
    wormHeadDef.type = b2_dynamicBody;
    wormHeadDef.position.Set(initPosition.x, initPosition.y/2);
    wormHead = world->CreateBody(&wormHeadDef);
    xCollision = SimulationUtilities::pixelsToMeters(xHeadDimension);
    yCollision = SimulationUtilities::pixelsToMeters(yHeadDimension);

    dynamicBox.SetAsBox(xCollision, yCollision);
    wormHeadFixtureDef.shape = &dynamicBox;
    wormHeadFixtureDef.density = 1.0f;
    wormHeadFixtureDef.friction = 0.3f;
    wormHead->CreateFixture(&wormHeadFixtureDef);

    xCollision = SimulationUtilities::pixelsToMeters(xSegmentDimension);
    yCollision = SimulationUtilities::pixelsToMeters(ySegmentDimension);

    wormSegments.push_back(wormHead);
    jointA = wormHead;

    //Append body segments
    for (int i = 0; i < bodyLength; i++) {
        b2Body* wormSegment;
        b2BodyDef wormSegmentDef;
        b2FixtureDef wormSegmentFixtureDef;

        wormSegmentDef.type = b2_dynamicBody;
        wormSegmentDef.position.Set(jointA->GetPosition().x + 0.1f, jointA->GetPosition().y + 0.1f);
        wormSegment = world->CreateBody(&wormSegmentDef);

        wormSegmentFixtureDef.shape = &dynamicBox;
        wormSegmentFixtureDef.density = 1.0f;
        wormSegmentFixtureDef.friction = 0.3f;
        wormSegment->CreateFixture(&wormSegmentFixtureDef);
        wormSegments.push_back(wormSegment);


        jointB = wormSegment;
        assignJoints(jointA, jointB, world);
        jointA = wormSegment;
    }
    wormHead->SetAngularDamping(10.0f);
    wormHead->SetUserData(this);
}

void WormBeing::update()
{
    
    randomBehavior();
    internalClock();
}

void WormBeing::draw()
{
    ofSetColor(r,g,b);
    for (int i = 0; i < wormSegments.size(); i++) {
        b2Vec2 position = wormSegments[i]->GetPosition();
        b2Vec2 convertedPosition = SimulationUtilities::metersToPixels(position);
        //ofDrawEllipse(convertedPosition.x, convertedPosition.y, xSegmentDimension, ySegmentDimension);
        if (i > 0) {
            b2Vec2 secondPosition = wormSegments[i - 1]->GetPosition();
            b2Vec2 secondConvertedPosition = SimulationUtilities::metersToPixels(secondPosition);
            ofDrawLine(convertedPosition.x, convertedPosition.y, secondConvertedPosition.x, secondConvertedPosition.y);
            ofSetLineWidth(7.0f);
        }
        if (i == 0) {
            ofDrawEllipse(convertedPosition.x, convertedPosition.y, xHeadDimension, yHeadDimension);
            //head.draw(convertedPosition.x, convertedPosition.y, xSegmentDimension + 10, ySegmentDimension + 10);

        }
    }
}

void WormBeing::randomBehavior()
{
    b2Vec2 velocity = wormHead->GetLinearVelocity();
    if (velocity.Length() < maxSpeed) {
        wormHead->ApplyLinearImpulse(b2Vec2(ofRandom(-10, 10), ofRandom(-10, 10)), wormHead->GetWorldCenter(), true);
    }
}

void WormBeing::assignJoints(b2Body* bodyA, b2Body* bodyB, b2World* world)
{
    jointDef.bodyA = bodyA;
    jointDef.bodyB = bodyB;
    jointDef.collideConnected = false;
    //jointDef.maxLength = 0.01f;
    jointDef.localAnchorA.Set(-0.15, -0.15);
    jointDef.localAnchorB.Set(0.15 ,   0.15);
    joint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
}

void WormBeing::drawDebugInfo()
{
    //debugFont.drawString("Name: " + name + '\n' + "pos: x:" + to_string(wormHead->GetPosition().x) + " y:" + to_string(wormHead->GetPosition().y) + '\n' + "Dream: " +
    //    dream,
    //    SimulationUtilities::metersToPixels(wormHead->GetPosition()).x + 20, SimulationUtilities::metersToPixels(wormHead->GetPosition()).y);
    debugFont.drawString("Name: " + name + '\n' + "Dream: " +
        dream,
        SimulationUtilities::metersToPixels(wormHead->GetPosition()).x + 20, SimulationUtilities::metersToPixels(wormHead->GetPosition()).y);
}

void WormBeing::checkCollision(Entity * other)
{
    if (Food* pFood = (Food*)other) {
        eat();
    }
}

void WormBeing::internalClock()
{
    if (ofGetElapsedTimeMillis() - lap > interval) {
        hungerLevel -= 10;
        //std::cout << hungerLevel << std::endl;
        lap = ofGetElapsedTimeMillis();
    }
}

void WormBeing::eat()
{
    hungerLevel += 30;
    //std::cout << hungerLevel << std::endl;
}
