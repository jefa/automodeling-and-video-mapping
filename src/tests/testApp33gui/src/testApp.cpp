#include "testApp.h"

bool	myBool1Animate;
bool	myBool2;
bool	myBool3;
bool	myBool4;
bool	myBool5;
bool	myBool6;
bool	myBool7;
bool	myBool8;
bool	myBool9;

int		myInt1;
int		myInt2;
int		myInt3;
int		myInt4;
int		myInt5;
int		myInt6;
int		myInt7;
int		myInt8;
int		myInt9;

int      box1;
int      box2;

float	myFloat1;
float	myFloat2;
float	myFloat3;
float	myFloat4;
float	myFloat5;
float	myFloat6;
float	myFloat7;
float	myFloat8;
float	myFloat9;

ofxSimpleGuiControl *floatSliderControl = NULL;

ofColor	aColor;


// for demonstrating adding any drawable object (that extends ofBaseDraw);
ofVideoGrabber		vidGrabber;
unsigned char * 	videoInverted;
ofTexture			videoTexture;

bool	randomizeButton = true;

ofPoint *points;
ofPoint	v[300];


float translationX = -0.1;
int timeActualMS = 0;
int timeElapsedMS = 0;
int timeAnteriorMS = 0;


void mouse(int button, int state, int x, int y);


void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(24.0f, 1.33333f, 0.1f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(-2.24f, -0.5f, 1.53f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//gluLookAt(0.0f, 0.0f, 4.62f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	gluLookAt(-0.24f + 1.45f, -0.52f, 1.90f, 0.487f, 0.14f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void testApp::drawOBJ(ofxObjLoader obj3d){

  if (bMousePressed == false){
                    
        //draw the model
        glColor4f(0.5,1,0,0.4);//lime color
        obj3d.fillFaces();//first the faces
        
        glColor4f(0,0.8,0,1);//outline
        obj3d.outlineFaces();//then the edges.
      
  } else {
    
        glColor4f(0,0.1,0,0.5);//outline
        obj3d.outlineFaces();//then the edges.
        
        //wanna see the vertices?
        glColor4f(0,0,0,0.85);
        glPointSize(1);
        obj3d.pointVertices();
  }
  
}

//--------------------------------------------------------------
void testApp::setup(){

	setupLogging();
	ofLog(OF_LOG_NOTICE, "despues de setuploggiong");

	//para habilitar wheel detection
	//glutMouseFunc(mouse);

	//loadProject();
  
	int screenW = ofGetScreenWidth();
	int screenH = ofGetScreenHeight();
	//ofSetWindowPosition(screenW/2-300/2, screenH/2-300/2);

	bFullscreen	= 0;

  //ofBackground(0, 0, 0);
  //ofBackground(255,255,200);
  ofBackground(aColor.r * 255, aColor.g * 255.0f, aColor.b * 255.0);
  
  //for smooth animation
  ofSetVerticalSync(true);

  //turn on alpha blending for colors
  ofEnableAlphaBlending();

  //load some obj files from disk
  crane.loadFile("crane.obj");
  crane2.loadFile("cube.obj");

  bMousePressed = false;

	// for demonstrating adding any drawable object (that extends ofBaseDraw);
	vidGrabber.initGrabber(320, 240);	
	videoInverted 	= new unsigned char[int(vidGrabber.getWidth() * vidGrabber.getHeight() * 3)];
	videoTexture.allocate(vidGrabber.getWidth(), vidGrabber.getHeight(), GL_RGB);
	
	
	// 'gui' is a global variable declared in ofxSimpleGuiToo.h
	gui.addTitle("A group");
	gui.addToggle("myBool1 Animate", myBool1Animate);
	gui.addSlider("myFloat1: noise", myFloat1, 0.0, 1); 
	gui.addSlider("myInt1", myInt1, 100, 200); 
	gui.addComboBox("box1", box1, 12, NULL);
	gui.addButton("Randomize Background", randomizeButton);
	gui.addColorPicker("BG Color", &aColor.r);
	
	
	// start a new group
	gui.addTitle("Another group");
	
	floatSliderControl = &gui.addSlider("myFloat2", myFloat2, 0.0, 1);
	//floatSlyder = &floatSliderControl;
	((ofxSimpleGuiSliderFloat *)floatSliderControl)->setSmoothing(0.5);
	//gui.addSlider("myFloat2", myFloat2, 0.0, 1).setSmoothing(0.5);

	gui.addSlider("myInt2", myInt2, 3, 8);
	gui.addToggle("myBool2", myBool2);	
	string titleArray[] = {"Lame", "Alright", "Better", "Best"};
	gui.addComboBox("box2", box2, 4,  titleArray);
	gui.addFPSCounter();
	
	// new group, this time separate into it's own column
	gui.addTitle("Yes one more group").setNewColumn(true);
	gui.addToggle("myBool4", myBool4);	
	gui.addToggle("myBool3", myBool3);	
	gui.addSlider("myFloat3", myFloat3, 0.0, 1).setSmoothing(0.8);
	gui.addSlider("myFloat4", myFloat4, 0.0, 20).setSmoothing(1);
	gui.addSlider("myInt6", myInt6, 0, 10);
	gui.addSlider("myInt4", myInt4, 320, 1280);
	gui.addContent("Camera feed", vidGrabber);
	gui.addContent("Inverted", videoTexture);
	
	
	gui.addPage("A new page");		// use '[' ']' to cycle through pages, or keys 1-9
	gui.addSlider("myInt5", myInt5, 2, 5);
	gui.addSlider("myInt7", myInt7, 0, 100);
	gui.addSlider("myInt8", myInt8, 10, 50);
	gui.addSlider("myInt3", myInt3, 0, 100);
	gui.addSlider("myFloat7", myFloat7, 0.0, 1).setSmoothing(0.0);		// default
	gui.addSlider("myFloat8", myFloat8, 0.0, 0.1).setSmoothing(0.5);
	gui.addSlider("myInt9", myInt9, 0, 10).setSmoothing(0.9); 
	
	gui.addTitle("Final group?");
	gui.addToggle("myBool5", myBool5);	
	gui.addToggle("myBool6", myBool6);	
	gui.addToggle("myBool7", myBool7);	
	gui.addToggle("myBool8", myBool8);	
	
	
	// by default each page is saved in an xml with the same name as display name
	// you can override this with ofxSimpleGuiPage::setXMLName(string s);
	// ofxSimpleGuiToo::addPage() returns reference to the page, so you can do it directly on one line
	// of save it in a variable for use later
	gui.addPage("My 3rd page").setXMLName("foo.xml");	
	gui.addSlider("myFloat5", myFloat5, 0.0, 5);
	gui.addSlider("myFloat6", myFloat6, 0.0, 1);
	gui.addSlider("myFloat9", myFloat9, 0.0, 0.01 ); 
	gui.addToggle("myBool9", myBool9);	
	
	gui.loadFromXML();
	
	printf("myint : %i\n", myInt1);
	
	gui.show();

}

//--------------------------------------------------------------
void testApp::update(){

	timeActualMS = ofGetElapsedTimeMillis();
    timeElapsedMS = timeActualMS - timeAnteriorMS;
    timeAnteriorMS = timeActualMS;
	translationX += timeElapsedMS / 20000.0f;

	/*if(bFullscreen){
		ofHideCursor();
	}else{
		ofShowCursor();
	}*/

	if(myBool1Animate) myFloat1 = ofNoise(ofGetElapsedTimef());
	
	/*myFloat2 = ((ofxSimpleGuiSliderFloat *)floatSliderControl)->getValue();
	string str = ofToString(myFloat2);
	ofLog(OF_LOG_WARNING, str);*/

	if(randomizeButton) {
		randomizeButton = false;
		aColor.r = ofRandomuf();
		aColor.g = ofRandomuf();
		aColor.b = ofRandomuf();
	}
	
	// from ofVideoGrabber example (
	vidGrabber.update();
	if(vidGrabber.isFrameNew()){
		int totalPixels = vidGrabber.getWidth() * vidGrabber.getHeight() * 3;
		unsigned char * pixels = vidGrabber.getPixels();
		for(int i = 0; i < totalPixels; i++) videoInverted[i] = 255 - pixels[i];
		videoTexture.loadData(videoInverted, vidGrabber.getWidth(), vidGrabber.getHeight(), GL_RGB);
	}
}

//--------------------------------------------------------------
void testApp::draw(){
  //ofSetupScreen();
  //setupCamera();

  ofBackground(aColor.r * 255, aColor.g * 255.0f, aColor.b * 255.0);
  gui.draw();

  //draw in middle of the screen
  glTranslatef(ofGetWidth()/2,ofGetHeight()/2,0/*translationX*/);

  //tumble according to mouse
  if (myBool2 == true){
	  glRotatef(mouseY,1,0,0);
	  glRotatef(mouseX,0,1,0);
  }

  //scale large enough to see the model
  float s = min(ofGetWidth(),ofGetHeight())*0.4;
  glScalef(s,s,s);

  drawOBJ(crane);

  glTranslatef(myFloat2,myFloat2,0);
  
  drawOBJ(crane2);

	glPushMatrix();
		//we position the rotation point
		//at the location we want it to
		//spin around .
		glTranslatef(750, 320, 0);
		glRotatef(/*spin*/0, 0, 0, 1);

		//draw a red circle
		ofSetColor(255,0, 0);
		ofCircle(-50, -25, 100);

		//draw a green circle
		ofSetColor(0,255, 0);
		ofCircle(50, -25, 100);

		//draw a blue circle
		ofSetColor(0, 0, 255);
		ofCircle(0, 57, 100);
	glPopMatrix();
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
  //loop through all the crane's vertices and scramble each point a
  //little bit.
  for(int i=0;i<crane.vertices.size();i++){
    crane.vertices[i].x += ofRandomf()*0.1;
    crane.vertices[i].y += ofRandomf()*0.1;
    crane.vertices[i].z += ofRandomf()*0.1;
  }

	if(key == 'f'){
		bFullscreen = !bFullscreen;
		if(!bFullscreen){
			ofSetWindowShape(300,300);
			ofSetFullscreen(false);
			// figure out how to put the window in the center:
			int screenW = ofGetScreenWidth();
			int screenH = ofGetScreenHeight();
			ofSetWindowPosition(screenW/2-300/2, screenH/2-300/2);
		} else if(bFullscreen == 1){
			ofSetFullscreen(true);
		}
	} else if(key == 's'){ //no data gets saved unless you hit the s key
		XML.saveFile("myProject.xml");
		printf("project saved to xml!\n");
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
  
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
  
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
     bMousePressed = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
     bMousePressed = false;
}

void testApp::loadProject(){
	//we load our settings file
	//if it doesn't exist we can still make one
	//by hitting the 's' key
	if( XML.loadFile("myProject.xml") ){
		printf("myProject.xml loaded!\n");
	}else{
		printf("unable to load myProject.xml check data/ folder\n");
	}

	//read the colors from XML
	//if the settings file doesn't exist we assigns default values (170, 190, 240)
	red		= XML.getValue("BACKGROUND:COLOR:RED", 170);
	green	= XML.getValue("BACKGROUND:COLOR:GREEN", 190);
	blue	= XML.getValue("BACKGROUND:COLOR:BLUE", 240);

	/*	"BACKGROUND:COLOR:RED" referes to a structure like this:
		<BACKGROUND>
			<COLOR>
				<RED>101.103516</RED>
			</COLOR>
		</BACKGROUND>	*/
}

void testApp::saveProject(){
	ofLog(OF_LOG_NOTICE, "salvando proyecto");

	//update the colors to the XML structure when the mouse is released
	jefaXML.clear();
	int tagkey = jefaXML.addTag("Project");
	jefaXML.addAttribute("Project", "Nombre", "nomProyecto", tagkey);

	jefaXML.pushTag("Project", tagkey);
	tagkey = jefaXML.addTag("Objetos");

	jefaXML.pushTag("Objetos", tagkey);
	tagkey = jefaXML.addTag("Objeto");

	jefaXML.pushTag("Objeto", tagkey);
	jefaXML.setValue("POSITION:X", 10);
	jefaXML.setValue("POSITION:Y", 20);
	jefaXML.setValue("POSITION:Z", 30);
	jefaXML.popTag();

	tagkey = jefaXML.addTag("Objeto");
	jefaXML.pushTag("Objeto", tagkey);
	jefaXML.setValue("POSITION:X", 50);
	jefaXML.setValue("POSITION:Y", 60);
	jefaXML.setValue("POSITION:Z", 70);
	jefaXML.popTag();

	jefaXML.saveFile("./jefa.xml");

}

void mouse(int button, int state, int x, int y) {
   switch(button) {
   case GLUT_LEFT_BUTTON:
   case GLUT_RIGHT_BUTTON:
      // ...
      break;

   case GLUT_WHEEL_UP:
      assert(state == GLUT_UP);
      printf("Wheel UP????\n");
      break;
   case GLUT_WHEEL_DOWN:
      assert(state == GLUT_UP);
      printf("Wheel DOWN????\n");
      break;
   }
}

void testApp::exit(){
	saveProject();
}

void testApp::setupLogging(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofLog(OF_LOG_VERBOSE, "seteando logs");
}