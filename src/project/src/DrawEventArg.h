#ifndef POINTEVENT_H_INCLUDED
#define POINTEVENT_H_INCLUDED

#include "EventArg.h"

class DrawEventArg : public EventArg {
  public:
    int _shapeId;
    int _vertexId;
    int _x;
    int _y;
    int _evtType;
};

#endif
