#include "testApp.h"
#include "AnimationController.h"
#include "Animation.h"
#include "LinearAnimation.h"
#include "Background.h"
#include "Quad2D.h"
#include "VideoController.h"

AnimationController animController;
VideoController videoController;
Background *background;

Quad2D* quads[2];

int selectedIdx = -1;
int selectedVtx = 0;
float xoffset = 5;
float yoffset = 5;

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

    videoController.AddVideo("video1", "fingers.mov");
    videoController.PlayVideo("video1");

    videoController.AddVideo("video2", "cartoon.mov");
    videoController.PlayVideo("video2");

    //LinearAnimation *anim1 = new LinearAnimation(obj3D, POS_X, 5, 600);
    //LinearAnimation *anim2 = new LinearAnimation(obj3D, POS_Y, 4, 700);
    //LinearAnimation *anim3 = new LinearAnimation(background, COLOR_R, 3, 255);
    //LinearAnimation *anim4 = new LinearAnimation(background, COLOR_G, 3, 128);
    //anim1->Start();
    //anim2->Start();

    //animController.AddAnimation(anim1, IMMEDIATE);
    //animController.AddAnimation(anim2, IMMEDIATE);
    //animController.AddAnimation(anim3, IMMEDIATE);
    //animController.AddAnimation(anim4, IMMEDIATE);

    quads[0] = new Quad2D(100,100, 250,80, 270,260, 80,250);
    quads[1] = new Quad2D(600,600, 750,580, 770,760, 580,750);

}

//--------------------------------------------------------------
void testApp::update(){
    #ifndef CONSOLE
    animController.Update(ofGetLastFrameTime());
    videoController.IdleMovies();
    #endif
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetupScreen();
    //obj3D->draw();

    #ifndef CONSOLE
    videoController.bindTexture("video1");
    #endif

    quads[0]->draw();

    #ifndef CONSOLE
    videoController.unbindTexture("video1");
    #endif

    #ifndef CONSOLE
    videoController.bindTexture("video2");
    #endif

    quads[1]->draw();

    #ifndef CONSOLE
    videoController.unbindTexture("video2");
    #endif
}


//--------------------------------------------------------------

/*
void testApp::keyPressed  (int key){
    if(key == '1')
    {
        ++selectedIdx;
        selectedIdx %= 2;
    }
    if(key == '2')
    {
        ++selectedVtx;
        selectedVtx %= 4;
    }

    if(key == 'a')
    {
        float x, y;
        quads[selectedIdx]->getPoint(selectedVtx, x, y);
        x -= xoffset;
        quads[selectedIdx]->setPoint(selectedVtx, x, y);
    }
    if(key == 'd')
    {
        float x, y;
        quads[selectedIdx]->getPoint(selectedVtx, x, y);
        x += xoffset;
        quads[selectedIdx]->setPoint(selectedVtx, x, y);
    }
    if(key == 's')
    {
        float x, y;
        quads[selectedIdx]->getPoint(selectedVtx, x, y);
        y += yoffset;
        quads[selectedIdx]->setPoint(selectedVtx, x, y);
    }
    if(key == 'w')
    {
        float x, y;
        quads[selectedIdx]->getPoint(selectedVtx, x, y);
        y -= yoffset;
        quads[selectedIdx]->setPoint(selectedVtx, x, y);
    }
}
*/

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
    if(selectedIdx >= 0)
    {
        quads[selectedIdx]->setPoint(selectedVtx, x, y);
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    for(int i = 0; i < 2; i++)
    {
        int cp = quads[i]->getControlPointAt(x,y);
        if(cp >= 0)
        {
            selectedIdx = i;
            selectedVtx = cp;
            break;
        }
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    selectedIdx = -1;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

