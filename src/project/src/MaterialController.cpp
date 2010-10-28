#include "MaterialController.h"

MaterialController::MaterialController()
{
    //ctor
    ambient_shader.loadShader(AMBIENT_SHADER_PATH);
}

MaterialController::~MaterialController()
{
    //dtor
}

void MaterialController::EnableShader(SHADER_TYPE type)
{
    activeShader = type;
    switch(type)
    {
        case AMBIENT_SHADER:
            ambient_shader.setShaderActive(true);
            break;
    }
}

void MaterialController::DisableShader()
{
    switch(activeShader)
    {
        case AMBIENT_SHADER:
            ambient_shader.setShaderActive(false);
            break;
    }
}
