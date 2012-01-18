#ifndef _VMT
#define _VMT

#include "ofMain.h"

#include "vmtmodel.h"
#include "ofxCamera.h"
#include "ofxLight.h"
#include "treewindow.h"
#include "effectslistwindow.h"
#include "evteffectslistwindow.h"
#include "keyeffectslistwindow.h"
#include "timeline.h"

using namespace gui;

class Vmt : public ofBaseApp {

	public:
        Vmt();

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
        VmtModel *vmtModel;
        TreeWindow *treeWindow;
        EffectsListWindow *effectsWindow;
        evtEffectsListWindow *evteffectsWind;
        keyEffectsListWindow *evteffectsWindkey;

        timeline *timelineWindow;

};

#endif
