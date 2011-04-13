#include "Object3D.h"

//-------------------------------------------
static string getExtension( string filename ){
	std::string::size_type idx;
	idx = filename.rfind('.');

	if(idx != std::string::npos){
		return filename.substr(idx+1);
	}
	else{
		return "";
	}
}

//-------------------------------------------
Object3D::Object3D(string id, string path){
    this->id = id;
    numRotations = 0;
    rotAngle.clear();
    rotAxis.clear();
    scale = ofPoint(1, 1, 1);

	model = NULL;

	if( model != NULL)delete model;

	string ext = getExtension( path );
	if( ext == "3ds" || ext == "3DS" ){
		model = new model3DS(path.c_str(), 3);
	}
}

Object3D::~Object3D(){
    //dtor
    if( model != NULL )delete model;
}

void Object3D::draw() {
    glPushMatrix();
        glTranslatef(pos.x, pos.y, pos.z);

        glScalef(scale.x, scale.y, scale.z);
        for(int i = 0; i < numRotations; i++){
            glRotatef(rotAngle[i], rotAxis[i].x, rotAxis[i].y, rotAxis[i].z);
        }

        glShadeModel(GL_SMOOTH);
		if( model->hasTexture)glEnable(GL_TEXTURE_2D);
            model->draw();
        if( model->hasTexture)glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

//-------------------------------------------
void Object3D::setPosition(float x, float y, float z){
    pos.x = x;
    pos.y = y;
    pos.z = z;
}

void Object3D::setScale(float x, float y, float z){
    scale.x = x;
    scale.y = y;
    scale.z = z;
}

//-------------------------------------------
void Object3D::setRotation(int which, float angle, float rot_x, float rot_y, float rot_z){

    if(which + 1 > numRotations){
        int diff = 1 + (which - numRotations);
        for(int i = 0; i < diff; i++){
            rotAngle.push_back(0);
            rotAxis.push_back(ofPoint());
        }
        numRotations = rotAngle.size();
    }

    rotAngle[which]  = angle;
    rotAxis[which].x = rot_x;
    rotAxis[which].y = rot_y;
    rotAxis[which].z = rot_z;
}

float Object3D::get(int aParam) {
    switch(aParam) {
        case POS_X:
            return pos.x;
        case POS_Y:
            return pos.y;
        case POS_Z:
            return pos.z;
    }
    return 0;
}

void Object3D::set(int aParam, float aValue) {
    switch(aParam) {
        case POS_X:
            pos.x = aValue;
            break;
        case POS_Y:
            pos.y = aValue;
            break;
        case POS_Z:
            pos.z = aValue;
            break;
    }
}

void Object3D::setId(string id){
    this->id = id;
}

string Object3D::getId(){
    return this->id;
}
