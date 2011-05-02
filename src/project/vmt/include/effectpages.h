#ifndef EFFECTPAGES_H
#define EFFECTPAGES_H

#include <QWidget>

class PositionEffectPage : public QWidget
{
public:
    PositionEffectPage(QWidget *parent = 0);
};

class FadeEffectPage : public QWidget
{
public:
    FadeEffectPage(QWidget *parent = 0);
};

class TextureEffectPage : public QWidget
{
public:
    TextureEffectPage(QWidget *parent = 0);
};

#endif
