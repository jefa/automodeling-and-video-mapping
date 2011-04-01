#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "ofxCamera.h"
#include "ofxLight.h"

#include "Scene.h"
#include "treewindow.h"

using namespace gui;

class vmt : public ofBaseApp {

	public:
        vmt();

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

        float centerX, centerY, centerZ;
        float camX, camY, camZ;

    private:
        Scene *scene;
        TreeWindow *treeWindow;

};

#endif
