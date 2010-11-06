#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "Object3D.h"
#include "Translation.h"
#include "OscManager.h"
#include "MidiManager.h"
#include "IEventListener.h"
#include "Quad2D.h"
#include "ofxMidiEvents.h"
#include "ofxConsole.h"
#include "DrawEventArg.h"
#include "TimedEventArg.h"


class testApp : public ofBaseApp, public IEventListener, public ofxMidiListener {

	public:

        testApp(string nodeName);

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
        void quit(const std::vector<std::string> & args);

        void setupLogging();
        void setupConsole();

        void setPoint(int selectedIdx, int selectedVtx,
                      int x, int y, bool sendEvent=true);
		int addQuad(const char* label=NULL, bool sendEvent=true);
		void addQuad(const std::vector<std::string> & args);

		void event(EventArg *e);

        void saveQuads();
        void loadQuads();

        void saveShow();
        void loadShow();

    private:
        string nodeName;
		Object3D *obj3D;
		OscManager *oscManager;
		MidiManager	*midiManager;
        ofxConsole * console;

};

#endif
