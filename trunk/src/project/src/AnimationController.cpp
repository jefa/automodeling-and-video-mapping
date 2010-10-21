#include "AnimationController.h"
#include <iostream>
using namespace std;

AnimationController::AnimationController()
{
    //ctor
}

AnimationController::~AnimationController()
{
    //dtor
}

/// <summary>
/// Agrega una animacion a la lista correspondiente dependiendo del tipo de concatenación.
/// </summary>
/// <param name="anim"></param>
/// <param name="conc"></param>
void AnimationController::AddAnimation(Animation *anim, AnimationsLinking conc)
{
    if (conc == IMMEDIATE)
    {
        //Quito repetidos si los hay
        for (unsigned int i = 0; i < animator.size(); i++)
        {
            Animation *animIter = animator[i];
            if (animIter->mismaAnimacion(anim))
            {
                animator.erase(animator.begin() + i);
            }
        }
        for (unsigned int i = 0; i < colaEspera.size(); i++)
        {
            Animation *animIter = colaEspera[i];
            if (animIter->mismaAnimacion(anim))
            {
                colaEspera.erase(colaEspera.begin() + i);
            }
        }
        animator.push_back(anim);
    }
    else if (conc == WAITEND)
    {
        for (unsigned int i = 0; i < animator.size(); i++)
        {
            Animation *animIter = animator[i];
            if (animIter->mismaAnimacion(anim))
            {
                colaEspera.push_back(anim);
                return; //Retorno porque hay una animacion activa del mismo tipo.
            }
        }
        animator.push_back(anim);
    }

}

void AnimationController::Update(unsigned int interval)
{
    for (unsigned int i = 0; i < animator.size(); i++)
    {
        Animation *anim = animator[i];
        anim->Update(interval);
        break;
        if (anim->isOff())
        {
            animator.erase(animator.begin() + i);

            //Busco si hay una animacion del mismo tipo esperando
            //y si encuentro una la agrego a animator y la saco de colaEspera
            for (unsigned int j = 0; j < colaEspera.size(); j++)
            {
                Animation *espera = colaEspera[j];
                if (espera->mismaAnimacion(anim))
                {
                    animator.push_back(espera);
                    colaEspera.erase(colaEspera.begin() + j);
                    break;
                }
            }
        }
    }
}
