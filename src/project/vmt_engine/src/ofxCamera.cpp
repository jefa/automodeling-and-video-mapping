#include "ofxCamera.h"

map<string, Layer2D*>::iterator layersIt;

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

void ofxCamera::drawCamera(/*MeshModel &m, Shotf &ls, */bool DrawFrustum/*, int cameraSourceId, QPainter *painter, QFont qf*/)
{

  /*if(!ls.IsValid())
  {
    if(cameraSourceId == 1 ) glLabel::render2D(painter,glLabel::TOP_LEFT,"Current Mesh Has an invalid Camera");
    else if(cameraSourceId == 2 ) glLabel::render2D(painter,glLabel::TOP_LEFT,"Current Raster Has an invalid Camera");
    else glLabel::render2D(painter,glLabel::TOP_LEFT,"Current TrackBall Has an invalid Camera");
    return;
  }*/

  glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT | GL_DEPTH_BUFFER_BIT );
	glDepthFunc(GL_ALWAYS);
	glDisable(GL_LIGHTING);
	glColor3f(.8f,.8f,.8f);

  int ln=0;
  //if(ls.Intrinsics.cameraType == Camera<float>::PERSPECTIVE) glLabel::render2D(painter,glLabel::TOP_LEFT,ln++, "Camera Type: Perspective");
  //if(ls.Intrinsics.cameraType == Camera<float>::ORTHO)       glLabel::render2D(painter,glLabel::TOP_LEFT,ln++, "Camera Type: Orthographic");

  //Point3f vp = ls.GetViewPoint();
  ofxVec3f vp = this->getEye();
  //glLabel::render2D(painter,glLabel::TOP_LEFT,ln++, QString("ViewPoint %1 %2 %3").arg(vp[0]).arg(vp[1]).arg(vp[2]));
  //Point3f ax0 = ls.Axis(0);
  ofxVec3f ax0 = this->getPosition()[0];
  //glLabel::render2D(painter,glLabel::TOP_LEFT,ln++, QString("axis 0 - %1 %2 %3").arg(ax0[0]).arg(ax0[1]).arg(ax0[2]));
  //Point3f ax1 = ls.Axis(1);
  ofxVec3f ax1 = this->getPosition()[1];
  //glLabel::render2D(painter,glLabel::TOP_LEFT,ln++, QString("axis 1 - %1 %2 %3").arg(ax1[0]).arg(ax1[1]).arg(ax1[2]));
  //Point3f ax2 = ls.Axis(2);
  ofxVec3f ax2 = this->getPosition()[2];
  //glLabel::render2D(painter,glLabel::TOP_LEFT,ln++, QString("axis 2 - %1 %2 %3").arg(ax2[0]).arg(ax2[1]).arg(ax2[2]));
  //float fov = ls.GetFovFromFocal();
  //glLabel::render2D(painter,glLabel::TOP_LEFT,ln++, QString("Fov %1 ( %2 x %3) ").arg(fov).arg(ls.Intrinsics.ViewportPx[0]).arg(ls.Intrinsics.ViewportPx[1]));
  //float focal = ls.Intrinsics.FocalMm;
  //glLabel::render2D(painter,glLabel::TOP_LEFT,ln++, QString("Focal Lenght %1 (pxsize %2 x %3) ").arg(focal).arg(ls.Intrinsics.PixelSizeMm[0]).arg(ls.Intrinsics.PixelSizeMm[1]));
  //if(ls.Intrinsics.cameraType == Camera<float>::PERSPECTIVE)
  //{
	//float len = m.cm.bbox.Diag()/20.0;
	float len = 200/20.0;
	 	glBegin(GL_LINES);
			glVertex3f(vp[0]-len,vp[1],vp[2]); 	glVertex3f(vp[0]+len,vp[1],vp[2]);
			glVertex3f(vp[0],vp[1]-len,vp[2]); 	glVertex3f(vp[0],vp[1]+len,vp[2]);
			glVertex3f(vp[0],vp[1],vp[2]-len); 	glVertex3f(vp[0],vp[1],vp[2]+len);
		glEnd();

    glBegin(GL_LINES);
      ofxVec3f vp1 = vp+ax0*len*2.0;
      glColor3f(1.0,0,0); /*gl*/ofVertex(vp.x,vp.y); 	/*gl*/ofVertex(vp1.x, vp1.y);
      ofxVec3f vp2 = vp+ax1*len*2.0;
      glColor3f(0,1.0,0); /*gl*/ofVertex(vp.x,vp.y); 	/*gl*/ofVertex(vp2.x, vp2.y);
      ofxVec3f vp3 = vp+ax2*len*2.0;
      glColor3f(0,0,1.0); /*gl*/ofVertex(vp.x,vp.y); 	/*gl*/ofVertex(vp3.x, vp3.y);
    glEnd();

// Now draw the frustum
/*    ofxVec3f viewportCenter = vp - ax2*ls.Intrinsics.FocalMm;
    ofxVec3f viewportHorizontal = ax0* float(ls.Intrinsics.ViewportPx[0]*ls.Intrinsics.PixelSizeMm[0]/2.0f);
    ofxVec3f viewportVertical   = ax1* float(ls.Intrinsics.ViewportPx[1]*ls.Intrinsics.PixelSizeMm[1]/2.0f);

    glColor3f(0.0f,1.0f,1.0f);
    glBegin(GL_LINES);
    glColor(Color4b::White);
    glVertex3f(vp[0],vp[1],vp[2]); glVertex(viewportCenter);
    glColor(Color4b::Cyan);
    glVertex(vp); glVertex(viewportCenter+viewportHorizontal+viewportVertical);
    glVertex(vp); glVertex(viewportCenter+viewportHorizontal-viewportVertical);
    glVertex(vp); glVertex(viewportCenter-viewportHorizontal+viewportVertical);
    glVertex(vp); glVertex(viewportCenter-viewportHorizontal-viewportVertical);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex(viewportCenter+viewportHorizontal+viewportVertical);
    glVertex(viewportCenter+viewportHorizontal-viewportVertical);
    glVertex(viewportCenter-viewportHorizontal-viewportVertical);
    glVertex(viewportCenter-viewportHorizontal+viewportVertical);
    glEnd();


    if(DrawFrustum)
    {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(.8f,.8f,.8f,.2f);
      glBegin(GL_TRIANGLE_FAN);
      glVertex(vp);
      glVertex(viewportCenter+viewportHorizontal+viewportVertical);
      glVertex(viewportCenter+viewportHorizontal-viewportVertical);
      glVertex(viewportCenter-viewportHorizontal-viewportVertical);
      glVertex(viewportCenter-viewportHorizontal+viewportVertical);
      glVertex(viewportCenter+viewportHorizontal+viewportVertical);
      glEnd();
    }
*/  //}
    glPopAttrib();
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
