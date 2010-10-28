#ifndef MATERIALCONTROLLER_H
#define MATERIALCONTROLLER_H

#include "ofxShader.h"

enum SHADER_TYPE {AMBIENT_SHADER};

class MaterialController
{
    public:
        MaterialController();
        virtual ~MaterialController();

        ofxShader ambient_shader;

        void EnableShader(SHADER_TYPE type);
        void DisableShader();
    protected:
    private:
        const string AMBIENT_SHADER_PATH;
        SHADER_TYPE activeShader;

};

const string AMBIENT_SHADER_PATH = "shaders/ambient";

#endif // MATERIALCONTROLLER_H
