#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

#include <QtGui\QApplication>

//========================================================================
int main(int argc, char *argv[]){//you have to add
                                //int argc, char *argv[]
    QApplication app(argc, argv); //Qt app
    //Q_INIT_RESOURCE(yourResources); //Load Qt resource (icons) //named “yourResources” in the lib

    ofAppGlutWindow window2;
	ofSetupOpenGL(&window2, 1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:

	ofRunApp( new testApp());

    return app.exec(); //Qt app
    //return tabdialog.exec();
}


