#ifndef ANIMEVENT_H_INCLUDED
#define ANIMEVENT_H_INCLUDED

#include "EventArg.h"

class AnimEventArg : public EventArg {
  public:
    bool isActivate;
    string id;

};

#endif
