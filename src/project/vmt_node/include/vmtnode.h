#ifndef _VMTNODE
#define _VMTNODE

#include "ofMain.h"
#include "ofxOsc.h"

#include "Scene.h"

// listen on port 12345
#define PORT 12345
#define NUM_MSG_STRINGS 20


//--------------------------------------------------------
class VmtNode : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		ofTrueTypeFont		font;


private:
		ofxOscReceiver	receiver;

		int				current_msg_string;
		string		msg_strings[NUM_MSG_STRINGS];
		float			timers[NUM_MSG_STRINGS];

		int				mouseX, mouseY;
		string			mouseButtonState;

		Scene *scene;
};

#endif
