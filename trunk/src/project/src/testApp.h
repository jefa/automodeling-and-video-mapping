#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "Object3D.h"
#include "Translation.h"
#include "SynchManager.h"

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

    private:
		Object3D *obj3D;
		SynchManager *synchManager;
};

#endif
