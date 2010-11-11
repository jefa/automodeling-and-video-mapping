#include "testApp.h"
#include "AnimationController.h"
#include "Animation.h"
#include "LinearAnimation.h"
#include "Background.h"
#include "TimeManager.h"
#include "ofxXmlSettings.h"
#include <map>

ofxXmlSettings quadsXML;
ofxXmlSettings showConfig;

map<string, Quad2D*> quads;
map<string, Quad2D*>::iterator quadsIt;
multimap<float, Quad2D*> quadsByZ;

map<string, vector<Quad2D*> > quadGroups;

map<string, Material*> materials;

string selectedQuadKey;
int selectedIdx = 0;
int selectedVtx = 0;
float xoffset = 1;
float yoffset = 1;
bool consoleEnabled = false;
bool bFullscreen = false;

map<string, int> OscPorts;

map<string, string > MidiPorts;

map<string, Node > Network;


//--------------------------------------------------------------

testApp::testApp(string nodeName) : ofBaseApp() {
    this->nodeName = nodeName;
}

void testApp::setup(){

    setupLogging();

    //set background to black
	ofBackground(0, 0, 0);
    ofSetFullscreen(bFullscreen);

    //for smooth animation, set vertical sync if we can
	ofSetVerticalSync(true);
	// also, frame rate:
	ofSetFrameRate(60);

    //load showconfig from xml
	loadShow();

    #ifdef CONSOLE
        ofSetWindowTitle("Console APP");
    #else
        ofSetWindowTitle("Client APP");
    #endif

    #ifndef CONSOLE
        OscManager::Init(nodeName, Network, OscPorts, false); //set as sender
        OscManager::AddListener(this, "/all");
    #else
        OscManager::Init(nodeName, Network, OscPorts); //set as sender
    #endif

    /*LinearAnimation *anim5 = new LinearAnimation(materials["mat1"], AMBIENT_R, 2, 1.0);
    LinearAnimation *anim6 = new LinearAnimation(materials["mat1"], AMBIENT_R, 2, 0.0);

    AnimationLoop *loop1 = new AnimationLoop("loop1");
    loop1->AddAnimation(anim5);
    loop1->AddAnimation(anim6);

    animController.AddLoop("loop1", loop1);*/

    #ifdef CONSOLE

    std::cout << " ofSoundPlayer ";

    mySound.loadSound("sounds/export_mapping.mp3");
    mySound.setMultiPlay(false);
    mySound.setVolume(1.0f);

    TimeManager::Init(this);
    setupConsole();

    #endif

}

//--------------------------------------------------------------
void testApp::update(){
    AnimationController::Update();

    #ifndef CONSOLE
        OscManager::Update();    //Check for messages
    #else
        TimeManager::Update();
    #endif

    TextureManager::Update();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetupScreen();

    multimap<float, Quad2D*>::iterator it;
    for(it = quadsByZ.begin(); it != quadsByZ.end(); it++) {
        it->second->draw();
    }

    #ifdef CONSOLE
        console->render();
    #endif
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

        if (oldSelectedIdx < quads.size()){
            quadsIt = quads.begin();
            std::advance(quadsIt, oldSelectedIdx);
            (*quadsIt).second->setSelected(false);
        } else {
            ofLog(OF_LOG_WARNING, "testApp: cycleQuadSelection: oldSelectedIndex=%d is invalid for quads.size=%d. Probably was removed...", oldSelectedIdx, quads.size());
        }
        quadsIt = quads.begin();
        std::advance(quadsIt, selectedIdx);
        selectedQuadKey = (*quadsIt).first;
        (*quadsIt).second->setSelected(true);

        ofLog(OF_LOG_VERBOSE, selectedQuadKey.c_str());
    }
}

void testApp::keyPressed  (int key){

    if(key == 'f'){
		bFullscreen = !bFullscreen;
        ofSetFullscreen(bFullscreen);
	}

#ifdef CONSOLE

    if(key == '+') {
        consoleEnabled = !consoleEnabled;
        ofLog(OF_LOG_NOTICE, "CONSOLE ENABLED = %d", consoleEnabled);
    }
    if (consoleEnabled)
        return;

    if(key == 't') {
        addQuad();
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
    if(key == '9') {
        ofxOscMessage oscMessage;
        oscMessage.setAddress("/texture/setcolor");
        oscMessage.addStringArg(selectedQuadKey);
        oscMessage.addFloatArg(1.0f);
        oscMessage.addFloatArg(1.0f);
        oscMessage.addFloatArg(0.0f);
        oscMessage.addFloatArg(1.0f);
        OscManager::SendMessage(oscMessage);
    }
    if(key == '0') {
        ofxOscMessage oscMessage;
        oscMessage.setAddress("/texture/setcolor");
        oscMessage.addStringArg(selectedQuadKey);
        oscMessage.addFloatArg(1.0f);
        oscMessage.addFloatArg(1.0f);
        oscMessage.addFloatArg(1.0f);
        oscMessage.addFloatArg(1.0f);
        OscManager::SendMessage(oscMessage);
    }


    if(key == 'a') {
        if(!selectedQuadKey.empty()) {
            float x, y;
            quads[selectedQuadKey]->getPoint(selectedVtx, x, y);
            x -= xoffset;
            setPoint(selectedQuadKey, selectedVtx, x, y);
        }
    }
    if(key == 'd') {
        if(!selectedQuadKey.empty()) {
            float x, y;
            quads[selectedQuadKey]->getPoint(selectedVtx, x, y);
            x += xoffset;
            setPoint(selectedQuadKey, selectedVtx, x, y);
        }
    }
    if(key == 's') {
        if(!selectedQuadKey.empty()) {
            float x, y;
            quads[selectedQuadKey]->getPoint(selectedVtx, x, y);
            y += yoffset;
            setPoint(selectedQuadKey, selectedVtx, x, y);
        }
    }
    if(key == 'w') {
        if(!selectedQuadKey.empty()) {
            float x, y;
            quads[selectedQuadKey]->getPoint(selectedVtx, x, y);
            y -= yoffset;
            setPoint(selectedQuadKey, selectedVtx, x, y);
        }
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
        saveShow();
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
    if(selectedIdx >= 0 && selectedVtx >= 0)
    {
        //ofLog(OF_LOG_VERBOSE, "mouseDragged: ===== selectedIds=%d, selectedVtx=%d", selectedIdx,selectedVtx);
        setPoint(selectedQuadKey, selectedVtx, x, y);
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

void testApp::quit(const std::vector<std::string> & args){
	std::exit(0);
}

int textureUnit = 0;

void setZ(string id, float z) {
    multimap<float, Quad2D*>::iterator it;
    bool quadFound = false;
    for(it = quadsByZ.begin(); it != quadsByZ.end(); it++) {
        if(it->second->getId().compare(id) == 0) {
            quadsByZ.erase(it);
            quadFound = true;
            break;
        }
    }
    if(quadFound) {
        quadsByZ.insert(pair<float, Quad2D*>(z, it->second));
    }
    else {
        ofLog(OF_LOG_VERBOSE, "Quad %s was not found to change Z.", id.c_str());
    }
}

void testApp::event(EventArg *e) {
    string address = e->args.getAddress().c_str();
    ofLog(OF_LOG_VERBOSE, "testApp:: Event received. address=%s", address.c_str());
    if(address.compare("/video/play") == 0) {
        //El parametro 0 indica que video iniciar.
        TextureManager::PlayVideo(e->args.getArgAsString(0), e->args.getArgAsFloat(1));
    }
    else if(address.compare("/video/stop") == 0) {
        //El parametro 0 indica que video detener.
        TextureManager::StopVideo(e->args.getArgAsString(0));
    }
    else if(address.compare("/video/set") == 0) {
        //param0 indica el quad al que asignar el video.
        //param1 indica el id del video a asignar.
        quads[e->args.getArgAsString(0)]->getMaterial()->SetTextureParams(e->args.getArgAsString(1), videoTexture, textureUnit);
        //textureUnit = (textureUnit + 1) % 8;
    }
    else if(address.compare("/synch/setpoint") == 0) {
        //param0
        setPoint(e->args.getArgAsString(0), e->args.getArgAsInt32(1), e->args.getArgAsInt32(2),
                 e->args.getArgAsInt32(3), false);
    }
    else if(address.compare("/synch/addquad") == 0) {
        selectedIdx = addQuad(e->args.getArgAsString(0).c_str(), false);
    }
    else if(address.compare("/synch/removequad") == 0) {
        selectedIdx = removeQuad(e->args.getArgAsString(0).c_str(), false);
    }
    else if(address.compare("/texture/setcolor") == 0) {
        ofLog(OF_LOG_VERBOSE, "testApp:: Setcolor for quad %s", e->args.getArgAsString(0).c_str());
        Quad2D *quad = quads[e->args.getArgAsString(0)];
        quad->getMaterial()->set(AMBIENT_R, e->args.getArgAsFloat(1));
        quad->getMaterial()->set(AMBIENT_G, e->args.getArgAsFloat(2));
        quad->getMaterial()->set(AMBIENT_B, e->args.getArgAsFloat(3));
        quad->getMaterial()->set(AMBIENT_A, e->args.getArgAsFloat(4));
    }
    else if(address.compare("/texture/setcolorgroup") == 0) {
        string groupId = e->args.getArgAsString(0);
        float r = e->args.getArgAsFloat(1);
        float g = e->args.getArgAsFloat(2);
        float b = e->args.getArgAsFloat(3);
        float a = e->args.getArgAsFloat(4);
        vector<Quad2D*>::iterator it;
        for(it = quadGroups[groupId].begin(); it != quadGroups[groupId].end(); ++it)
        {
            (*it)->getMaterial()->set(AMBIENT_R, r);
            (*it)->getMaterial()->set(AMBIENT_G, g);
            (*it)->getMaterial()->set(AMBIENT_B, b);
            (*it)->getMaterial()->set(AMBIENT_A, a);
        }
    }
    else if(address.compare("/texture/fadeto") == 0) {
        Material *mat = quads[e->args.getArgAsString(0)]->getMaterial();
        Animation *a = new LinearAnimation(mat, AMBIENT_A, e->args.getArgAsFloat(1), e->args.getArgAsFloat(2));
        AnimationLoop *loop = new AnimationLoop("loop");
        loop->AddAnimation(a);
        AnimationController::PlayLoop(loop);
    }
    else if(address.compare("/texture/fadetogroup") == 0) {
        string groupId = e->args.getArgAsString(0);
        vector<Quad2D*>::iterator it;
        for(it = quadGroups[groupId].begin(); it != quadGroups[groupId].end(); ++it)
        {
            Material *mat = (*it)->getMaterial();
            Animation *a = new LinearAnimation(mat, AMBIENT_A, e->args.getArgAsFloat(1), e->args.getArgAsFloat(2));
            AnimationLoop *loop = new AnimationLoop("loop");
            loop->AddAnimation(a);
            AnimationController::PlayLoop(loop);
        }
    }
    else if(address.compare("/quads/setz") == 0) {
        string quadID = e->args.getArgAsString(0);
        float z = e->args.getArgAsFloat(1);
        setZ(quadID, z);
    }
    else if(address.compare("/internal/playaudio") == 0) {
        mySound.play();
        std::cout << " ejecutando ahora: "<<   mySound.getIsPlaying() ;
    }
    else if(address.compare("/internal/settime") == 0) {
        float offset = e->args.getArgAsFloat(0);
        float percentPos = offset/632;        //dura 10 mins + 32 segs = 600 segs + 32 segs = 632 segs
        ofLog(OF_LOG_VERBOSE, "====== NUEVA POSITION %f", percentPos);
        mySound.setPosition(percentPos);
        TimeManager::SetOffset(offset);
    }
    else {
        ofLog(OF_LOG_WARNING, "unknown event with address %s", address.c_str());
    }
}

void testApp::setupLogging() {
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofLog(OF_LOG_VERBOSE, "Configuring Logs");
    ofLog(OF_LOG_VERBOSE, "Initiating with nodeName="+this->nodeName);
}

void testApp::setupConsole() {
    console = new ofxConsole();
    console->setDimentions(ofGetWidth(), ofGetHeight()/15);
	console->print("Mapping app started...");
	console->addFunction("quit", this, &testApp::quit);
	console->addFunction("addQuad", this, &testApp::addQuad);
	console->addFunction("removeQuad", this, &testApp::removeQuad);
	console->addFunction("removeQuadSel", this, &testApp::removeQuadSelected);
}

void testApp::setPoint(string selectedQuad, int selectedVtx, int x, int y, bool sendEvent) {
    quads[selectedQuad]->setPoint(selectedVtx, x, y);

    if (sendEvent) {
        ofxOscMessage oscMessage;
        oscMessage.setAddress("/synch/setpoint");
        oscMessage.addStringArg(selectedQuad);
        oscMessage.addIntArg(selectedVtx);
        oscMessage.addIntArg(x);
        oscMessage.addIntArg(y);
        OscManager::SendMessage(oscMessage);
    }
}

void testApp::addQuad(const std::vector<std::string> & args) {
	if(args.size()<2){
		console->print("Wrong number of arguments for < "+args[0]+" >!", CTEXT_ERROR);
		ofLog(OF_LOG_ERROR, "Wrong number of arguments for < "+args[0]+" >!");
		return;
	}
	string label = args[1];
    addQuad(label.c_str(), true);
}

int testApp::addQuad(string label, bool sendEvent) {
    ofLog(OF_LOG_NOTICE, "Adding QUAD [%s, %d]", label.c_str(), sendEvent);

    if (label.empty()) {
        char buffer [50];
        sprintf (buffer, "quad%d", quads.size());
        label = buffer;
    }

    Quad2D *q = new Quad2D(label);
    q->setSelected(true);
    q->setEnabled(true);
    quads.insert(pair<string, Quad2D*>(label, q));
    quadsByZ.insert(pair<float, Quad2D*>(0, q));

    if (sendEvent) {
        ofxOscMessage oscMessage;
        oscMessage.setAddress("/synch/addquad");
        oscMessage.addStringArg(label);
        OscManager::SendMessage(oscMessage);
    }

    return quads.size() - 1;
}

void testApp::removeQuadSelected(const std::vector<std::string> & args) {
	if(args.size()<1){
		console->print("Wrong number of arguments for < "+args[0]+" >!", CTEXT_ERROR);
		ofLog(OF_LOG_ERROR, "Wrong number of arguments for < "+args[0]+" >!");
		return;
	}
    removeQuad("", true);
}

void testApp::removeQuad(const std::vector<std::string> & args) {
	if(args.size()<2){
		console->print("Wrong number of arguments for < "+args[0]+" >!", CTEXT_ERROR);
		ofLog(OF_LOG_ERROR, "Wrong number of arguments for < "+args[0]+" >!");
		return;
	}
	string label = args[1];
    removeQuad(label.c_str(), true);
}

void removeQuadFromQuadsByZ(string label) {
    multimap<float, Quad2D*>::iterator it;
    for(it = quadsByZ.begin(); it != quadsByZ.end(); it++) {
        if(it->second->getId().compare(label) == 0) {
            quadsByZ.erase(it);
            ofLog(OF_LOG_VERBOSE, "testApp: quad %s removed from z container.", label.c_str());
            return;
        }
    }
    ofLog(OF_LOG_VERBOSE, "testApp: quad with id: %s not found in z container", label.c_str());
}

int testApp::removeQuad(string label, bool sendEvent) {
    ofLog(OF_LOG_NOTICE, "Removing QUAD [%s, %d]", label.c_str(), sendEvent);

    if (label.empty()) {
        ofLog(OF_LOG_WARNING, "Removing Quad with no label provided. Removing selected...");
        if(quads.size() > 0 && selectedIdx >= 0) {
            quadsIt = quads.begin();
            std::advance(quadsIt, selectedIdx);
            label = (*quadsIt).first;
            (*quadsIt).second->setSelected(false);
            quads.erase(quadsIt);
            removeQuadFromQuadsByZ(label);
            selectedQuadKey = "";
        } else {
            ofLog(OF_LOG_WARNING, "Removing Quad: no quads or not one selected.");
            return -1;
        }
    } else if (quads.size() > 0) {
        map<string, Quad2D*>::iterator q = quads.find(label);
        if(q != quads.end()){
            q->second->setSelected(false);
            quads.erase(q);
            removeQuadFromQuadsByZ(label);
            selectedQuadKey = "";
        } else {
            ofLog(OF_LOG_WARNING, "testApp:: No Quad for label '"+label+"'");
            return -1;
        }
    } else {
        ofLog(OF_LOG_ERROR, "Removing Quad:: Neither label or selected index provided.");
        return -1;
    }

    if (sendEvent) {
        ofxOscMessage oscMessage;
        oscMessage.setAddress("/synch/removequad");
        oscMessage.addStringArg(label);
        OscManager::SendMessage(oscMessage);
    }

    return quads.size() - 1;
}

void testApp::loadShow() {

    ofLog(OF_LOG_NOTICE, "loading show config...");
    showConfig.loadFile("./SHOWCONF.xml");
    showConfig.pushTag("Show");

    string showName = showConfig.getAttribute("Data", "name", "", 0);
    //std::cout << " showName: "<< showName;

    showConfig.pushTag("Ports");
    int numTags = showConfig.getNumTags("OscPorts");
    showConfig.pushTag("OscPorts");

    for(int i = 0; i < numTags; i++)
    {
        string name = showConfig.getAttribute("Port", "name", "", i);
        string port = showConfig.getAttribute("Port", "port", "", i);
        //std::cout << " Port OscPorts Data: "<<  port << endl;

        OscPorts.insert(pair<string, int>(name, atoi(port.c_str())));
    }
    showConfig.popTag();

    numTags = showConfig.getNumTags("MidiPorts");
    showConfig.pushTag("MidiPorts");

    for(int i = 0; i < numTags; i++)
    {
        string name = showConfig.getAttribute("Port", "name", "", i);
        string port = showConfig.getAttribute("Port", "port", "", i);
        //std::cout << " Port MidiPorts Data: "<<  port << endl;

        MidiPorts.insert(pair<string, string>(name, port));
    }
    showConfig.popTag();

    showConfig.popTag();

    showConfig.pushTag("Network");

    for(int i = 0; i < showConfig.getNumTags("Node"); i++)
    {
        string name = showConfig.getAttribute("Node", "name", "", i);
        string address = showConfig.getAttribute("Node", "address", "", i);
        string port = showConfig.getAttribute("Node", "port", "", i);
        //std::cout << " Network Data: "<< name + " " + address + " "+ port<< endl;

        Node NodeData;
        string newStr (address);
        NodeData.address = newStr;//address;
        NodeData.port = atoi(port.c_str());
        Network.insert(pair<string, Node>(name, NodeData));

    }
    showConfig.popTag();

    showConfig.pushTag("Textures", 0);
    showConfig.pushTag("Images");

    for(int i = 0; i < showConfig.getNumTags("Image"); i++)
    {
        string name = showConfig.getAttribute("Image", "name","", i);
        string path = showConfig.getAttribute("Image", "path","", i);
        //std::cout << " Images Data: "<< name + " " + path << endl;

        TextureManager::LoadImageTexture(name, path);

    }
    showConfig.popTag();

    showConfig.pushTag("Videos");
    for(int i = 0; i < showConfig.getNumTags("Video"); i++)
    {
        string name = showConfig.getAttribute("Video", "name","", i);
        string path = showConfig.getAttribute("Video", "path","", i);
        TextureManager::LoadVideoTexture(name, path);
    }
    showConfig.popTag();

    showConfig.popTag();

    showConfig.pushTag("Shapes");
    showConfig.pushTag("Quads2D");

    for(int i = 0; i < showConfig.getNumTags("Quad2D"); i++) {
        string id = showConfig.getAttribute("Quad2D", "id","", i);
        int x0 = showConfig.getAttribute("Quad2D", "x0", 0, i);
        int y0 = showConfig.getAttribute("Quad2D", "y0", 0, i);

        int x1 = showConfig.getAttribute("Quad2D", "x1", 50, i);
        int y1 = showConfig.getAttribute("Quad2D", "y1", 0, i);

        int x2 = showConfig.getAttribute("Quad2D", "x2", 50, i);
        int y2 = showConfig.getAttribute("Quad2D", "y2", 50, i);

        int x3 = showConfig.getAttribute("Quad2D", "x3", 50, i);
        int y3 = showConfig.getAttribute("Quad2D", "y3", 50, i);

        // add quad2
        addQuad(id, false);

        setPoint(id, 0, x0, y0, false);
        setPoint(id, 1, x1, y1, false);
        setPoint(id, 2, x2, y2, false);
        setPoint(id, 3, x3, y3, false);
    }

    showConfig.popTag();//Quads2D
    showConfig.popTag();//Shapes

    showConfig.pushTag("Groups", 0);

    for(int i=0; i < showConfig.getNumTags("Group"); i++) {
        string idGroup = showConfig.getAttribute("Group", "id", "", i);
        showConfig.pushTag("Group", i);

        vector<Quad2D*> qGroup;
        for(int j=0; j < showConfig.getNumTags("Item"); j++) {
            Quad2D *q = quads[showConfig.getAttribute("Item", "id", "", j)];
            qGroup.push_back(q);
        }
        quadGroups.insert(make_pair(idGroup.c_str(), qGroup));
        ofLog(OF_LOG_VERBOSE, "Cargando grupo %s con %i elementos.", idGroup.c_str(), qGroup.size());
        showConfig.popTag();
    }

    showConfig.popTag();//Groups

    showConfig.pushTag("Events", 0);
    showConfig.pushTag("OscEvents");

    for(int i = 0; i < showConfig.getNumTags("Event"); i++)
    {
        string name = showConfig.getAttribute("Event", "name","", i);
        string destination = showConfig.getAttribute("Event", "destination","", i);
        string delay = showConfig.getAttribute("Event", "delay","", i);
        //std::cout << " Event Data: "<< name + " " +destination+ " " +delay << endl;

        //   add synchmanager event
    }

    showConfig.popTag(); //OscEvents

    showConfig.pushTag("TimedEvents");
    for(int i = 0; i < showConfig.getNumTags("TimedEvent"); i++)
    {
        string destination = showConfig.getAttribute("TimedEvent", "destination","", i);
        float time = showConfig.getAttribute("TimedEvent", "time", 0.0, i);

        showConfig.pushTag("TimedEvent", i);
        for(int j=0; j< showConfig.getNumTags("Message"); j++) {
            string address = showConfig.getAttribute("Message", "address", "", j);
            string param1 = showConfig.getAttribute("Message", "param1", "", j);
            #ifdef CONSOLE
            if(address.compare("/video/play") == 0) {
                float param2f = showConfig.getAttribute("Message", "param2", 1.0, j);
                TimeManager::ScheduleEvent(time, destination, new EventArg(address, param1, param2f));
            } else if(address.compare("/texture/setcolor") == 0) {
                float param2f = showConfig.getAttribute("Message", "param2", 1.0, j);
                float param3f = showConfig.getAttribute("Message", "param3", 1.0, j);
                float param4f = showConfig.getAttribute("Message", "param4", 1.0, j);
                float param5f = showConfig.getAttribute("Message", "param5", 1.0, j);
                TimeManager::ScheduleEvent(time, destination, new EventArg(address, param1, param2f, param3f, param4f, param5f));
            } else if(address.compare("/texture/setcolorgroup") == 0){
                float param2f = showConfig.getAttribute("Message", "param2", 1.0, j);
                float param3f = showConfig.getAttribute("Message", "param3", 1.0, j);
                float param4f = showConfig.getAttribute("Message", "param4", 1.0, j);
                float param5f = showConfig.getAttribute("Message", "param5", 1.0, j);
                TimeManager::ScheduleEvent(time, destination, new EventArg(address, param1, param2f, param3f, param4f, param5f));
            } else if((address.compare("/texture/fadeto") == 0)) {
                float param2f = showConfig.getAttribute("Message", "param2", 1.0, j);
                float param3f = showConfig.getAttribute("Message", "param3", 1.0, j);
                TimeManager::ScheduleEvent(time, destination, new EventArg(address, param1, param2f, param3f));
            } else if((address.compare("/texture/fadetogroup") == 0)) {
                float param2f = showConfig.getAttribute("Message", "param2", 1.0, j);
                float param3f = showConfig.getAttribute("Message", "param3", 1.0, j);
                TimeManager::ScheduleEvent(time, destination, new EventArg(address, param1, param2f, param3f));
            } else if((address.compare("/quads/setz") == 0)) {
                float param2f = showConfig.getAttribute("Message", "param2", 0.0, j);
                TimeManager::ScheduleEvent(time, destination, new EventArg(address, param1, param2f));
            } else if((address.compare("/internal/settime") == 0)) {
                float param1f = showConfig.getAttribute("Message", "param1", 0.0, j);
                TimeManager::ScheduleEvent(time, destination, new EventArg(address, param1f, 0.0f, 0.0f, 0.0f));
            } else {
                string param2 = showConfig.getAttribute("Message", "param2", "", j);
                string param3 = showConfig.getAttribute("Message", "param3", "", j);
                string param4 = showConfig.getAttribute("Message", "param4", "", j);
                string param5 = showConfig.getAttribute("Message", "param5", "", j);
                std::cout << " TimedEvent Message: "<< address+ " " +param1 << " " << param2 << " " << param3 << " " << param4 << " " << param5 << endl;
                TimeManager::ScheduleEvent(time, destination, new EventArg(address, param1, param2, param3, param4, param5));
            }
            #endif
        }
        showConfig.popTag(); //TimedEvent
    }

    showConfig.popTag(); //TimedEvents
    showConfig.popTag(); //Events
    ofLog(OF_LOG_NOTICE, "Show config loaded.");
}

void testApp::saveShow() {

    showConfig.loadFile("./SHOWCONF.xml");
    showConfig.pushTag("Show");
    showConfig.pushTag("Shapes");
    showConfig.pushTag("Quads2D");

    showConfig.clear();
    //showConfig.addTag("Quads2D");
    showConfig.pushTag("Quads2D");

    float x0, y0;
    float x1, y1;
    float x2, y2;
    float x3, y3;
    string id;
    map<string, Quad2D*>::iterator iter = quads.begin();
    while (iter != quads.end() )
    {
        int showTagKey = showConfig.addTag("Quad2D");
        id=iter->first;
        showConfig.addAttribute("Quad2D", "id", id, showTagKey);
        (iter->second)->getPoint(0,x0,y0);
        showConfig.addAttribute("Quad2D", "x0", x0, showTagKey);
        showConfig.addAttribute("Quad2D", "y0", y0, showTagKey);
        (iter->second)->getPoint(1,x1,y1);
        showConfig.addAttribute("Quad2D", "x1", x1, showTagKey);
        showConfig.addAttribute("Quad2D", "y1", y1, showTagKey);
        (iter->second)->getPoint(2,x2,y2);
        showConfig.addAttribute("Quad2D", "x2", x2, showTagKey);
        showConfig.addAttribute("Quad2D", "y2", y2, showTagKey);
        (iter->second)->getPoint(3,x3,y3);
        showConfig.addAttribute("Quad2D", "x3", x3, showTagKey);
        showConfig.addAttribute("Quad2D", "y3", y3, showTagKey);

        iter++;
        std::cout << " iter id quad2D: "<< id << endl;

    }

    showConfig.popTag();
    showConfig.popTag();

    showConfig.saveFile("./SHOWCONF.xml");
    //ofLog(OF_LOG_NOTICE, "Show config saved.");
}
