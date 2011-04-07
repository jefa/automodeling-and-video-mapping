#include "Quad2D.h"
#include "vmt.h"
#include <map>
//--------------------------------------------------------------

vmt::vmt() : ofBaseApp() {
}

void vmt::setup(){

    //for smooth animation, set vertical sync if we can
	ofSetVerticalSync(true);
	// also, frame rate:
	ofSetFrameRate(60);

	ofSetVerticalSync(true);
	glEnable(GL_DEPTH_TEST); //lights look weird if depth test is not enabled

    scene->setBackground(150, 250, 250);

    scene = new Scene();
    scene->addCamera("cam1");
    ofxCamera* cam1 = scene->activateCamera("cam1");
    cam1->setOrigin(OF_ORIGIN_ZERO);
	cam1->position(ofGetWidth()/2, ofGetHeight()/2, 500); //initialize the camera at a far position from the sphere

    scene->addCamera("cam2");
    ofxCamera* cam2 = scene->getCamera("cam2");
    cam2->setOrigin(OF_ORIGIN_ZERO);
	cam2->position(ofGetWidth()/8, ofGetHeight()/8, 700); //initialize the camera at a far position from the sphere

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

int keypressed = 0;

void vmt::keyPressed  (int key){

    keypressed++;

    if(keypressed == 1) {
        //each light will emit white reflexions
        ofxLight* light1 = scene->addLight("light1");
        light1->specular(100, 255, 255);

        //light1
        float L1DirectionX = 1;
        float L1DirectionY = 0;
        float L1DirectionZ = 0;

        light1->directionalLight(255, 0, 0, L1DirectionX, L1DirectionY, L1DirectionZ);
    }
    else if(keypressed == 2) {
        ofxLight* light2 = scene->addLight("light2");
        light2->specular(255, 100, 255);

        //light2
        float L2ConeAngle = 50;
        float L2Concentration = 60;
        float L2PosX = 400;
        float L2PosY = 400;
        float L2PosZ = 800;
        float L2DirectionX = 0;
        float L2DirectionY = 0;
        float L2DirectionZ = -1;

        light2->spotLight(0, 255, 0,
                         L2PosX, L2PosY, L2PosZ,
                         L2DirectionX, L2DirectionY, L2DirectionZ,
                         L2ConeAngle,
                         L2Concentration);
    }
    else if(keypressed == 3) {
        ofxLight* light3 = scene->addLight("light3");
        light3->specular(255, 255, 100);

        //light3
        float L3PosX = ofGetWidth();
        float L3PosY = 50;
        float L3PosZ = 500;
        light3->pointLight(0, 0, 255, L3PosX, L3PosY, L3PosZ);
    }
    else if (keypressed == 4) {

        ofxLight* light1 = scene->getLight("light1");
        ofxLight* light2 = scene->getLight("light2");
        ofxLight* light3 = scene->getLight("light3");

        light1->off();
        light2->off();
        light3->off();
    }

}

//--------------------------------------------------------------
void vmt::keyReleased(int key){
}

//--------------------------------------------------------------
void vmt::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void vmt::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void vmt::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void vmt::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
