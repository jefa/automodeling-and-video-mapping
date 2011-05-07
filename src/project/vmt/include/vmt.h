#ifndef _VMT
#define _VMT

#include "ofMain.h"

#include "vmtmodel.h"
#include "ofxCamera.h"
#include "ofxLight.h"
#include "treewindow.h"
#include "effectslistwindow.h"

using namespace gui;

enum CAM_CONTROL_MODE {
	ORBIT_MODE,
	PAN_MODE,
	ROLL_MODE,
	DOLLY_MODE
};

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

        void setControlMode(CAM_CONTROL_MODE mode);
        CAM_CONTROL_MODE getControlMode();

    private:
        VmtModel *vmtModel;
        TreeWindow *treeWindow;
        EffectsListWindow *effectsWindow;
        CAM_CONTROL_MODE control_mode;
};

#endif
