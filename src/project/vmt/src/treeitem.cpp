#include <QStringList>

#include "treeitem.h"

using namespace gui;

//! [0]
//TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent)
TreeItem::TreeItem(TreeItemData *data, TreeItem *parent)
{
    parentItem = parent;
    itemData = data;
}
//! [0]

//! [1]
TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}
//! [1]

//! [2]
TreeItem *TreeItem::child(int number)
{
    return childItems.value(number);
}
//! [2]

//! [3]
int TreeItem::childCount() const
{
    return childItems.count();
}
//! [3]

//! [4]
int TreeItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}
//! [4]

//! [5]
int TreeItem::columnCount() const
{
    return 2;//itemData.count();
}
//! [5]

//! [6]
QVariant TreeItem::data(int column) //const
{
    if (itemData == NULL) { //is root
        if (column == 0)
            return QVariant(QString("Escena"));
        if (column == 1)
            return QVariant(QString(""));
    }
    //return itemData.value(column);
    return itemData->getData(column);
}
//! [6]

//! [7]
/*bool TreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        TreeItem *item = new TreeItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}*/
//! [7]

//! [8]
/*bool TreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    foreach (TreeItem *child, childItems)
        child->insertColumns(position, columns);

    return true;
}*/
//! [8]

//! [9]
TreeItem *TreeItem::parent()
{
    return parentItem;
}
//! [9]

//! [10]
/*bool TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}*/
//! [10]

/*bool TreeItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.remove(position);

    foreach (TreeItem *child, childItems)
        child->removeColumns(position, columns);

    return true;
}*/

//! [11]
bool TreeItem::setData(int column, TreeItemData *value)
{
    if (column < 0 || column >= /*itemData.size()*/2)
        return false;

    //itemData[column] = value;
    itemData = value;
    return true;
}
//! [11]


LayerItemData::LayerItemData(Layer2D *layer2D){
    this->layer = layer2D;
}

LayerItemData::~LayerItemData(){
}

QVariant LayerItemData::getData(int column){
    if (column == 0)
        return QVariant(QString(this->layer->getName().c_str()));
    if (column == 1)
        return QVariant(this->layer->isEnabled());
    return QVariant(QString("no data"));
}

void LayerItemData::setData(int column, QVariant colValue){
}
