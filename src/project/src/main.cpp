#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( int argc, char** argv ) {

    string nodeName = "noname";
    if (argc > 1){
        nodeName = argv[1];
    }

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW);			// <-------- setup the GL context

    #ifndef CONSOLE
    ofSetWindowPosition(-1024,0);
    #else
    ofSetWindowPosition(200,20);
    #endif

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp(nodeName));

}
