#include "vmt.h"
#include "ObjectEditDialog.h"
#include "Quad2D.h"
#include "Object3D.h"
#include <map>
//--------------------------------------------------------------

Vmt::Vmt() : ofBaseApp() {
}

void Vmt::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE);

    //for smooth animation, set vertical sync if we can
	ofSetVerticalSync(true);
	// also, frame rate:
	ofSetFrameRate(60);

	ofSetVerticalSync(true);
	glEnable(GL_DEPTH_TEST); //lights look weird if depth test is not enabled

    vmtModel = new VmtModel();

    vmtModel->addNetNode("node1", "localhost", 54321, true, "cam2");

    vmtModel->setBackground(0.6f, 1.0f, 1.0f);

    vmtModel->addCamera("cam1");
	vmtModel->setCameraPos("cam1", 0,0,0);
	vmtModel->setCameraEye("cam1", 1,0,0);

    vmtModel->addCamera("cam2");
	vmtModel->setCameraPos("cam2", 0, 0, -30);
	vmtModel->setCameraEye("cam2", 0, 0,   0);

	vmtModel->activateCamera("cam2");

    vmtModel->addGroup("group1");
    vmtModel->addLayer("cam2", "layer1");
    vmtModel->addQuad("cam2", "layer1", "quad1");

    vmtModel->addQuadToGroup("group1", "cam2", "layer1", "quad1");
    vmtModel->enableQuad("cam2", "layer1", "quad1", true);

    vmtModel->addQuad("cam2", "layer1", "quad2");
    vmtModel->addQuadToGroup("group1", "cam2", "layer1", "quad2");
    vmtModel->setQuadPoint("cam2", "layer1", "quad2", 0, 10, 10);
    vmtModel->setQuadPoint("cam2", "layer1", "quad2", 1, 10, 20);
    vmtModel->setQuadPoint("cam2", "layer1", "quad2", 2, 30, 20);
    vmtModel->setQuadPoint("cam2", "layer1", "quad2", 3, 30, 10);
    vmtModel->enableQuad("cam2", "layer1", "quad2", true);

    vmtModel->setClientResolution("cam2", 1024, 768);

    vmtModel->addLayer("cam1", "layer2");
    vmtModel->addQuad("cam1", "layer2", "q3");
    vmtModel->enableQuad("cam1", "layer2", "q3", true);
    vmtModel->setQuadPoint("cam1", "layer2", "q3", 0, 10+20, 10+20);
    vmtModel->setQuadPoint("cam1", "layer2", "q3", 1, 10+20, 20+20);
    vmtModel->setQuadPoint("cam1", "layer2", "q3", 2, 30+20, 20+20);
    vmtModel->setQuadPoint("cam1", "layer2", "q3", 3, 30+20, 10+20);

    vmtModel->addObject3D("squirrel", "data/NewSquirrel.3DS");
/*
    vmtModel->addPositionEffect("ef1", "squirrel", ofxVec3f(0,3,0), ofxVec3f(0,-3,0), 0.5f);
    vmtModel->addPositionEffect("ef2", "squirrel", ofxVec3f(3,0,0), ofxVec3f(-3,0,0), 0.5f);
    vmtModel->addPositionEffect("ef3", "squirrel", ofxVec3f(0,0,3), ofxVec3f(0,0,-3), 0.5f);

    vmtModel->addFadeEffect("ef4", "group1", ofxVec4f(0,0,0,0), ofxVec4f(1,1,1,1), 0.5f);
*/
    //vmtModel->addTextureGroupEffect("ef5", "group1", "data/videos/cubo_azul.mov", VIDEO_TEXTURE);

    /*Lighting*/

    //each light will emit white reflexions
    //light1
    vmtModel->addLight("light1");
    vmtModel->setLightSpecular("light1", 100, 255, 255);

    float L1DirectionX = 1, L1DirectionY = 0, L1DirectionZ = 0;
    vmtModel->setLightDirectional("light1", 255, 0, 0, L1DirectionX, L1DirectionY, L1DirectionZ);

    //light2
    vmtModel->addLight("light2");
    vmtModel->setLightSpecular("light2", 255, 100, 255);

    float L2ConeAngle = 50, L2Concentration = 60;
    float L2PosX = 400, L2PosY = 400, L2PosZ = 800;
    float L2DirectionX = 0, L2DirectionY = 0, L2DirectionZ = -1;

    vmtModel->setLightSpot("light2", 0, 255, 0,
                     L2PosX, L2PosY, L2PosZ,
                     L2DirectionX, L2DirectionY, L2DirectionZ,
                     L2ConeAngle,
                     L2Concentration);

    //light3
    vmtModel->addLight("light3");
    vmtModel->setLightSpecular("light3", 255, 255, 100);

    float L3PosX = ofGetWidth(), L3PosY = 50, L3PosZ = 500;
    vmtModel->setLightPoint("light3", 0, 0, 255, L3PosX, L3PosY, L3PosZ);

    /* End Lighting */
/*
    vmtModel->addKeyEvent('a', "ef1");
    vmtModel->addKeyEvent('s', "ef2");

    vmtModel->scheduleEvent(1.0f, "ef1");
    vmtModel->scheduleEvent(2.0f, "ef2");
    vmtModel->scheduleEvent(3.0f, "ef3");
*/
    /*vmtModel->scheduleEvent(11.0f, "ef1");
    vmtModel->scheduleEvent(1.0f, "ef4");
    vmtModel->scheduleEvent(2.0f, "ef4");
    vmtModel->scheduleEvent(3.0f, "ef4");
    vmtModel->scheduleEvent(4.0f, "ef4");
    vmtModel->scheduleEvent(5.0f, "ef4");
    vmtModel->scheduleEvent(6.0f, "ef4");
    vmtModel->scheduleEvent(7.0f, "ef4");
    vmtModel->scheduleEvent(8.0f, "ef4");
    vmtModel->scheduleEvent(9.0f, "ef4");*/

    //vmtModel->startTimeManager(LOOP);

    vmtModel->saveShow("showXXX.xml");

    treeWindow = new TreeWindow(this->vmtModel);
    treeWindow->show();

    effectsWindow = new EffectsListWindow(this->vmtModel);
    effectsWindow->show();

    evteffectsWind = new evtEffectsListWindow(this->vmtModel);
    evteffectsWind->show();

}

//--------------------------------------------------------------
void Vmt::update(){
    this->vmtModel->update();
}

//--------------------------------------------------------------
void Vmt::draw(){
    //Draw scene
    this->vmtModel->draw();
}

//--------------------------------------------------------------

void Vmt::keyPressed(int key){

    if (vmtModel->hasKeyEvent(key)) {
        vmtModel->testEffect(vmtModel->getEffectIdForKeyEvent(key));
    }

    if(key == '0')
        vmtModel->resetScene();

    if(key == '1')
        vmtModel->activateCamera("cam1");

    if(key == '2')
        vmtModel->activateCamera("cam2");
}

//--------------------------------------------------------------
void Vmt::keyReleased(int key){
}

//--------------------------------------------------------------
void Vmt::mouseMoved(int x, int y ){
}

int xMouseDown, yMouseDown;



//--------------------------------------------------------------
void Vmt::mouseDragged(int x, int y, int button){
    int dx = x - xMouseDown;
    int dy = y - yMouseDown;

    xMouseDown = x;
    yMouseDown = y;

    switch(vmtModel->getControlMode()) {
        case ORBIT_MODE:
            vmtModel->OrbitActiveCamera(dx,dy);
            break;
        case ROLL_MODE:
            vmtModel->RollActiveCamera(dx);
            break;
        case DOLLY_MODE:
            vmtModel->DollyActiveCamera(dy);
            break;
        case PAN_MODE:
            vmtModel->PanActiveCamera(dx, dy);
            break;
    }

}

//--------------------------------------------------------------
void Vmt::mousePressed(int x, int y, int button){
    xMouseDown = x;
    yMouseDown = y;
}

//--------------------------------------------------------------
void Vmt::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
