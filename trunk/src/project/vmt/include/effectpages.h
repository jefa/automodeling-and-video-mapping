#ifndef EFFECTPAGES_H
#define EFFECTPAGES_H

#include "Effect.h"
#include "PositionEffect.h"
#include "VmtModel.h"

#include <QtGui>

void setComboIndexForText(QComboBox *combo, string txt);

class PositionEffectPage : public QWidget
{
public:
    PositionEffectPage(VmtModel *vmtModel, Effect *ef, QWidget *parent = 0);
    void saveEffect();

private:
    void loadEffect();

    PositionEffect *effect;
    VmtModel *vmtModel;

    QLineEdit *effectIdTxt;
    QComboBox *objectCombo;
    QDoubleSpinBox *xIniSpinBox;
    QDoubleSpinBox *yIniSpinBox;
    QDoubleSpinBox *zIniSpinBox;
    QDoubleSpinBox *xFinSpinBox;
    QDoubleSpinBox *yFinSpinBox;
    QDoubleSpinBox *zFinSpinBox;
    QDoubleSpinBox *delaySpinBox;

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
