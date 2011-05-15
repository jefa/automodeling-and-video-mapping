#ifndef EVTEFFECTITEM_H
#define EVTEFFECTITEM_H


#include <QList>
#include <QVariant>
#include <QVector>
#include <QTime>

using namespace std;

namespace gui {

//! [0]
class evtEffectItem
{
public:
    evtEffectItem(string idEffect = "", QTime Time = QTime(0, 0, 0, 0) );
    ~evtEffectItem();

    QVariant data(int column) /*const*/;
    bool setData(int column, const QVariant &value);
    QTime getItemData();

private:
    QTime evtTime;
    string idEffect;
};
//! [0]

}
#endif
