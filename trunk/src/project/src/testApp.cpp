#include "testApp.h"
#include "AnimationController.h"
#include "Animation.h"
#include "LinearAnimation.h"
#include "Background.h"
#include "VideoController.h"
#include "DrawEventArg.h"
#include "ofxXmlSettings.h"
#include <vector>
#include <map>
using namespace std;

AnimationController animController;
VideoController videoController;
ofxXmlSettings quadsXML;
Background *background;

map<string, Quad2D*> quads;
map<string, Quad2D*>::iterator quadsIt;

map<string, Material*> materials;

string selectedQuadKey;
int selectedIdx = -1;
int selectedVtx = 0;
float xoffset = 5;
float yoffset = 5;

Object3D *obj3D;

//--------------------------------------------------------------
void testApp::setup(){

    setupLogging();

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
    //videoController.AddVideo("video1", "fingers.mov");
    //videoController.PlayVideo("video1");

    //videoController.AddVideo("video2", "cartoon.mov");
    //videoController.PlayVideo("video2");

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

    #ifndef CONSOLE
        this->synchManager = new SynchManager(false); //set as receiver
        this->synchManager->addListener(this, "/all");
        //this->synchManager->addListener(&animController, "/anim");
        this->midiManager = new MidiManager(); //midi  receiver
        this->midiManager->addListener(this, "");
    #else
        this->synchManager = new SynchManager(true); //set as sender
    #endif

    quads.insert(pair<string, Quad2D*>("quad1", new Quad2D("quad1", 100,100, 250,80, 270,260, 80,250))) ;
    materials.insert(pair<string, Material*>("mat1", new Material()));

    //TextureManager::LoadImageTexture("pegado", "pegado.jpg");
    TextureManager::LoadVideoTexture("pegado", "cartoon.mov");
    //materials["mat1"]->SetTextureParams("pegado", imageTexture);
    materials["mat1"]->SetTextureParams("pegado", videoTexture);

    quads["quad1"]->setMaterial(materials["mat1"]);

    LinearAnimation *anim5 = new LinearAnimation(materials["mat1"], AMBIENT_R, 2, 1.0);
    LinearAnimation *anim6 = new LinearAnimation(materials["mat1"], AMBIENT_R, 2, 0.0);

    AnimationLoop *loop1 = new AnimationLoop("loop1");
    loop1->AddAnimation(anim5);
    loop1->AddAnimation(anim6);

    animController.AddLoop("loop1", loop1);
}

//--------------------------------------------------------------
void testApp::update(){
    animController.Update(ofGetLastFrameTime());

    #ifndef CONSOLE
        synchManager->checkForMessages();
    #endif

    //#ifndef CONSOLE
    TextureManager::Update();
    //#endif
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetupScreen();
    //obj3D->draw();

    for(quadsIt = quads.begin(); quadsIt != quads.end(); ++quadsIt)
    {
        (*quadsIt).second->draw();
    }
}


//--------------------------------------------------------------

void cycleQuadSelection(bool fwd) {
    if(quads.size() > 0) {
        int oldSelectedIdx = selectedIdx;
        if(fwd) {
            ++selectedIdx;
        }
        else {
            --selectedIdx;
        }
        selectedIdx %= quads.size();

        quadsIt = quads.begin();
        std::advance(quadsIt, oldSelectedIdx);
        (*quadsIt).second->setSelected(false);
        quadsIt = quads.begin();
        std::advance(quadsIt, selectedIdx);
        selectedQuadKey = (*quadsIt).first;
        (*quadsIt).second->setSelected(true);
    }
}

void testApp::keyPressed  (int key){
    #ifdef CONSOLE

    if(key == 'h') {
        quads["quad1"]->setEnabled(true);
    }
    if(key == 'g') {
        animController.PlayLoop("loop1");
    }
    if(key == 'k') {
        loadQuads();
    }
    if(key == '1') {
        cycleQuadSelection(true);
    }
    if(key == '2') {
        cycleQuadSelection(false);
    }
    if(key == '3') {
        ++selectedVtx;
        selectedVtx %= 4;
    }
    if(key == '4') {
        ++selectedVtx;
        selectedVtx %= 4;
    }

    if(key == 'a') {
        if(!selectedQuadKey.empty()) {
            float x, y;
            quads[selectedQuadKey]->getPoint(selectedVtx, x, y);
            x -= xoffset;
            setPoint(selectedIdx, selectedVtx, x, y);
        }
    }
    if(key == 'd') {
        if(!selectedQuadKey.empty()) {
            float x, y;
            quads[selectedQuadKey]->getPoint(selectedVtx, x, y);
            x += xoffset;
            setPoint(selectedIdx, selectedVtx, x, y);
        }
    }
    if(key == 's') {
        if(!selectedQuadKey.empty()) {
            float x, y;
            quads[selectedQuadKey]->getPoint(selectedVtx, x, y);
            y += yoffset;
            setPoint(selectedIdx, selectedVtx, x, y);
        }
    }
    if(key == 'w') {
        if(!selectedQuadKey.empty()) {
            float x, y;
            quads[selectedQuadKey]->getPoint(selectedVtx, x, y);
            y -= yoffset;
            setPoint(selectedIdx, selectedVtx, x, y);
        }
    }
    if(key == ' ') {
        selectedIdx = addQuad(selectedIdx);
    }
    if(key == '\b') {
        if(quads.size() > 0 && selectedIdx >= 0) {
            quadsIt = quads.begin();
            std::advance(quadsIt, selectedIdx);
            (*quadsIt).second->setSelected(false);
            quads.erase(quadsIt);
            selectedQuadKey = "";
        }
    }
    if(key == 'l') {
        saveQuads();
    }

    #endif
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    #ifdef CONSOLE
    ofLog(OF_LOG_VERBOSE, "mouseDragged: x=%d, y=%d", x, y);

    if(selectedIdx >= 0 && selectedVtx >= 0)
    {
        ofLog(OF_LOG_VERBOSE, "mouseDragged: ===== selectedIds=%d, selectedVtx=%d", selectedIdx,selectedVtx);
        setPoint(selectedIdx, selectedVtx, x, y);
    }
    #endif
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    #ifdef CONSOLE

    if(!selectedQuadKey.empty()) {
        selectedVtx = quads[selectedQuadKey]->getControlPointAt(x,y);
    }

    #endif
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

void testApp::event(EventArg *e) {
    ofLog(OF_LOG_NOTICE, "=========EN ENENT EN TESTAPP!!!!!\n");
    DrawEventArg *evtArg = (DrawEventArg*) e;
    if (evtArg->_evtType == 0) //setpoint
    {
        setPoint(evtArg->_shapeId, evtArg->_vertexId, evtArg->_x, evtArg->_y, false);
    } else if (evtArg->_evtType == 1) //draw new quad
    {
        selectedIdx = addQuad(evtArg->_shapeId, false);
    }

}

void testApp::setupLogging() {
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofLog(OF_LOG_VERBOSE, "seteando logs");
}

void testApp::setPoint(int selectedIdx, int selectedVtx, int x, int y, bool sendEvent) {
    quadsIt = quads.begin();
    std::advance(quadsIt, selectedIdx);
    (*quadsIt).second->setPoint(selectedVtx, x, y);

    if (sendEvent)
    {
        ofxOscMessage oscMessage;
        oscMessage.addIntArg(selectedIdx);
        oscMessage.addIntArg(selectedVtx);
        oscMessage.addIntArg(x);
        oscMessage.addIntArg(y);
        this->synchManager->SendMessage(oscMessage, SETPOINT);
    }
}

int testApp::addQuad(int selIdx, bool sendEvent) {
    quads.insert(pair<string, Quad2D*>("quadX", new Quad2D("quadX"))) ;

    if(selIdx >= 0) {
        quadsIt = quads.begin();
        std::advance(quadsIt, selIdx);
        (*quadsIt).second->setSelected(false);
    }

    if (sendEvent) {
        ofxOscMessage oscMessage;
        oscMessage.addIntArg(selIdx);
        this->synchManager->SendMessage(oscMessage, ADDQUAD);
    }

    selIdx = quads.size() - 1;

    quadsIt = quads.begin();
    std::advance(quadsIt, selIdx);
    selectedQuadKey = (*quadsIt).first;
    (*quadsIt).second->setSelected(true);

    return selIdx;
}

void testApp::loadQuads() {
    ofLog(OF_LOG_NOTICE, "loading project...");

    quadsXML.loadFile("./quads.xml");

    quadsXML.pushTag("quads");

    int numQuadItems = quadsXML.getNumTags("quadItem");

    for(int i = 0; i < numQuadItems; i++)
    {
        selectedIdx = addQuad(selectedIdx);

        quadsXML.pushTag("quadItem", i);

            double x0 = quadsXML.getAttribute("vx0", "x", 0.0, 0);
            double y0 = quadsXML.getAttribute("vx0", "y", 0.0, 0);

            double x1 = quadsXML.getAttribute("vx1", "x", 50.0, 0);
            double y1 = quadsXML.getAttribute("vx1", "y", 0.0, 0);

            double x2 = quadsXML.getAttribute("vx2", "x", 50.0, 0);
            double y2 = quadsXML.getAttribute("vx2", "y", 50.0, 0);

            double x3 = quadsXML.getAttribute("vx3", "x", 0.0, 0);
            double y3 = quadsXML.getAttribute("vx3", "y", 50.0, 0);

            setPoint(selectedIdx, 0, x0, y0);
            setPoint(selectedIdx, 1, x1, y1);
            setPoint(selectedIdx, 2, x2, y2);
            setPoint(selectedIdx, 3, x3, y3);

        quadsXML.popTag();
    }

    quadsXML.popTag();

    ofLog(OF_LOG_NOTICE, "project loaded. loaded quads: %i", numQuadItems);
}

void testApp::saveQuads() {
    ofLog(OF_LOG_NOTICE, "saving project...");
    quadsXML.clear();
    int quadsTagKey = quadsXML.addTag("quads");
    quadsXML.pushTag("quads", quadsTagKey);

    for(quadsIt = quads.begin(); quadsIt != quads.end(); ++quadsIt)
    {
        int quadItemTagKey = quadsXML.addTag("quadItem");
        quadsXML.pushTag("quadItem", quadItemTagKey);

        float x0, y0, x1, y1, x2, y2, x3, y3;
        (*quadsIt).second->getPoint(0, x0, y0);
        (*quadsIt).second->getPoint(1, x1, y1);
        (*quadsIt).second->getPoint(2, x2, y2);
        (*quadsIt).second->getPoint(3, x3, y3);

        int quadVx0Key = quadsXML.addTag("vx0");
        quadsXML.addAttribute("vx0", "x", x0, quadVx0Key);
        quadsXML.addAttribute("vx0", "y", y0, quadVx0Key);

        int quadVx1Key = quadsXML.addTag("vx1");
        quadsXML.addAttribute("vx1", "x", x1, quadVx1Key);
        quadsXML.addAttribute("vx1", "y", y1, quadVx1Key);

        int quadVx2Key = quadsXML.addTag("vx2");
        quadsXML.addAttribute("vx2", "x", x2, quadVx2Key);
        quadsXML.addAttribute("vx2", "y", y2, quadVx2Key);

        int quadVx3Key = quadsXML.addTag("vx3");
        quadsXML.addAttribute("vx3", "x", x3, quadVx3Key);
        quadsXML.addAttribute("vx3", "y", y3, quadVx3Key);

        quadsXML.popTag();
    }
    quadsXML.popTag();
    quadsXML.saveFile("./quads.xml");

    ofLog(OF_LOG_NOTICE, "Project saved.");

}
