#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( int argc, char** argv ) {

    int minResWidth = 800;
    int maxResWidth = 2048;
    int minResHeight = 300;
    int maxResHeight = 2048;
    int minPosWinX = -2048;
    int maxPosWinX = 2048;
    int minPosWinY = 0;
    int maxPosWinY = 1024;

    string nodeName = "noname";
    int resWidth, resHeight, posWinX, posWinY;
    if (argc != 6){
        ofLog(OF_LOG_ERROR, "Debe iniciar el programa con 6 argumentos: %s nodeName resWidth resHeight posWinX posWinY", argv[0]);
        return -1;
    }
    else {
        nodeName = argv[1];
        resWidth = atoi(argv[2]);
        resHeight = atoi(argv[3]);
        posWinX = atoi(argv[4]);
        posWinY = atoi(argv[5]);

        if(resWidth > maxResWidth || resWidth < minResWidth) {
            ofLog(OF_LOG_ERROR, "el argumento resWidth debe estar entre %i y %i", minResWidth, maxResWidth);
            return -1;
        }
        if(resHeight > maxResHeight || resHeight < minResHeight) {
            ofLog(OF_LOG_ERROR, "el argumento resHeight debe estar entre %i y %i", minResHeight, maxResHeight);
            return -1;
        }
        if(posWinX > maxPosWinX || posWinX < minPosWinX) {
            ofLog(OF_LOG_ERROR, "el argumento posWinX debe estar entre %i y %i", minPosWinX, maxPosWinX);
            return -1;
        }
        if(posWinY > maxPosWinY || posWinY < minPosWinY) {
            ofLog(OF_LOG_ERROR, "el argumento posWinY debe estar entre %i y %i", minPosWinY, maxPosWinY);
            return -1;
        }
    }

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, resWidth, resHeight, OF_WINDOW);			// <-------- setup the GL context

    ofSetWindowPosition(posWinX, posWinY);


	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp(nodeName));

}
