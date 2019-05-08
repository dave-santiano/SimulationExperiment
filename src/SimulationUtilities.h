#pragma once
#include "ofMain.h"
#include "Box2D/Box2D.h"


class SimulationUtilities
{
public:
    SimulationUtilities();
    ~SimulationUtilities();
    static b2Vec2 pixelsToMeters(float xPixels, float yPixels);
    static b2Vec2 pixelsToMeters(b2Vec2 position);
    static b2Vec2 metersToPixels(float xMeters, float yMeters);
    static b2Vec2 metersToPixels(b2Vec2 position);
    static float pixelsToMeters(float pixels);
    static float metersToPixels(float meters);
    static vector<string>dreams;
    static vector<string>names;
 


private:
    static const float TO_PIXELS_SCALING_FACTOR;
    static const float TO_METERS_SCALING_FACTOR;
    //static const float TO_PIXELS_SCALING_FACTOR = 30.0f;
    //static const float TO_METERS_SCALING_FACTOR = 1 / TO_PIXELS_SCALING_FACTOR;
};

