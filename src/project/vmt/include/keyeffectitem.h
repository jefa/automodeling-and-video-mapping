#ifndef KEYEFFECTITEM_H
#define KEYEFFECTITEM_H


#include <QList>
#include <QVariant>
#include <QVector>
#include <QTime>

using namespace std;

namespace gui {

//! [0]
class keyEffectItem
{
public:
    keyEffectItem(string idEffect = "", string key ="");
    ~keyEffectItem();

    QVariant data(int column) /*const*/;
    bool setData(int column, const QVariant &value);
    string getItemData();

private:
    string key;
    string idEffect;
};
//! [0]

}
#endif
