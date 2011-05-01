#include "listitem.h"

#include <QColor>

using namespace gui;

//! [0]
ListItem::ListItem(Effect *data, string label)
{
    itemData = data;
    itemLabel = label;
}
//! [0]

//! [1]
ListItem::~ListItem()
{
}
//! [1]

//! [6]
QVariant ListItem::data(int column) //const
{
    if (itemData != NULL) { //is root
        if (column == 0)
            return QVariant(itemData->toString());
        if (column == 1)
            return QVariant(QString(""));
    }
    return QVariant(QString(itemLabel.c_str()));
}
//! [6]


//! [11]
bool ListItem::setData(int column, const QVariant &value)
{
    //cout<< " set data: "<<column << &value ;
    if (column < 0 || column >= /*itemData.size()*/2)
        return false;

    if (itemData == NULL)
        return false;

    //itemData[column] = value;
    //itemData->setData(column, value);
    return true;
}
//! [11]

Effect* ListItem::getItemData(){
    return this->itemData;
}
