#ifndef MATERIALCONTROLLER_H
#define MATERIALCONTROLLER_H

#include "ofxShader.h"

enum SHADER_TYPE {AMBIENT_SHADER};

class MaterialController
{
    public:
        MaterialController();
        virtual ~MaterialController();

        static void Init();
        static ofxShader ambient_shader;

        static void EnableShader(SHADER_TYPE type);
        static void DisableShader();
    protected:
    private:
        static const string AMBIENT_SHADER_PATH;
        static SHADER_TYPE activeShader;

};

#endif // MATERIALCONTROLLER_H
