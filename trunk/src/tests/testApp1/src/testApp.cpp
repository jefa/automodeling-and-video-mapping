#include "testApp.h"

GLfloat * point1 = new GLfloat[2];
GLfloat * point2 = new GLfloat[2];
GLfloat * point3 = new GLfloat[2];
GLfloat * point4 = new GLfloat[2];

GLfloat * point5 = new GLfloat[2];
GLfloat * point6 = new GLfloat[2];
GLfloat * point7 = new GLfloat[2];
GLfloat * point8 = new GLfloat[2];

GLfloat * point9 = new GLfloat[2];
GLfloat * point10 = new GLfloat[2];
GLfloat * point11 = new GLfloat[2];
GLfloat * point12 = new GLfloat[2];

int clickN = 0;

ofVideoPlayer fingerMovie;
ofVideoPlayer planeMovie;
ofVideoPlayer cartoonMovie;

/***/

void bindMyTexture(ofVideoPlayer *ofvp) {
    ofTexture &tex = ofvp->getTextureReference();
    tex.bind();
   
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();
   
    ofTextureData texData = tex.getTextureData();
    if(texData.textureTarget == GL_TEXTURE_RECTANGLE_ARB) {
        glScalef(tex.getWidth(), tex.getHeight(), 1.0f);
    } else {
        glScalef(tex.getWidth() / texData.tex_w, tex.getHeight() / texData.tex_h, 1.0f);
    }
   
    glMatrixMode(GL_MODELVIEW);
}

void unbindMyTexture(ofVideoPlayer *ofvp) {
    ofvp->getTextureReference().unbind();
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

//--------------------------------------------------------------
void testApp::setup(){

	//set background to black
	ofBackground(0, 0, 0);

	//for smooth animation, set vertical sync if we can
	ofSetVerticalSync(true);
	// also, frame rate:
	ofSetFrameRate(60);

	fingerMovie.loadMovie("fingers.mov");
	fingerMovie.play();

	cartoonMovie.loadMovie("cartoon.mov");
	cartoonMovie.play();

	planeMovie.loadMovie("plane_lands.avi");
	planeMovie.play();
}

//--------------------------------------------------------------
void testApp::update(){
	fingerMovie.idleMovie();
	cartoonMovie.idleMovie();
	planeMovie.idleMovie();
}

void drawPoint(const GLfloat* p1)
{
	glBegin(GL_POINTS);
	glVertex2fv(p1);
	glEnd( );
}

void drawLine(const GLfloat* p1, const GLfloat* p2)
{
	glBegin(GL_LINES);
	glVertex2fv(p1);
	glVertex2fv(p2);
	glEnd( );
}

void drawTri(const GLfloat* p1, const GLfloat* p2, const GLfloat* p3)
{
	glBegin(GL_TRIANGLES);
	glVertex2fv(p1);
	glVertex2fv(p2);
	glVertex2fv(p3);
	glEnd( );
}

void drawQuad(const GLfloat* p1, const GLfloat* p2, const GLfloat* p3, const GLfloat* p4)
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2fv(p1);
	glTexCoord2f(1.0f, 0.0f); glVertex2fv(p2);
	glTexCoord2f(1.0f, 1.0f); glVertex2fv(p3);
	glTexCoord2f(0.0f, 1.0f); glVertex2fv(p4);
	glEnd( );
}

void drawFirstQuad()
{
	bindMyTexture(&fingerMovie);
	drawQuad(point1, point2, point3, point4);
	unbindMyTexture(&fingerMovie);
}

void draw2ndQuad()
{
	bindMyTexture(&cartoonMovie);
	drawQuad(point5, point6, point7, point8);
	unbindMyTexture(&cartoonMovie);
}

void draw3rdQuad()
{
	bindMyTexture(&planeMovie);
	drawQuad(point9, point10, point11, point12);
	unbindMyTexture(&planeMovie);
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetupScreen();

	if(clickN > 0)
	{
		switch(clickN) {
			case 1:
				drawPoint(point1);
				break;
			case 2:
				drawLine(point1, point2);
				break;
			case 3:
				drawTri(point1, point2, point3);
				break;
			case 4:
				drawFirstQuad();
				break;
			case 5:
				drawFirstQuad();
				drawPoint(point5);
				break;
			case 6:
				drawFirstQuad();
				drawLine(point5, point6);
				break;
			case 7:
				drawFirstQuad();
				drawTri(point5, point6, point7);
				break;
			case 8:
				drawFirstQuad();
				draw2ndQuad();
				break;
			case 9:
				drawFirstQuad();
				draw2ndQuad();
				drawPoint(point9);
				break;
			case 10:
				drawFirstQuad();
				draw2ndQuad();
				drawLine(point9, point10);
				break;
			case 11:
				drawFirstQuad();
				draw2ndQuad();
				drawTri(point9, point10, point11);
				break;
			default:
				drawFirstQuad();
				draw2ndQuad();
				draw3rdQuad();
				break;
		}
	}
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

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
	clickN += 1;

	switch(clickN) {
		case 1:
			point1[0] = x;
			point1[1] = y;
			break;
		case 2:
			point2[0] = x;
			point2[1] = y;
			break;
		case 3:
			point3[0] = x;
			point3[1] = y;
			break;
		case 4:
			point4[0] = x;
			point4[1] = y;
			break;

		case 5:
			point5[0] = x;
			point5[1] = y;
			break;
		case 6:
			point6[0] = x;
			point6[1] = y;
			break;
		case 7:
			point7[0] = x;
			point7[1] = y;
			break;
		case 8:
			point8[0] = x;
			point8[1] = y;
			break;

		case 9:
			point9[0] = x;
			point9[1] = y;
			break;
		case 10:
			point10[0] = x;
			point10[1] = y;
			break;
		case 11:
			point11[0] = x;
			point11[1] = y;
			break;
		case 12:
			point12[0] = x;
			point12[1] = y;
			break;
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

