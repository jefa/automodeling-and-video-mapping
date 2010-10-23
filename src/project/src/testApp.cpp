#include "testApp.h"
#include "AnimationController.h"
#include "Animation.h"
#include "LinearAnimation.h"
#include "Background.h"

AnimationController animController;
Background *background;
//--------------------------------------------------------------
void testApp::setup(){

	//set background to black
	ofBackground(0, 0, 0);

	//for smooth animation, set vertical sync if we can
	ofSetVerticalSync(true);
	// also, frame rate:
	ofSetFrameRate(60);

    obj3D = new Object3D();
    //obj3D->addObject("squirrel/NewSquirrel.3ds");
    obj3D->addObject("sphere/sphere.3ds");

    background = new Background();

    LinearAnimation *anim1 = new LinearAnimation(obj3D, POS_X, 5, 600);
    LinearAnimation *anim2 = new LinearAnimation(obj3D, POS_Y, 4, 700);
    //LinearAnimation *anim3 = new LinearAnimation(background, COLOR_R, 3, 255);
    //LinearAnimation *anim4 = new LinearAnimation(background, COLOR_G, 3, 128);
    anim1->Start();
    anim2->Start();

    animController.AddAnimation(anim1, IMMEDIATE);
    animController.AddAnimation(anim2, IMMEDIATE);
    //animController.AddAnimation(anim3, IMMEDIATE);
    //animController.AddAnimation(anim4, IMMEDIATE);


}

//--------------------------------------------------------------
void testApp::update(){
    animController.Update(ofGetLastFrameTime());
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetupScreen();

    obj3D->draw();
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

