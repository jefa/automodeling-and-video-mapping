#include "ofxCamera.h"

#include <cmath>

map<string, Layer2D*>::iterator layersIt;

float Rad2Deg (float Angle) {
  static float ratio = 180.0 / 3.141592653589793238;
  return Angle * ratio;
}

float Deg2Rad (float Angle) {
  static float ratio = 3.141592653589793238 / 180.0 ;
  return Angle * ratio;
}

ofxCamera::ofxCamera() {
    setOrigin(OF_ORIGIN);
	perspective();
	position();
	eye();
	up();
}

void ofxCamera::position(float x, float y, float z) {
	posCoord.x = x;
	posCoord.y = y;
	posCoord.z = z;
}

void ofxCamera::position(ofxVec3f _pos) {
	posCoord = _pos;
}

void ofxCamera::position() {
    if(origin == OF_ORIGIN) {
        posCoord.x = (float)w/2.0f;
        posCoord.y = (float)h/2.0f;
    }
    else {
        posCoord.x = 0.0f;
        posCoord.y = 0.0f;
    }
	float halfFov = PI * fieldOfView / 360.0f;
	float theTan = tanf(halfFov);
	posCoord.z = posCoord.y/theTan;
}

void ofxCamera::lerpPosition(float _targetX, float _targetY, float _targetZ, float _step) {
	posCoord.x += (_targetX - posCoord.x) * _step;
	posCoord.y += (_targetY - posCoord.y) * _step;
	posCoord.z += (_targetZ - posCoord.z) * _step;
}

void ofxCamera::lerpPosition(ofxVec3f target, float step) {
	lerpPosition(target.x, target.y, target.z, step);
}

void ofxCamera::lerpEye(float _targetX, float _targetY, float _targetZ, float _step) {
	eyeCoord.x += (_targetX - eyeCoord.x) * _step;
	eyeCoord.y += (_targetY - eyeCoord.y) * _step;
	eyeCoord.z += (_targetZ - eyeCoord.z) * _step;
}

void ofxCamera::lerpEye(ofxVec3f target, float step) {
	lerpEye(target.x, target.y, target.z, step);
}

void ofxCamera::eye(float x, float y, float z) {
	eyeCoord.x = x;
	eyeCoord.y = y;
	eyeCoord.z = z;
}

void ofxCamera::eye(ofxVec3f _pos) {
	eyeCoord = _pos;
}

void ofxCamera::eye() {
    if(origin == OF_ORIGIN) {
        eyeCoord.x = (float)w/2.0f;
        eyeCoord.y = (float)h/2.0f;
    }
    else {
        eyeCoord.x = 0;
        eyeCoord.y = 0;
    }
	eyeCoord.z = 0;
}

void ofxCamera::up(float _nx, float _ny, float _nz) {
	upVec.x = _nx;
	upVec.y = _ny;
	upVec.z = _nz;
}

void ofxCamera::up(ofxVec3f _up) {
	upVec = _up;
}

void ofxCamera::up() {
	upVec.x = 0;
	upVec.y = 1;
	upVec.z = 0;
}

void ofxCamera::perspective(float _fov, float _aspect, float _zNear, float _zFar) {
	fieldOfView = _fov;
	aspectRatio = _aspect;
	if(_zNear==0) _zNear = 0.01;
	zNear = _zNear;
	zFar = _zFar;
}

void ofxCamera::perspective() {
	fieldOfView = 65.0f;
	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);
	aspectRatio = (float)w/(float)h;
	zNear = 1.0f;
	zFar = 10000.0f;
}

// This sets the camera origin to either OF coordinates or zero (for OF_ORIGIN_ZERO)
void ofxCamera::setOrigin(cameraOrigin org) {
    origin = org;
	position();
	eye();
}

void ofxCamera::place() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fieldOfView, aspectRatio, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posCoord[0], posCoord[1], posCoord[2], eyeCoord[0], eyeCoord[1], eyeCoord[2], upVec[0], upVec[1], upVec[2]);

	// the coordinate system here is based on 2d geometry:
	// down = +y
	// right = +x
	// out of screen = +z
	// this is a bit different from the usual 3d coordinate systems,
	// where +y is up instead of down
	if(origin == OF_ORIGIN) {
        glScalef(1, -1, 1);
        glTranslatef(0, -h, 0);
	}
}

//Removes the camera, so it returns as if there was no camera
void ofxCamera::remove() {
	ofSetupScreen();
}

void ofxCamera::moveLocal(float _x, float _y, float _z) {
	moveLocal(ofxVec3f(_x, _y, _z));
}

void ofxCamera::moveLocal(ofxVec3f move) {
	ofxVec3f dir =  getDir().normalized();
	posCoord += dir.rescaled(move.z);
	eyeCoord += dir.rescaled(move.z);

	posCoord += upVec.rescaled(move.y);
	eyeCoord += upVec.rescaled(move.y);

	posCoord += dir.getCrossed(upVec).rescaled(move.x);
	eyeCoord += dir.getCrossed(upVec).rescaled(move.x);
}

void ofxCamera::moveGlobal(float _x, float _y, float _z) {
	posCoord.x += _x;
	posCoord.y += _y;
	posCoord.z += _z;
	eyeCoord.x += _x;
	eyeCoord.y += _y;
	eyeCoord.z += _z;
}

void ofxCamera::moveGlobal(ofxVec3f move) {
	posCoord += move;
	eyeCoord += move;
}

void ofxCamera::orbitAround(ofxVec3f target, ofxVec3f axis, float angle) {
	ofxVec3f r = posCoord-target;
	posCoord = target + r.rotated(angle, axis);
}

void ofxCamera::rotate(ofxVec3f axis, float angle) {
	ofxVec3f r = -posCoord+eyeCoord;
	eyeCoord = posCoord + r.rotated(angle, axis);
}

//
//Getters
//
ofxVec3f ofxCamera::getDir() {
	return eyeCoord-posCoord;
}

ofxVec3f ofxCamera::getPosition() {
	return posCoord;
}

ofxVec3f ofxCamera::getEye() {
	return eyeCoord;
}

ofxVec3f ofxCamera::getUp() {
	return upVec;
}

bool ofxCamera::isProjector(){
    return projector;
}

void ofxCamera::setIsProjector(bool projector){
    this->projector = projector;
}

Layer2D* ofxCamera::addLayer2D(string id) {
    Layer2D* layer = new Layer2D(id);
    layers2D.insert(pair<string, Layer2D*>(id, layer));
    return layer;
}

Layer2D* ofxCamera::getLayer2D(string id) {
    return layers2D[id];
}

map<string, Layer2D*> ofxCamera::getLayers2D() {
    return layers2D;
}

void ofxCamera::drawLayers() {
    for(layersIt = layers2D.begin(); layersIt != layers2D.end(); layersIt++) {
            layersIt->second->draw();
    }
}

void ofxCamera::drawCamera(){

    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT | GL_DEPTH_BUFFER_BIT );
    glDepthFunc(GL_ALWAYS);
    glDisable(GL_LIGHTING);
    glColor3f(.8f,.8f,.8f);

    //ofCircle(getPosition()[0], getPosition()[1], 2);
    glutSolidSphere(5, 1, 1);

    /*glBegin(GL_LINES);
        glVertex3f(pos[0],pos[1],pos[2]); 	glVertex3f(ax0[0],ax0[1],ax0[2]);
        glVertex3f(pos[0],pos[1],pos[2]); 	glVertex3f(ax1[0],ax1[1],ax1[2]);
        glVertex3f(pos[0],pos[1],pos[2]); 	glVertex3f(ax2[0],ax2[1],ax2[2]);
    glEnd();*/

    ofxVec3f lVec = getDir();
    ofxVec3f upVec = getUp();
    ofxVec3f rightVec = lVec.crossed(upVec);
    //printf("================= Vector L:     (%f,%f,%f)\n", lVec[0],lVec[1],lVec[2]);
    //printf("================= Vector UP:    (%f,%f,%f)\n", upVec[0],upVec[1],upVec[2]);
    //printf("================= Vector RIGHT: (%f,%f,%f)\n", rightVec[0],rightVec[1],rightVec[2]);

    glColor3f(1.0, 1.0, 0.0);

    float length = lVec.length();
    float fovRadians = Deg2Rad(this->fieldOfView);
    float apHf = 2 * length * tan ( fovRadians / 2 );
    float apVf = apHf / aspectRatio;
    //printf("================= Vector FOV: %f, %f\n", this->fieldOfView, fovRadians);
    //printf("================= Vector LVEC length: %f\n", length);
    //printf("================= Vector ASPECTRATIO: %f \n", aspectRatio);
    //printf("================= Vector APH: %f ::: APV: %f\n", apHf, apVf);

    ofxVec3f vecUp =  upVec * apVf / 2; //(0, apVf/2, eye[2]);
    ofxVec3f vecRight = rightVec * apHf ; //(apHf/2, 0, eye[2]);

    ofxVec3f p1 = lVec - vecRight + vecUp;
    ofxVec3f p2 = lVec + vecRight + vecUp;
    ofxVec3f p3 = lVec - vecRight - vecUp;
    ofxVec3f p4 = lVec + vecRight - vecUp;

    //printf("================= Vector P1:  (%f,%f,%f)\n", p1[0],p1[1],p1[2]);
    //printf("================= Vector P2:  (%f,%f,%f)\n", p2[0],p2[1],p2[2]);
    //printf("================= Vector P3:  (%f,%f,%f)\n", p3[0],p3[1],p3[2]);
    //printf("================= Vector P4:  (%f,%f,%f)\n", p4[0],p4[1],p4[2]);

    glBegin(GL_LINES);
        glVertex3f(getPosition()[0],getPosition()[1],getPosition()[2]); 	glVertex3f(p1[0],p1[1],p1[2]);
        glVertex3f(getPosition()[0],getPosition()[1],getPosition()[2]); 	glVertex3f(p2[0],p2[1],p2[2]);
        glVertex3f(getPosition()[0],getPosition()[1],getPosition()[2]); 	glVertex3f(p3[0],p3[1],p3[2]);
        glVertex3f(getPosition()[0],getPosition()[1],getPosition()[2]); 	glVertex3f(p4[0],p4[1],p4[2]);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(p1[0],p1[1],p1[2]);
        glVertex3f(p2[0],p2[1],p2[2]);
        glVertex3f(p4[0],p4[1],p4[2]);
        glVertex3f(p3[0],p3[1],p3[2]);
    glEnd();

    glPopAttrib();

    //printf("\n");
}
