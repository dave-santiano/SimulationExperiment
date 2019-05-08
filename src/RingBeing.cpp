#include "RingBeing.h"

RingBeing::RingBeing() :
    bodyLength(10),
    initPosition(SimulationUtilities::pixelsToMeters(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()))),
    density(1.0f),
    friction(0.3f)
{
}

RingBeing::~RingBeing()
{
}

void RingBeing::spawn(b2World* world)
{
    dream = SimulationUtilities::dreams[(int)ofRandom(0, SimulationUtilities::dreams.size() - 1)];
    name = SimulationUtilities::names[(int)ofRandom(0, SimulationUtilities::names.size() - 1)];

    xSegmentDimension = 15.0f;
    ySegmentDimension = 15.0f;
    debugFont.load("runescape_uf.ttf", 16);
    maxSpeed = ofRandom(1.0f, 10.0f);

    r = ofRandom(200, 255);
    g = ofRandom(150, 190);
    b = ofRandom(150, 180);
     
    //Head
    ringHeadDef.type = b2_dynamicBody;
    ringHeadDef.position.Set(initPosition.x, initPosition.y/2);
    ringHead = world->CreateBody(&ringHeadDef);
    xCollision = SimulationUtilities::pixelsToMeters(xSegmentDimension);
    yCollision = SimulationUtilities::pixelsToMeters(ySegmentDimension);

    dynamicBox.SetAsBox(xCollision, yCollision);
    ringHeadFixtureDef.shape = &dynamicBox;
    ringHeadFixtureDef.density = 1.0f;
    ringHeadFixtureDef.friction = 0.3f;
    ringHead->CreateFixture(&ringHeadFixtureDef);

    ringSegments.push_back(ringHead);
    jointA = ringHead;

    //Append body segments
    for (int i = 0; i < bodyLength; i++) {
        b2Body* ringSegment;
        b2BodyDef ringSegmentDef;
        b2FixtureDef ringSegmentFixtureDef;

        ringSegmentDef.type = b2_dynamicBody;
        ringSegmentDef.position.Set(jointA->GetPosition().x + 0.1f, jointA->GetPosition().y + 0.1f);
        ringSegment = world->CreateBody(&ringSegmentDef);

        ringSegmentFixtureDef.shape = &dynamicBox;
        ringSegmentFixtureDef.density = 1.0f;
        ringSegmentFixtureDef.friction = 0.3f;
        ringSegment->CreateFixture(&ringSegmentFixtureDef);
        ringSegments.push_back(ringSegment);


        jointB = ringSegment;
        assignJoints(jointA, jointB, world);
        jointA = ringSegment;
    }
    assignJoints(jointA, ringHead, world);
    ringHead->SetAngularDamping(10.0f);
    ringHead->SetUserData(this);

}

void RingBeing::update()
{
    randomBehavior();
}

void RingBeing::draw()
{
    ofSetColor(r, g, b);
    for (int i = 0; i < ringSegments.size(); i++) {
        b2Vec2 position = ringSegments[i]->GetPosition();
        b2Vec2 convertedPosition = SimulationUtilities::metersToPixels(position);
        //ofDrawEllipse(convertedPosition.x, convertedPosition.y, xSegmentDimension, ySegmentDimension);
        if (i > 0) {
            b2Vec2 secondPosition = ringSegments[i - 1]->GetPosition();
            b2Vec2 secondConvertedPosition = SimulationUtilities::metersToPixels(secondPosition);
            ofLine(convertedPosition.x, convertedPosition.y, secondConvertedPosition.x, secondConvertedPosition.y);
            ofSetLineWidth(7.0f);
        }
        if (i == 0) {
            b2Vec2 secondPosition = ringSegments[ringSegments.size()-1]->GetPosition();
            b2Vec2 secondConvertedPosition = SimulationUtilities::metersToPixels(secondPosition);
            //ofDrawEllipse(convertedPosition.x, convertedPosition.y, xSegmentDimension, ySegmentDimension);
            ofLine(convertedPosition.x, convertedPosition.y, secondConvertedPosition.x, secondConvertedPosition.y);
        }
    }
}

void RingBeing::drawDebugInfo()
{
    debugFont.drawString("Name: " + name + '\n' + "Dream: " +  dream,
        SimulationUtilities::metersToPixels(ringHead->GetPosition()).x + 20, SimulationUtilities::metersToPixels(ringHead->GetPosition()).y);
}

void RingBeing::randomBehavior()
{
    b2Vec2 velocity = ringHead->GetLinearVelocity();
    if (velocity.Length() < maxSpeed) {
        ringHead->ApplyLinearImpulse(b2Vec2(ofRandom(-3, 3), ofRandom(-3, 3)), ringHead->GetWorldCenter(), true);
    }
}

void RingBeing::assignJoints(b2Body* bodyA, b2Body* bodyB, b2World* world)
{
    jointDef.bodyA = bodyA;
    jointDef.bodyB = bodyB;
    jointDef.collideConnected = false;
    jointDef.enableLimit = true;
    //jointDef.Set
    //jointDef.maxLength = 0.1f;
    //jointDef.localAnchorA.Set(bodyA->GetWorldCenter().x, bodyA->GetWorldCenter().y);
    //jointDef.localAnchorB.Set(bodyB->GetWorldCenter().x, bodyB->GetWorldCenter().y);
    jointDef.localAnchorA.Set(-0.2, -0.2);
    jointDef.localAnchorB.Set(0.2, 0.2);
    joint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
}

void RingBeing::checkCollision(Entity * other)
{
}
