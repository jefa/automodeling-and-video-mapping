#include "testApp.h"
#include "AnimationController.h"
#include "Animation.h"
#include "LinearAnimation.h"
#include "AnimationsLinking.h"

AnimationController animController;

//--------------------------------------------------------------
void testApp::setup(){

	//set background to black
	ofBackground(0, 0, 0);

	//for smooth animation, set vertical sync if we can
	ofSetVerticalSync(true);
	// also, frame rate:
	ofSetFrameRate(60);


    obj3D = new Object3D();
    obj3D->addObject("squirrel/NewSquirrel.3ds");

    //Translation *t = new Translation(obj3D);
    //obj3D->addModifier(t);

    LinearAnimation *anim = new LinearAnimation(obj3D, "x", 5000, 200);
    animController.AddAnimation(anim, IMMEDIATE);

}

//--------------------------------------------------------------
void testApp::update(){
    animController.Update(60);
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

