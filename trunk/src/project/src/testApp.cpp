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

map<string, Material*> materials;

string selectedQuadKey;
int selectedIdx = 0;
int selectedVtx = 0;
float xoffset = 1;
float yoffset = 1;
bool consoleEnabled = false;

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
	ofBackground(0, 60, 0);

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

    for(quadsIt = quads.begin(); quadsIt != quads.end(); ++quadsIt) {
        (*quadsIt).second->draw();
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
        selectedIdx = addQuad();
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

void testApp::quit(const std::vector<std::string> & args){
	std::exit(0);
}

void testApp::event(EventArg *e) {
    string address = e->args.getAddress();
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
        quads[e->args.getArgAsString(0)]->getMaterial()->SetTextureParams(e->args.getArgAsString(1), videoTexture, 0);
    }
    else if(address.compare("/synch/setpoint") == 0) {
        //param0
        setPoint(e->args.getArgAsInt32(0), e->args.getArgAsInt32(1), e->args.getArgAsInt32(2),
                 e->args.getArgAsInt32(3), false);
    }
    else if(address.compare("/synch/addquad") == 0) {
        selectedIdx = addQuad(e->args.getArgAsString(0).c_str(), false);
    }
    else if(address.compare("/synch/removequad") == 0) {
        selectedIdx = removeQuad(e->args.getArgAsString(0).c_str(), false);
    }
    else if(address.compare("/texture/setcolor") == 0) {
        Quad2D *quad = quads[e->args.getArgAsString(0)];
        quad->getMaterial()->set(AMBIENT_R, e->args.getArgAsFloat(1));
        quad->getMaterial()->set(AMBIENT_G, e->args.getArgAsFloat(2));
        quad->getMaterial()->set(AMBIENT_B, e->args.getArgAsFloat(3));
        quad->getMaterial()->set(AMBIENT_A, e->args.getArgAsFloat(4));
    }
    else if(address.compare("/texture/fadeout") == 0) {
        Material *mat = quads[e->args.getArgAsString(0)]->getMaterial();
        Animation *a = new LinearAnimation(mat, AMBIENT_A, e->args.getArgAsFloat(1), 0.0f);
        AnimationLoop *loop = new AnimationLoop("loop");
        loop->AddAnimation(a);
        //AnimationController::AddLoop("loop", loop);
        //AnimationController::PlayLoop("loop");
        AnimationController::PlayLoop(loop);
    }
    else if(address.compare("/texture/fadein") == 0) {
        Material *mat = quads[e->args.getArgAsString(0)]->getMaterial();
        Animation *a = new LinearAnimation(mat, AMBIENT_A, e->args.getArgAsFloat(1), 1.0f);
        AnimationLoop *loop = new AnimationLoop("loop");
        loop->AddAnimation(a);
        AnimationController::PlayLoop(loop);
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

void testApp::setPoint(int selectedIdx, int selectedVtx, int x, int y, bool sendEvent) {
    quadsIt = quads.begin();
    std::advance(quadsIt, selectedIdx);
    (*quadsIt).second->setPoint(selectedVtx, x, y);

    if (sendEvent) {
        ofxOscMessage oscMessage;
        oscMessage.setAddress("/synch/setpoint");
        oscMessage.addIntArg(selectedIdx);
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
    addQuad(label.c_str());
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
    removeQuad();
}

void testApp::removeQuad(const std::vector<std::string> & args) {
	if(args.size()<2){
		console->print("Wrong number of arguments for < "+args[0]+" >!", CTEXT_ERROR);
		ofLog(OF_LOG_ERROR, "Wrong number of arguments for < "+args[0]+" >!");
		return;
	}
	string label = args[1];
    removeQuad(label.c_str());
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

void testApp::loadQuads() {
    ofLog(OF_LOG_NOTICE, "loading project...");

    quadsXML.loadFile("./quads.xml");

    quadsXML.pushTag("quads");

    int numQuadItems = quadsXML.getNumTags("quadItem");

    for(int i = 0; i < numQuadItems; i++)
    {
        selectedIdx = addQuad();

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

void testApp::loadShow() {

    ofLog(OF_LOG_NOTICE, "loading show config...");
    showConfig.loadFile("./SHOWCONF.xml");
    showConfig.pushTag("Show");

    string showName = showConfig.getAttribute("Data", "name", "", 0);
    //std::cout << " showName: "<< showName;

    showConfig.pushTag("Ports");
    int numItems = showConfig.getNumTags("OscPorts");
    showConfig.pushTag("OscPorts");

    for(int i = 0; i < numItems; i++)
    {
        string name = showConfig.getAttribute("Port", "name", "", i);
        string port = showConfig.getAttribute("Port", "port", "", i);
        //std::cout << " Port OscPorts Data: "<<  port << endl;

        OscPorts.insert(pair<string, int>(name, atoi(port.c_str())));
    }
    showConfig.popTag();

    numItems = showConfig.getNumTags("MidiPorts");
    showConfig.pushTag("MidiPorts");

    for(int i = 0; i < numItems; i++)
    {
        string name = showConfig.getAttribute("Port", "name", "", i);
        string port = showConfig.getAttribute("Port", "port", "", i);
        //std::cout << " Port MidiPorts Data: "<<  port << endl;

        MidiPorts.insert(pair<string, string>(name, port));
    }
    showConfig.popTag();

    showConfig.popTag();

    showConfig.pushTag("Network");
    numItems = showConfig.getNumTags("Node");

    for(int i = 0; i < numItems; i++)
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
    numItems = showConfig.getNumTags("Image");

    for(int i = 0; i < numItems; i++)
    {
        string name = showConfig.getAttribute("Image", "name","", i);
        string path = showConfig.getAttribute("Image", "path","", i);
        //std::cout << " Images Data: "<< name + " " + path << endl;

        TextureManager::LoadImageTexture(name, path);

    }
    showConfig.popTag();


    showConfig.pushTag("Videos");
    numItems = showConfig.getNumTags("Video");
    for(int i = 0; i < numItems; i++)
    {
        string name = showConfig.getAttribute("Video", "name","", i);
        string path = showConfig.getAttribute("Video", "path","", i);
        //std::cout << " Videos Data: "<< name + " " + path << endl;

        TextureManager::LoadVideoTexture(name, path);
    }
    showConfig.popTag();

    showConfig.popTag();

    showConfig.pushTag("Shapes");
    showConfig.pushTag("Quads2D");
    numItems = showConfig.getNumTags("Quad2D");

    for(int i = 0; i < numItems; i++)
    {
        string id = showConfig.getAttribute("Quad2D", "id","", i);
        double x0 = showConfig.getAttribute("Quad2D", "x0", 0.0, i);
        double y0 = showConfig.getAttribute("Quad2D", "y0", 0.0, i);

        double x1 = showConfig.getAttribute("Quad2D", "x1", 50.0, i);
        double y1 = showConfig.getAttribute("Quad2D", "y1", 0.0, i);

        double x2 = showConfig.getAttribute("Quad2D", "x2", 50.0, i);
        double y2 = showConfig.getAttribute("Quad2D", "y2", 50.0, i);

        double x3 = showConfig.getAttribute("Quad2D", "x3", 50.0, i);
        double y3 = showConfig.getAttribute("Quad2D", "y3", 50.0, i);

        //std::cout << " Quad2D Data: "<< id<< endl;

        // add quad2
        int selIdx = addQuad(id.c_str(), false);
        setPoint(selIdx, 0, x0, y0, false);
        setPoint(selIdx, 1, x1, y1, false);
        setPoint(selIdx, 2, x2, y2, false);
        setPoint(selIdx, 3, x3, y3, false);

    }

    showConfig.popTag();

    showConfig.popTag();

    showConfig.pushTag("Events", 0);
    showConfig.pushTag("OscEvents");
    numItems = showConfig.getNumTags("Event");

    for(int i = 0; i < numItems; i++)
    {
        string name = showConfig.getAttribute("Event", "name","", i);
        string destination = showConfig.getAttribute("Event", "destination","", i);
        string delay = showConfig.getAttribute("Event", "delay","", i);
        //std::cout << " Event Data: "<< name + " " +destination+ " " +delay << endl;

        //   add synchmanager event
    }

    showConfig.popTag(); //OscEvents

    showConfig.pushTag("TimedEvents");
    numItems = showConfig.getNumTags("TimedEvent");
    for(int i = 0; i < numItems; i++)
    {
        string destination = showConfig.getAttribute("TimedEvent", "destination","", i);
        float time = showConfig.getAttribute("TimedEvent", "time", 0.0, i);
        //std::cout << " TimedEvent Data: "<< destination+ " " +time << endl;
        string address = showConfig.getAttribute("TimedEvent:Message", "address", "", i);
        string param1 = showConfig.getAttribute("TimedEvent:Message", "param1", "", i);

        #ifdef CONSOLE
        if(address.compare("/video/play") == 0) {
            float param2f = showConfig.getAttribute("TimedEvent:Message", "param2", 1.0, i);
            TimeManager::ScheduleEvent(time, destination, new EventArg(address, param1, param2f));
        } else if(address.compare("/texture/setcolor") == 0) {
            float param2f = showConfig.getAttribute("TimedEvent:Message", "param2", 1.0, i);
            float param3f = showConfig.getAttribute("TimedEvent:Message", "param3", 1.0, i);
            float param4f = showConfig.getAttribute("TimedEvent:Message", "param4", 1.0, i);
            float param5f = showConfig.getAttribute("TimedEvent:Message", "param5", 1.0, i);
            TimeManager::ScheduleEvent(time, destination, new EventArg(address, param1, param2f, param3f, param4f, param5f));
        } else if((address.compare("/texture/fadeout") == 0) || (address.compare("/texture/fadein") == 0)) {
            float param2f = showConfig.getAttribute("TimedEvent:Message", "param2", 1.0, i);
            TimeManager::ScheduleEvent(time, destination, new EventArg(address, param1, param2f));

        } else {
            string param2 = showConfig.getAttribute("TimedEvent:Message", "param2", "", i);
            string param3 = showConfig.getAttribute("TimedEvent:Message", "param3", "", i);
            string param4 = showConfig.getAttribute("TimedEvent:Message", "param4", "", i);
            string param5 = showConfig.getAttribute("TimedEvent:Message", "param5", "", i);
            std::cout << " TimedEvent Message: "<< address+ " " +param1 << " " << param2 << " " << param3 << " " << param4 << " " << param5 << endl;
            TimeManager::ScheduleEvent(time, destination, new EventArg(address, param1, param2, param3, param4, param5));
        }
        #endif
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
