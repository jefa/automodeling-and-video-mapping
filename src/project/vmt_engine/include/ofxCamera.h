#pragma once

#include "ISerializable.h"
#include "ofMain.h"
#include "ofxVectorMath.h"
#include "Layer2D.h"

class ofxCamera: public ISerializable {
public:
	ofxCamera();

	void position(float x, float y, float z);
	void position(ofxVec3f _pos);
	void position(); //reset the position to initial values

	void eye(float _x, float _y, float _z);
	void eye(ofxVec3f _eye);
	void eye(); //reset eye psition to the initial values
	void up(float _x, float _y, float _z);
	void up(ofxVec3f _up);
	void up(); //reset up vector to initial values

	float getfieldOfView();
	float getaspectRatio();
	float getzNear();
	float getzFar();

	void perspective(float _fov, float _aspect, float _zNear, float _zFar);
	void perspective();//reset perspective to initial values

	virtual void place(); //this must go in the draw function!!!!
	void remove(); //Removes the camera, so it returns as if there was no camera

	void moveLocal(float _x, float _y, float _z); //Moves the camera along it's own coordinatesystem
	void moveLocal(ofxVec3f move);
	void moveGlobal(float _x, float _y, float _z); //Moves the camera along the global coordinatesystem
	void moveGlobal(ofxVec3f move);

	void orbitAround(ofxVec3f target, ofxVec3f axis, float value);
	void rotate(ofxVec3f axis, float value);

	ofxVec3f getDir();
	ofxVec3f getPosition();
	ofxVec3f getEye();
	ofxVec3f getUp();

	void setId(string id);
	string getId();

    void drawCamera();
    bool isProjector();
    void setIsProjector(bool);

    void drawLayers();

    //resolucion de la ventana en el nodo.
    void setClientResolution(int resx, int resy);

    Layer2D* addLayer2D(string id);
    Layer2D* getLayer2D(string id);
    map<string, Layer2D*> getLayers2D();

    SerializedNode* Serialize();

    void calculateHomography();
    void resetHomography();

    void setDisplayHelpers(bool);
    void setSrcHelperCoord(int i, ofxVec2f coord);
    void setDstHelperCoord(int i, ofxVec2f coord);
    ofxVec2f getSrcHelperCoord(int i);
    ofxVec2f getDstHelperCoord(int i);

protected:
	ofxVec3f posCoord;
	ofxVec3f eyeCoord;
	ofxVec3f upVec;

	//relative to defining the persperctive:
	float	fieldOfView;
	int	w;
	int	h;
	float	aspectRatio;
	float zNear, zFar;

private:
	bool projector;
	string id;
    map<string, Layer2D*> layers2D;
    int clientX, clientY;

    void SetupScreen_ext();

    GLfloat homographyMatrix[16];

    bool displayHelpers;

    ofxVec2f helperSrc[4];
    ofxVec2f helperDst[4];

    float helpersRadius;

};



