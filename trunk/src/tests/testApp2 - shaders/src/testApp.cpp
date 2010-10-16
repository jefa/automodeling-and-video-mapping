#include "testApp.h"

float lightDir[3] = { 0.7f, -0.7f, 0.0f};

//--------------------------------------------------------------
void testApp::setup(){
	myShader.loadShader("myShader");
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	//lets tumble the world with the mouse
	lightDir[0] += 0.01;
	lightDir[1] -= 0.01;
    glPushMatrix();




        myShader.setShaderActive(true);
        myShader.setUniformVariable3fv("lightDir", 1, lightDir);
        glEnable(GL_DEPTH_TEST);
        glPushMatrix();
        glTranslatef(ofGetWidth()/2.0, ofGetHeight()/2.0, 0);
        //tumble according to mouse
        glRotatef(-mouseY,1,0,0);
        glRotatef(mouseX,0,1,0);

        glutSolidTeapot(130);
        glPopMatrix();
        glDisable(GL_DEPTH_TEST);
        myShader.setShaderActive(false);

    glPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

