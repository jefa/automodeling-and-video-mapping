#include "testApp.h"
#include "AnimationController.h"
#include "Animation.h"
#include "LinearAnimation.h"
#include "Background.h"
#include "Quad2D.h"
#include "VideoController.h"
#include <vector>
using namespace std;

AnimationController animController;
VideoController videoController;
Background *background;

vector<Quad2D*> quads;
vector<Material*> materials;

int selectedIdx = 0;
int selectedVtx = 0;
float xoffset = 5;
float yoffset = 5;

Object3D *obj3D;

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

    quads.push_back(new Quad2D(100,100, 250,80, 270,260, 80,250));
    quads.push_back(new Quad2D(500,500, 650,480, 670,660, 480,650));
}

//--------------------------------------------------------------
void testApp::update(){
    animController.Update(ofGetLastFrameTime());

    //#ifndef CONSOLE
    videoController.IdleMovies();
    //#endif
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetupScreen();
    //obj3D->draw();

    //#ifndef CONSOLE
    //videoController.bindTexture("video1");
    //#endif
    vector<Quad2D*>::iterator it;
    for(it = quads.begin(); it != quads.end(); ++it)
    {
        (*it)->draw();
    }


    //#ifndef CONSOLE
    //videoController.unbindTexture("video1");
    //#endif

    //#ifndef CONSOLE
    //videoController.bindTexture("video2");
    //#endif

    //#ifndef CONSOLE
    //videoController.unbindTexture("video2");
    //#endif
}


//--------------------------------------------------------------

void testApp::keyPressed  (int key){
    if(key == '1')
    {
        if(quads.size() > 0) {
            quads[selectedIdx]->setSelected(false);
            ++selectedIdx;
            selectedIdx %= quads.size();
            quads[selectedIdx]->setSelected(true);
        }
    }
    if(key == '2')
    {
        if(quads.size() > 0) {
            quads[selectedIdx]->setSelected(false);
            --selectedIdx;
            selectedIdx %= quads.size();
            quads[selectedIdx]->setSelected(true);
        }
    }

    if(key == '3')
    {
        ++selectedVtx;
        selectedVtx %= 4;
    }
    if(key == '4')
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

    if(key == ' ')
    {
        quads.push_back(new Quad2D());
        quads[selectedIdx]->setSelected(false);
        selectedIdx = quads.size() - 1;
        quads[selectedIdx]->setSelected(true);
    }
    if(key == '\b') {
        if(quads.size() > 0 && selectedIdx >= 0) {
            vector<Quad2D*>::iterator it = quads.begin();
            for(int i = 0; i < selectedIdx; i++)
                ++it;
            (*it)->setSelected(false);
            quads.erase(it);
        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    if(selectedIdx >= 0 && selectedVtx >= 0)
    {
        quads[selectedIdx]->setPoint(selectedVtx, x, y);
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    selectedVtx = quads[selectedIdx]->getControlPointAt(x,y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

