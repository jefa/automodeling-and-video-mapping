#include "testApp.h"
#include <QtGui>

//--------------------------------------------------------------
void testApp::setup(){
	counter = 0;
	vagRounded.loadFont("vag.ttf", 32);
	ofBackground(50,50,50);
	synth.loadSound("sounds/synth.wav");

	//FMOD_System_GetSpectrum(sys, fftSpectrum, nBandsToGet, 0, FMOD_DSP_FFT_WINDOW_HANNING);


     QGraphicsItem *ball = new QGraphicsEllipseItem(0, 0, 20, 20);
     QGraphicsItem *bar = new QGraphicsLineItem(0, 0, 0, 20);

     QPen mypen = QPen( QColor( 204, 0, 255, 76 ) );
     mypen.setWidth(5);
     ((QGraphicsLineItem*)bar)->setPen(mypen);

     QTimeLine *timer = new QTimeLine(5000);
     timer->setFrameRange(0, 100);

     QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
     //animation->setItem(ball);
     animation->setItem(bar);
     animation->setTimeLine(timer);

     for (int i = 0; i < 200; ++i)
         animation->setPosAt(i / 200.0, QPointF(i, /*i*/1));

     QGraphicsScene *scene = new QGraphicsScene();
     scene->setSceneRect(0, 0, 250, 250);
     scene->addItem(ball);
     scene->addItem(bar);

     QGraphicsView *view = new QGraphicsView(scene);
     view->move(1000, 500);
     view->show();

     timer->start();

}


//--------------------------------------------------------------
void testApp::update(){
	counter = counter + 0.033f;
}

//--------------------------------------------------------------
void testApp::draw(){

	sprintf (timeString, "time: %0.2i:%0.2i:%0.2i \nelapsed time %i", ofGetHours(), ofGetMinutes(), ofGetSeconds(), ofGetElapsedTimeMillis());

	float w = vagRounded.stringWidth(eventString);
	float h = vagRounded.stringHeight(eventString);

	ofSetColor(0xffffff);
	vagRounded.drawString(eventString, 98,198);

	ofSetColor(255,122,220);
	vagRounded.drawString(eventString, 100,200);


	ofSetColor(0xffffff);
	vagRounded.drawString(timeString, 98,98);

	ofSetColor(255,122,220);
	vagRounded.drawString(timeString, 100,100);

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	sprintf(eventString, "keyPressed = (%i)", key);
	printf("keyPressed = (%i)\n", key);
	if (key = 's') {
        sliderWindow.show();
        timelineWindow.show();
//	} else if (key = 't') {
	}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	sprintf(eventString, "mouseMoved = (%i,%i)", x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	sprintf(eventString, "mouseDragged = (%i,%i - button %i)", x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	sprintf(eventString, "mousePressed = (%i,%i - button %i)", x, y, button);

}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	sprintf(eventString, "mouseReleased = (%i,%i - button %i)", x, y, button);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	sprintf(eventString, "resized = (%i,%i)", w, h);
}

void testApp::setBackground(int value){
    ofBackground(value,50,50);
}
