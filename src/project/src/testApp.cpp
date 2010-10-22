#include "testApp.h"
#include "AnimationController.h"
#include "Animation.h"
#include "LinearAnimation.h"
#include "AnimationsLinking.h"
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
    obj3D->addObject("squirrel/NewSquirrel.3ds");
    //obj3D->addObject("sphere/sphere.3ds");

    background = new Background();

    //Translation *t = new Translation(obj3D);
    //obj3D->addModifier(t);

    LinearAnimation *anim = new LinearAnimation(obj3D, "x", 5000, 200);
    LinearAnimation *anim2 = new LinearAnimation(obj3D, "y", 5000, 500);
    LinearAnimation *anim3 = new LinearAnimation(background, "color.r", 10000, 255);
    LinearAnimation *anim4 = new LinearAnimation(background, "color.g", 10000, 255);
    animController.AddAnimation(anim, IMMEDIATE);
    animController.AddAnimation(anim2, IMMEDIATE);
    animController.AddAnimation(anim3, IMMEDIATE);
    animController.AddAnimation(anim4, IMMEDIATE);

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

