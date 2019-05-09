
#pragma once

#include "ofMain.h"
#include "Box2D/Box2D.h"
#include "WormBeing.h"
#include "RingBeing.h"
#include "Plant.h"
#include "Food.h"
#include "SimulationUtilities.h"
#include "SimContactListener.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void setBoundary();
        void resizeBoundary(int w, int h);
		void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        void windowResized(int w, int h);
        void BeginContact(b2Contact* contact);
        void worldClock();

		//void keyReleased(int key);
		//void mouseMoved(int x, int y );
		//void mouseDragged(int x, int y, int button);
		//void mouseReleased(int x, int y, int button);
		//void mouseEntered(int x, int y);
		//void mouseExited(int x, int y);
		//void dragEvent(ofDragInfo dragInfo);
		//void gotMessage(ofMessage msg);



    private:
        ofFbo fbo;
        ofShader shader;
        ofTexture texture;

        bool deleteWorms;
        bool initialSeed;

        SimContactListener contactListener;
        Food* food;
        bool debugMode;

        ofTrueTypeFont debugFont;
        float xWidthInMeters;
        float yHeightInMeters;
        vector<WormBeing> worms;
        vector<RingBeing> rings;
        vector<Food> foodStuff;
        vector<Plant> plants;


        b2World* world;

        b2BodyDef edgeBodyDefTop;
        b2EdgeShape edgeShapeTop;
        b2Body* edgeBodyTop;
        b2Fixture* topRef;

        b2BodyDef edgeBodyDefRight;
        b2EdgeShape edgeShapeRight;
        b2Body* edgeBodyRight;
        b2Fixture* rightRef;

        b2BodyDef edgeBodyDefBottom;
        b2EdgeShape edgeShapeBottom;
        b2Body* edgeBodyBottom;
        b2Fixture* bottomRef;

        b2BodyDef edgeBodyDefLeft;
        b2EdgeShape edgeShapeLeft;
        b2Body* edgeBodyLeft;
        b2Fixture* leftRef;

        float32 timeStep;
        int32 velocityIterations;
        int32 positionIterations;
};
