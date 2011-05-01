#ifndef LISTITEM_H
#define LISTITEM_H

#include "Effect.h"

#include <QList>
#include <QVariant>
#include <QVector>

using namespace std;

namespace gui {

//! [0]
class ListItem
{
public:
    ListItem(Effect *data = 0, string label = 0);
    ~ListItem();

    QVariant data(int column) /*const*/;
    bool setData(int column, const QVariant &value);
    Effect* getItemData();

private:
    string itemLabel;
    Effect *itemData;
};
//! [0]

}
#endif
