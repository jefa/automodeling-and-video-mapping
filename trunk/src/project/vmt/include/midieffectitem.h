#ifndef MIDIEFFECTITEM_H
#define MIDIEFFECTITEM_H


#include <QList>
#include <QVariant>
#include <QVector>
#include <QTime>

using namespace std;

namespace gui {

//! [0]
class midiEffectItem
{
public:
    midiEffectItem(string idEffect = "", char key ='a');
    ~midiEffectItem();

    QVariant data(int column) /*const*/;
    bool setData(int column, const QVariant &value);
    char getItemData();

private:
    char key;
    string idEffect;
};
//! [0]

}
#endif
