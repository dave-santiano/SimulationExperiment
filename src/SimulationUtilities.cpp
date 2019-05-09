#include "SimulationUtilities.h"
const float SimulationUtilities::TO_PIXELS_SCALING_FACTOR = 30.0f;
const float SimulationUtilities::TO_METERS_SCALING_FACTOR = 1 / TO_PIXELS_SCALING_FACTOR;
vector<b2Body*>SimulationUtilities::toBeDestroyed;
vector<string> SimulationUtilities::dreams = { "null", " To be the fifth member of BlackPink", "To have a bookshelf",
    "To have a camera storage room", "To be David Bowie" , "To be an old-town hoe", "To be financially independent","To be able to do a split",
"To hit all 7 continents by 20", "To be calm perpetually", "To own a stone-casted house with a fireplace, at the north bank of the Mediterranean",
"To transcend this mortal coil", "To be happy", "To make a difference in the world", "To retire and live in a house in the woods till death",
"To live in Vietnam", "That the world is transformed into a society of agrarians", "To own 50 cats"};

vector<string> SimulationUtilities::names = {"Steve", "Cornelius", "Olesya", "Bartholomew", "Joe", "Steve", "Hemingway", "Earnest", 
"Hugo", "Sylvia", "Dorothy", "Gertrude", "Bertha", "Robin", "Brian", "Tina", "Jackie", "Cindy", "Sophie", "Kaaatherine", "Thomas", "Millie",
"Kevin", "Dave"};

SimulationUtilities::SimulationUtilities()
{
}


SimulationUtilities::~SimulationUtilities()
{
}

b2Vec2 SimulationUtilities::pixelsToMeters(float xPixels, float yPixels)
{
    float xMeters = 0;
    float yMeters = 0;
    xMeters = xPixels * TO_METERS_SCALING_FACTOR;
    yMeters = yPixels * TO_METERS_SCALING_FACTOR;
    b2Vec2 convertedValues = { xMeters, yMeters };
    return convertedValues;
}

b2Vec2 SimulationUtilities::pixelsToMeters(b2Vec2 position)
{
    float xMeters = 0;
    float yMeters = 0;
    yMeters = position.y * TO_METERS_SCALING_FACTOR;
    xMeters = position.x * TO_METERS_SCALING_FACTOR;
    b2Vec2 convertedValues = { xMeters, yMeters };
    return convertedValues;
}

b2Vec2 SimulationUtilities::metersToPixels(float xMeters, float yMeters)
{
    float xPixels = 0;
    float yPixels = 0;
    xPixels = xMeters * TO_PIXELS_SCALING_FACTOR;
    yPixels = yMeters * TO_PIXELS_SCALING_FACTOR;
    b2Vec2 convertedValues = { xPixels, yPixels };
    return convertedValues;
}

b2Vec2 SimulationUtilities::metersToPixels(b2Vec2 position)
{
    float xPixels = 0;
    float yPixels = 0;
    xPixels = position.x * TO_PIXELS_SCALING_FACTOR;
    yPixels = position.y * TO_PIXELS_SCALING_FACTOR;
    b2Vec2 convertedValues = { xPixels, yPixels };
    return convertedValues;
}

void SimulationUtilities::addToDestroy(b2Body* body)
{
    toBeDestroyed.push_back(body);
}

float SimulationUtilities::pixelsToMeters(float pixels)
{
    float meters = pixels * TO_METERS_SCALING_FACTOR;
    return meters;
}

float SimulationUtilities::metersToPixels(float meters)
{
    float pixels = meters * TO_PIXELS_SCALING_FACTOR;
    return pixels;
}
