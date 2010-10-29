#include "MaterialController.h"

static const string AMBIENT_SHADER_PATH = "shaders/texture_ambient";
ofxShader MaterialController::ambient_shader;
SHADER_TYPE MaterialController::activeShader;

MaterialController::MaterialController()
{
    //ctor
}

MaterialController::~MaterialController()
{
    //dtor
}

void MaterialController::Init()
{
    ambient_shader.loadShader("shaders/texture_ambient");
}

void MaterialController::EnableShader(SHADER_TYPE type)
{
    ambient_shader.setShaderActive(true);
}

void MaterialController::DisableShader()
{
    ambient_shader.setShaderActive(false);
}
