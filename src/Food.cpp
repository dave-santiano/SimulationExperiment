#include "Food.h"



Food::Food(float x, float y) :
    x(x),
    y(y),
    positionPixels(x, y),
    positionMeters(SimulationUtilities::pixelsToMeters(x), SimulationUtilities::pixelsToMeters(y)),
    size(10.0f),
    sizeInMeters(SimulationUtilities::pixelsToMeters(size))
{}

Food::~Food()
{
}

void Food::spawn(b2World* world)
{
    //x = ofRandom(0, positionMeters.x);
    //y = ofRandom(0, positionMeters.y);
    //positionMeters = { SimulationUtilities::pixelsToMeters(x), SimulationUtilities::pixelsToMeters(y) };
    
    foodBodyDef.type = b2_dynamicBody;
    foodBodyDef.position.Set(positionMeters.x, positionMeters.y);
    
    foodBody = world->CreateBody(&foodBodyDef);
    foodBody->SetUserData(this);

    foodBox.SetAsBox(sizeInMeters, sizeInMeters);

    foodBodyFixtureDef.shape = &foodBox;
    foodBodyFixtureDef.density = 1.0f;
    foodBodyFixtureDef.friction = 0.3f;
    foodBody->CreateFixture(&foodBodyFixtureDef);
}

void Food::draw()
{
    ofSetColor(125);
    ofDrawRectangle(positionPixels.x, positionPixels.y, size, size);
    //std::cout << SimulationUtilities::metersToPixels(positionMeters.x) << " " << SimulationUtilities::metersToPixels(positionMeters.y) << std::endl;
    //std::cout << positionPixels.x << " " << positionPixels.y << std::endl;
}

void Food::update()
{

}


void Food::checkCollision(Entity * other)
{
    if (WormBeing* pWorm = (WormBeing*)other) {
    }
}