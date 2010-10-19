#ifndef _TEST_APP
#define _TEST_APP

#if !defined(GLUT_WHEEL_UP)
#  define GLUT_WHEEL_UP   3
#  define GLUT_WHEEL_DOWN 4
#endif

#include "ofMain.h"

#define OF_ADDON_USING_OFXOBJLOADER
#define OF_ADDON_USING_OFXXMLSETTINGS
#define OF_ADDON_USING_OFXSIMPLEGUITOO

#include "ofAddons.h"

class testApp : public ofSimpleApp{
	
	public:
  
		void setup();
		void update();
		void draw();
		void exit();
		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();

		void testApp::drawOBJ(ofxObjLoader obj3d);
		void testApp::loadProject();
		void testApp::saveProject();
		void testApp::setupLogging();

		ofxXmlSettings XML;
		ofxXmlSettings jefaXML;
		
		//my 3d model
		ofxObjLoader crane;
		ofxObjLoader crane2;
        bool bMousePressed;
		bool bFullscreen;

		float red;
		float green;
		float blue;

};

#endif	
