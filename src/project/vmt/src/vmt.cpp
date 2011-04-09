#include "Quad2D.h"
#include "Object3D.h"
#include "vmt.h"
#include <map>
//--------------------------------------------------------------

vmt::vmt() : ofBaseApp() {
}

void vmt::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE);

    //for smooth animation, set vertical sync if we can
	ofSetVerticalSync(true);
	// also, frame rate:
	ofSetFrameRate(60);

	ofSetVerticalSync(true);
	glEnable(GL_DEPTH_TEST); //lights look weird if depth test is not enabled

    scene->setBackground(150, 250, 250);

    scene = new Scene();
    ofxCamera* cam1 = scene->addCamera("cam1");
    cam1->setOrigin(OF_ORIGIN_ZERO);
	//cam1->position(ofGetWidth()/2, ofGetHeight()/2, 300); //initialize the camera at a far position from the sphere
	cam1->position(0, 0, 0); //initialize the camera at a far position from the sphere
	cam1->eye(1, 0, 0);

    scene->addCamera("cam2");
    ofxCamera* cam2 = scene->getCamera("cam2");
    cam2->setOrigin(OF_ORIGIN_ZERO);
	//cam2->position(ofGetWidth()/2, ofGetHeight()/2, -300); //initialize the camera at a far position from the sphere
	cam2->position(0, 0, -30); //initialize the camera at a far position from the sphere
	cam2->eye(0, 0, 0);

    scene->activateCamera("cam2");

    Layer2D* layer1 = cam1->addLayer2D("layer1");
    Quad2D* quad1 = layer1->addQuad2D("q1");
    quad1->setEnabled(true);
    Quad2D* quad2 = layer1->addQuad2D("q2");
    quad2->setPoint(0, 10, 10);
    quad2->setPoint(1, 10, 20);
    quad2->setPoint(2, 30, 20);
    quad2->setPoint(3, 30, 10);
    quad2->setEnabled(true);

    Layer2D* layer2 = cam1->addLayer2D("layer2");
    Quad2D* quad3 = layer2->addQuad2D("q3");
    quad3->setEnabled(true);
    quad3->setPoint(0, 10+20, 10+20);
    quad3->setPoint(1, 10+20, 20+20);
    quad3->setPoint(2, 30+20, 20+20);
    quad3->setPoint(3, 30+20, 10+20);
    quad3->setEnabled(true);

    scene->addObject3D("squirrel", "data/NewSquirrel.3ds");

    /*Lighting*/

    //each light will emit white reflexions
    //light1
    ofxLight* light1 = scene->addLight("light1");
    light1->specular(100, 255, 255);

    float L1DirectionX = 1, L1DirectionY = 0, L1DirectionZ = 0;
    light1->directionalLight(255, 0, 0, L1DirectionX, L1DirectionY, L1DirectionZ);

    //light2
    ofxLight* light2 = scene->addLight("light2");
    light2->specular(255, 100, 255);

    float L2ConeAngle = 50, L2Concentration = 60;
    float L2PosX = 400, L2PosY = 400, L2PosZ = 800;
    float L2DirectionX = 0, L2DirectionY = 0, L2DirectionZ = -1;

    light2->spotLight(0, 255, 0,
                     L2PosX, L2PosY, L2PosZ,
                     L2DirectionX, L2DirectionY, L2DirectionZ,
                     L2ConeAngle,
                     L2Concentration);

    //light3
    ofxLight* light3 = scene->addLight("light3");
    light3->specular(255, 255, 100);

    float L3PosX = ofGetWidth(), L3PosY = 50, L3PosZ = 500;
    light3->pointLight(0, 0, 255, L3PosX, L3PosY, L3PosZ);

    /* End Lighting */

    treeWindow = new TreeWindow(this->scene);
    treeWindow->show();

}

//--------------------------------------------------------------
void vmt::update(){
	//camera.lerpPosition(centerX, centerY, 500, 0.05); //interpolate the camera into a closer position
}

//--------------------------------------------------------------
void vmt::draw(){
    //Draw scene
    scene->draw();
}

//--------------------------------------------------------------

int activeCamera = 0;

void vmt::keyPressed(int key){

    if(activeCamera == 0) {
        scene->activateCamera("cam1");
        activeCamera = 1;
    }
    else {
        scene->activateCamera("cam2");
        activeCamera = 0;
    }
}

//--------------------------------------------------------------
void vmt::keyReleased(int key){
}

//--------------------------------------------------------------
void vmt::mouseMoved(int x, int y ){
}

int xMouseDown, yMouseDown;

//--------------------------------------------------------------
void vmt::mouseDragged(int x, int y, int button){
    int dx = x - xMouseDown;
    int dy = y - yMouseDown;

    ofxCamera *cam = scene->getActiveCamera();

    ofxVec3f dir = -(cam->getDir());

    float rotScale = 0.3f;

    dir.rotate(dx * rotScale, ofxVec3f(0,-1,0));

    ofxVec3f axis2 = dir.getCrossed(ofxVec3f(0,1,0));
    axis2.normalize();

    dir.rotate(dy * rotScale, axis2);

    ofxVec3f eye = cam->getEye();

    cam->position(eye + dir);

    xMouseDown = x;
    yMouseDown = y;
}

//--------------------------------------------------------------
void vmt::mousePressed(int x, int y, int button){
    xMouseDown = x;
    yMouseDown = y;
}

//--------------------------------------------------------------
void vmt::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
