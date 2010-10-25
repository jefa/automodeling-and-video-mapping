#ifndef POINTEVENT_H_INCLUDED
#define POINTEVENT_H_INCLUDED

#include "EventArg.h"

class PointEventArg : public EventArg {
  public:
    int _shapeId;
    int _vertexId;
    float _x;
    float _y;

};

#endif
