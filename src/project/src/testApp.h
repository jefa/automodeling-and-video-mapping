#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "Object3D.h"
#include "Translation.h"
#include "SynchManager.h"
#include "MidiManager.h"
#include "IEventListener.h"
#include "Quad2D.h"
#include "ofxMidiEvents.h"

class testApp : public ofBaseApp, public IEventListener, public ofxMidiListener {

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

        void setPoint(int selectedIdx, int selectedVtx,
                      int x, int y, bool sendEvent=true);
		int addQuad(int selIdx, bool sendEvent=true);

		void event(EventArg *e);

        void setupLogging();
        void saveQuads();
        void loadQuads();

    private:
		Object3D *obj3D;
		SynchManager *synchManager;
		MidiManager	*midiManager;
};

#endif
