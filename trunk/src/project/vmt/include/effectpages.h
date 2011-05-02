#ifndef EFFECTPAGES_H
#define EFFECTPAGES_H

#include "Effect.h"
#include "VmtModel.h"

#include <QWidget>

class PositionEffectPage : public QWidget
{
public:
    PositionEffectPage(VmtModel *vmtModel, Effect *ef, QWidget *parent = 0);
};

class FadeEffectPage : public QWidget
{
public:
    FadeEffectPage(VmtModel *vmtModel, Effect *ef, QWidget *parent = 0);
};

class TextureEffectPage : public QWidget
{
public:
    TextureEffectPage(VmtModel *vmtModel, Effect *ef, QWidget *parent = 0);
};

#endif
