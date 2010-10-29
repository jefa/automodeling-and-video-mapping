#include "testApp.h"
#include "AnimationController.h"
#include "Animation.h"
#include "LinearAnimation.h"
#include "Background.h"
#include "VideoController.h"
#include "DrawEventArg.h"
#include "ofxXmlSettings.h"
#include <vector>
using namespace std;

AnimationController animController;
VideoController videoController;
ofxXmlSettings quadsXML;
Background *background;

vector<Quad2D*> quads;
vector<Material*> materials;

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

    quads.push_back(new Quad2D(100,100, 250,80, 270,260, 80,250));
    //quads.push_back(new Quad2D(500,500, 650,480, 670,660, 480,650));

}

//--------------------------------------------------------------
void testApp::update(){
    animController.Update(ofGetLastFrameTime());

    #ifndef CONSOLE
        synchManager->checkForMessages();
    #endif

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
    #ifdef CONSOLE

    if(key == 'k')
    {
        loadQuads();
    }

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
        //quads[selectedIdx]->setPoint(selectedVtx, x, y);
        setPoint(&quads, selectedIdx, selectedVtx, x, y);
    }
    if(key == 'd')
    {
        float x, y;
        quads[selectedIdx]->getPoint(selectedVtx, x, y);
        x += xoffset;
        //quads[selectedIdx]->setPoint(selectedVtx, x, y);
        setPoint(&quads, selectedIdx, selectedVtx, x, y);
    }
    if(key == 's')
    {
        float x, y;
        quads[selectedIdx]->getPoint(selectedVtx, x, y);
        y += yoffset;
        //quads[selectedIdx]->setPoint(selectedVtx, x, y);
        setPoint(&quads, selectedIdx, selectedVtx, x, y);
    }
    if(key == 'w')
    {
        float x, y;
        quads[selectedIdx]->getPoint(selectedVtx, x, y);
        y -= yoffset;
        //quads[selectedIdx]->setPoint(selectedVtx, x, y);
        setPoint(&quads, selectedIdx, selectedVtx, x, y);
    }

    if(key == ' ')
    {
        /*quads.push_back(new Quad2D());
        quads[selectedIdx]->setSelected(false);
        selectedIdx = quads.size() - 1;
        quads[selectedIdx]->setSelected(true);*/
        selectedIdx = addQuad(&quads, selectedIdx);
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
        setPoint(&quads, selectedIdx, selectedVtx, x, y);
    }
    #endif
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    #ifdef CONSOLE

    if(selectedIdx >= 0)
        selectedVtx = quads[selectedIdx]->getControlPointAt(x,y);

    #endif
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

void testApp::event(EventArg *e)
{
    ofLog(OF_LOG_NOTICE, "=========EN ENENT EN TESTAPP!!!!!\n");
    DrawEventArg *evtArg = (DrawEventArg*) e;
    if (evtArg->_evtType == 0) //setpoint
    {
        //quads[evtArg->_shapeId]->setPoint(evtArg->_vertexId, evtArg->_x, evtArg->_y);
        setPoint(&quads, evtArg->_shapeId, evtArg->_vertexId, evtArg->_x, evtArg->_y, false);
    } else if (evtArg->_evtType == 1) //draw new quad
    {
        selectedIdx = addQuad(&quads, evtArg->_shapeId, false);
    }

}

void testApp::setupLogging(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofLog(OF_LOG_VERBOSE, "seteando logs");
}

int testApp::setPoint(vector<Quad2D*> *shapes, int selectedIdx, int selectedVtx,
                      int x, int y, bool sendEvent)
{
    shapes->at(selectedIdx)->setPoint(selectedVtx, x, y);

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

int testApp::addQuad(vector<Quad2D*> *shapes, int selIdx, bool sendEvent)
{
    shapes->push_back(new Quad2D());
    if(selIdx >= 0)
        shapes->at(selIdx)->setSelected(false);

    if (sendEvent)
    {
        ofxOscMessage oscMessage;
        oscMessage.addIntArg(selIdx);
        this->synchManager->SendMessage(oscMessage, ADDQUAD);
    }

    selIdx = shapes->size() - 1;
    shapes->at(selIdx)->setSelected(true);

    return selIdx;
}

void testApp::loadQuads()
{
    ofLog(OF_LOG_NOTICE, "loading project...");

    quadsXML.loadFile("./quads.xml");

    quadsXML.pushTag("quads");

    int numQuadItems = quadsXML.getNumTags("quadItem");

    for(int i = 0; i < numQuadItems; i++)
    {
        selectedIdx = addQuad(&quads, selectedIdx);

        quadsXML.pushTag("quadItem", i);

            double x0 = quadsXML.getAttribute("vx0", "x", 0.0, 0);
            double y0 = quadsXML.getAttribute("vx0", "y", 0.0, 0);

            double x1 = quadsXML.getAttribute("vx1", "x", 50.0, 0);
            double y1 = quadsXML.getAttribute("vx1", "y", 0.0, 0);

            double x2 = quadsXML.getAttribute("vx2", "x", 50.0, 0);
            double y2 = quadsXML.getAttribute("vx2", "y", 50.0, 0);

            double x3 = quadsXML.getAttribute("vx3", "x", 0.0, 0);
            double y3 = quadsXML.getAttribute("vx3", "y", 50.0, 0);

            setPoint(&quads, selectedIdx, 0, x0, y0);
            setPoint(&quads, selectedIdx, 1, x1, y1);
            setPoint(&quads, selectedIdx, 2, x2, y2);
            setPoint(&quads, selectedIdx, 3, x3, y3);

        quadsXML.popTag();
    }

    quadsXML.popTag();

    ofLog(OF_LOG_NOTICE, "project loaded. loaded quads: %i", numQuadItems);
}

void testApp::saveQuads()
{
    ofLog(OF_LOG_NOTICE, "saving project...");
    quadsXML.clear();
    int quadsTagKey = quadsXML.addTag("quads");
    quadsXML.pushTag("quads", quadsTagKey);

    vector<Quad2D*>::iterator it;
    for(it = quads.begin(); it != quads.end(); ++it)
    {
        int quadItemTagKey = quadsXML.addTag("quadItem");
        quadsXML.pushTag("quadItem", quadItemTagKey);

        float x0, y0, x1, y1, x2, y2, x3, y3;
        (*it)->getPoint(0, x0, y0);
        (*it)->getPoint(1, x1, y1);
        (*it)->getPoint(2, x2, y2);
        (*it)->getPoint(3, x3, y3);

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
