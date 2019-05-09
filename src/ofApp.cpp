#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(10);
    //ofSetBackgroundAuto(false);

    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    debugMode = false;
    deleteWorms = false;
    //shader.load("noise.vert", "noise.frag");
    //shader.load("vertex_shader.vert", "frag_shader.frag");
    //fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

    //Box2D code
    b2Vec2 gravity(0.0f, 0.0f); 
    world = new b2World(gravity);
    world->SetContactListener(&contactListener);

    b2Vec2 windowDimensionsMeters = SimulationUtilities::pixelsToMeters(b2Vec2(ofGetWidth(), ofGetHeight()));
    xWidthInMeters = windowDimensionsMeters.x;
    yHeightInMeters = windowDimensionsMeters.y;

    //BOUNDARY SETUP
    setBoundary();

    for (int i = 0; i < 80; i++) {
        plants.push_back(Plant(ofRandom(600, ofGetWidth()-600), ofGetHeight(), ofRandom(40,50), ofRandom(150, 230), ofRandom(150, 230), ofRandom(25, 30), world));
    }

    for (int i = 0; i < 40; i++) {
        worms.push_back(WormBeing());
    }
    for (int i = 0; i < 13; i++) {
        rings.push_back(RingBeing());
    }

    for (int i = 0; i < 20; i++) {
        foodStuff.push_back(Food(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));
    }

    for (int i = 0; i < plants.size(); i++) {
        plants[i].testFoo();
    }

    for (int i = 0; i < worms.size(); i++) {
        worms[i].spawn(world);
    }
    for (int i = 0; i < rings.size(); i++) {
        rings[i].spawn(world);
    }

    for (int i = 0; i < foodStuff.size(); i++) {
        foodStuff[i].spawn(world);
    }

    timeStep = 1.0f / 60.0f;
    velocityIterations = 6;
    positionIterations = 2;
}

void ofApp::mousePressed(int x, int y, int button)
{
    //foodStuff.push_back(Food(x, y));
    //std::cout << foodStuff.size() - 1 << std::endl;

    //This triggers an error, probably has something to do with adding world elements
    //during the wrong part of the physics loop
    //foodStuff[foodStuff.size() - 1].spawn(world);
}

void ofApp::windowResized(int w, int h)
{
    resizeBoundary(w, h);
}

void ofApp::BeginContact(b2Contact * contact)
{
    b2Fixture* a = contact->GetFixtureA();
    b2Fixture* b = contact->GetFixtureB();
    //std::cout << contact << std::endl;
}

void ofApp::worldClock()
{
    std::cout << ofGetElapsedTimeMillis() << std::endl;

}


//--------------------------------------------------------------
void ofApp::update()
{
    world->Step(timeStep, velocityIterations, positionIterations);
    //world->ClearForces();
    //std::cout << world->IsLocked() << std::endl;
        //std::cout << world->IsLocked() << std::endl;
    //if (deleteWorms == true) {
        //for (int i = 0; i < worms.size(); i++) {
        //    for (int j = 0; j < worms[i].wormSegments.size(); j++) {
        //        b2Body* pWorm = worms[i].wormSegments[j];
        //        world->DestroyBody(pWorm);
        //    }
        //    //worms.erase(worm);
        //    //delete pWorm;
        //    //worms[i].die();
        //    //worms.erase(pWorm);
        //}
        //worms.clear();
        //for (int i = 0; i < plants.size(); i++) {
        //    for (int j = 0; j < plants[i].plant.size(); j++) {
        //        b2Body* pPlant = plants[i].plant[j];
        //        world->DestroyBody(pPlant);
        //    }
        //    //worms.erase(worm);
        //    //delete pWorm;
        //    //worms[i].die();
        //    //worms.erase(pWorm);
        //}
        //plants.clear();
        for (int i = 0; i < SimulationUtilities::toBeDestroyed.size(); i++) {
            world->DestroyBody(SimulationUtilities::toBeDestroyed[i]);
        }
        SimulationUtilities::toBeDestroyed.clear();
    //}

    
    


    for (int i = 0; i < worms.size(); i++) {
        worms[i].update();
        //for (int j = 0; j < foodStuff.size(); j++) {
        //    b2Vec2 force = foodStuff[i].positionMeters - worms[i].wormHead->GetPosition();
        //    force.Normalize();
        //    force *= 15.0f;
        //    b2Vec2 steer = force - worms[i].wormHead->GetLinearVelocity();
        //    worms[i].wormHead->ApplyForce(steer, worms[i].wormHead->GetWorldCenter(), true);
        //}
        //b2Vec2 force = food->positionMeters - worms[i].wormHead->GetPosition();
        //force.Normalize();
        //force *= 15.0f;
        //b2Vec2 steer = force - worms[i].wormHead->GetLinearVelocity();
        //worms[i].wormHead->ApplyForce(steer, worms[i].wormHead->GetWorldCenter(), true);
    }
    for (int i = 0; i < rings.size(); i++) {
        rings[i].update();
    }
    for (int i = 0; i < plants.size(); i++) {
        plants[i].update();

    }

    world->ClearForces();
}

//--------------------------------------------------------------
void ofApp::draw(){
    //fbo.begin();
    //shader.begin();
    //shader.setUniform2f("mouse", mouseX - ofGetWidth() / 2, ofGetHeight() / 2 - mouseY);

    ofSetColor(200, 120, 120);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofDrawBitmapString(ofGetFrameRate(), 10, 10);
    ofDrawBitmapString(ofGetElapsedTimeMillis(), 10, 30);
    for (int i = 0; i < worms.size(); i++) {
        worms[i].draw();
        if (debugMode == true) {
            worms[i].drawDebugInfo();
        }

    }
    for (int i = 0; i < rings.size(); i++) {
        rings[i].draw();
        if (debugMode == true) {
            rings[i].drawDebugInfo();
        }
    }
    
    for (int i = 0; i < plants.size(); i++) {
        plants[i].draw();

    }
    //fbo.end();
    //shader.end();

    //for (int i = 0; i < foodStuff.size(); i++) {
    //    foodStuff[i].draw();
    //}

    //texture.loadScreenData(0, 0, ofGetWidth(), ofGetHeight());
    //shader.setUniformTexture("sceneText", fbo.getTextureReference(0), 0);

    //texture.bind();
    //fbo.draw(100, 100);
    //texture.unbind();
    //fbo.clear();

}

void ofApp::setBoundary()
{
    edgeBodyDefTop.type = b2_staticBody;
    edgeBodyDefTop.position.Set(xWidthInMeters / 2, 0);
    edgeBodyTop = world->CreateBody(&edgeBodyDefTop);
    edgeShapeTop.Set(b2Vec2(xWidthInMeters / 2 * -1, 0), b2Vec2(xWidthInMeters / 2, 0));
    topRef = edgeBodyTop->CreateFixture(&edgeShapeTop, 0.0f);

    edgeBodyDefRight.type = b2_staticBody;
    edgeBodyDefRight.position.Set(xWidthInMeters, yHeightInMeters / 2);
    edgeBodyRight = world->CreateBody(&edgeBodyDefRight);
    edgeShapeRight.Set(b2Vec2(0, yHeightInMeters / 2 * -1), b2Vec2(0, yHeightInMeters / 2));
    rightRef = edgeBodyRight->CreateFixture(&edgeShapeRight, 0.0f);

    edgeBodyDefBottom.type = b2_staticBody;
    edgeBodyDefBottom.position.Set(xWidthInMeters / 2, yHeightInMeters);
    edgeBodyBottom = world->CreateBody(&edgeBodyDefBottom);
    edgeShapeBottom.Set(b2Vec2(xWidthInMeters / 2 * -1, 0), b2Vec2(xWidthInMeters / 2, 0));
    bottomRef = edgeBodyBottom->CreateFixture(&edgeShapeBottom, 0.0f);

    edgeBodyDefLeft.type = b2_staticBody;
    edgeBodyDefLeft.position.Set(0, yHeightInMeters / 2);
    edgeBodyLeft = world->CreateBody(&edgeBodyDefLeft);
    edgeShapeLeft.Set(b2Vec2(0, yHeightInMeters / 2 * -1), b2Vec2(0, yHeightInMeters / 2));
    leftRef = edgeBodyLeft->CreateFixture(&edgeShapeLeft, 0.0f);
}

void ofApp::resizeBoundary(int w, int h)
{
    b2Vec2 resizedWindowDimensions = SimulationUtilities::pixelsToMeters(b2Vec2(w, h));
    float xWidthInMeters = resizedWindowDimensions.x;
    float yHeightInMeters = resizedWindowDimensions.y;
    //edgeBodyTop->DestroyFixture(topRef);
    //edgeBodyRight->DestroyFixture(rightRef);
    //edgeBodyBottom->DestroyFixture(bottomRef);
    //edgeBodyLeft->DestroyFixture(leftRef);

    //edgeBodyDefTop.type = b2_staticBody;
    //edgeBodyDefTop.position.Set(xWidthInMeters / 2, 0);
    //edgeBodyTop = world->CreateBody(&edgeBodyDefTop);
    //edgeShapeTop.Set(b2Vec2(xWidthInMeters / 2 * -1, 0), b2Vec2(xWidthInMeters / 2, 0));
    //edgeBodyTop->CreateFixture(&edgeShapeTop, 0.0f);
    //edgeBodyTop->GetFixtureList()[0].GetShape()->m_radius = xWidthInMeters;

    //edgeBodyDefRight.type = b2_staticBody;
    //edgeBodyDefRight.position.Set(xWidthInMeters, yHeightInMeters / 2);
    //edgeBodyRight = world->CreateBody(&edgeBodyDefRight);
    //edgeShapeRight.Set(b2Vec2(0, yHeightInMeters / 2 * -1), b2Vec2(0, yHeightInMeters / 2));
    //edgeBodyRight->CreateFixture(&edgeShapeRight, 0.0f);

    //edgeBodyRight->GetFixtureList()[0].GetShape()->m_radius = yHeightInMeters;

    //edgeBodyDefBottom.type = b2_staticBody;
    //edgeBodyDefBottom.position.Set(xWidthInMeters / 2, yHeightInMeters);
    //edgeBodyBottom = world->CreateBody(&edgeBodyDefBottom);
    //edgeShapeBottom.Set(b2Vec2(xWidthInMeters / 2 * -1, 0), b2Vec2(xWidthInMeters / 2, 0));
    //edgeBodyBottom->CreateFixture(&edgeShapeBottom, 0.0f);

    //edgeBodyBottom->GetFixtureList()[0].GetShape()->m_radius = xWidthInMeters;

    //edgeBodyDefLeft.type = b2_staticBody;
    //edgeBodyDefLeft.position.Set(0, yHeightInMeters / 2);
    //edgeBodyLeft = world->CreateBody(&edgeBodyDefLeft);
    //edgeShapeLeft.Set(b2Vec2(0, yHeightInMeters / 2 * -1), b2Vec2(0, yHeightInMeters / 2));
    //edgeBodyLeft->CreateFixture(&edgeShapeLeft, 0.0f);

    //edgeBodyLeft->GetFixtureList()[0].GetShape()->m_radius = yHeightInMeters;
}

void ofApp::keyPressed(int key)
{
    // if 'i' is pressed, show some info
    if (key == 105) {
        debugMode =  !debugMode;
        deleteWorms = true;
    }
}