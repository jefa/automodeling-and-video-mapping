#include "AnimationController.h"

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
void AnimationController::AddAnimation(Animation anim, ConcatenacionAnimaciones conc)
{

    if (conc == INMEDIATO)
    {
        //Quito repetidos si los hay
        for (int i = 0; i < animator.size(); i++)
        {
            Animation animIter = animator[i];
            if (animIter.mismaAnimacion(anim))
            {
                animator.erase(animator.begin() + i);
            }
        }
        for (int i = 0; i < colaEspera.size(); i++)
        {
            Animation animIter = colaEspera[i];
            if (animIter.mismaAnimacion(anim))
            {
                colaEspera.erase(colaEspera.begin() + i);
            }
        }
        animator.push_back(anim);
    }
    else if (conc == ESPERAFIN)
    {
        for (int i = 0; i < animator.size(); i++)
        {
            Animation animIter = animator[i];
            if (animIter.mismaAnimacion(anim))
            {
                colaEspera.push_back(anim);
                return; //Retorno porque hay una animacion activa del mismo tipo.
            }
        }
        animator.push_back(anim);
    }
}
