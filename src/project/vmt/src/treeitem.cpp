#include <QStringList>

#include "treeitem.h"

#include <QColor>

using namespace gui;

//! [0]
TreeItem::TreeItem(TreeItemData *data, TreeItem *parent, string label)
{
    parentItem = parent;
    itemData = data;
    itemLabel = label;
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
    TreeItem *retVal = childItems.value(number);
    if (retVal == NULL)
        qDebug("=== retVal NULL\n");
    return retVal;
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
    return 2;
    //return itemData.count();
}
//! [5]

//! [6]
QVariant TreeItem::data(int column) //const
{
    if (itemData == NULL) { //is root
        if (column == 0)
            return QVariant(QString(itemLabel.c_str()));
        if (column == 1)
            return QVariant(QString(""));
    }
    return itemData->getData(column);
}
//! [6]

//! [7]
bool TreeItem::insertChildren(int position, int count, /*int columns*/TreeItemData *itemData, string label )
{

    //qDebug("=== position:: %d\n", position);

    if (itemData == NULL)
        qDebug("=== itemData NULL\n");

    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        //QVector<QVariant> data(columns);
        TreeItem *item = new TreeItem(itemData, this, label);

        if (item  == NULL)
            qDebug("=== item  NULL\n");

        childItems.insert(position, item);
    }

    return true;
}
//! [7]

//! [8]
bool TreeItem::insertColumns(int position, int columns)
{
/*    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    foreach (TreeItem *child, childItems)
        child->insertColumns(position, columns);
*/
    return true;
}
//! [8]

//! [9]
TreeItem *TreeItem::parent()
{
    return parentItem;
}
//! [9]

//! [10]
bool TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}
//! [10]

bool TreeItem::removeColumns(int position, int columns)
{
/*    if (position < 0 || position + columns > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.remove(position);

    foreach (TreeItem *child, childItems)
        child->removeColumns(position, columns);
*/
    return true;
}

//! [11]
bool TreeItem::setData(int column, const QVariant &value)
{
    //cout<< " set data: "<<column << &value ;
    if (column < 0 || column >= /*itemData.size()*/2)
        return false;

    if (itemData == NULL)
        return false;

    //itemData[column] = value;
    itemData->setData(column, value);
    return true;
}
//! [11]


bool TreeItem::setSeleted(Scene *scene){

    if (this->itemData == NULL){
        return false;
    }

    return this->itemData->setSeleted(scene);

}

TreeItemData* TreeItem::getItemData(){
    return this->itemData;
}

CameraItemData::CameraItemData(ofxCamera *camera){
    this->itemId = 0;
    this->camera = camera;
}

CameraItemData::~CameraItemData(){
}

QVariant CameraItemData::getData(int column){
    //qDebug("CameraItemData::getData:: col=%d\n", column);
    if (column == 0)
        return QVariant(QString(this->camera->getId().c_str()));
    //if (column == 1)
    //    return QVariant(this->layer->isEnabled());  // poner llamado a la lista de layers
    return QVariant(QString("no data"));
}

void CameraItemData::setData(int column, QVariant colValue){
    //qDebug("CameraItemData::setData:: col=%d, value=%s\n", column, colValue.toString().toStdString().c_str());
    //if (column == 0)
    //    this->camera->setId(colValue.toString().toStdString());
    //if (column == 1)
    //    this->camera->setEnabled(colValue.toBool());
}

bool CameraItemData::setSeleted(Scene *scene){
    //activate camera
    ofxCamera *tmpCamera = scene->activateCamera(this->camera->getId());
    return (tmpCamera != NULL);
}

LayerItemData::LayerItemData(Layer2D *layer2D){
    this->itemId = 1;
    this->layer = layer2D;
}

LayerItemData::~LayerItemData(){
}

QVariant LayerItemData::getData(int column){
    //qDebug("LayerItemData::getData:: col=%d\n", column);
    if (column == 0)
        return QVariant(QString(this->layer->getName().c_str()));
    if (column == 1)
        return QVariant(this->layer->isEnabled());
    return QVariant(QString("no data"));
}

void LayerItemData::setData(int column, QVariant colValue){
    qDebug("LayerItemData::setData:: col=%d, value=%s\n", column, colValue.toString().toStdString().c_str());
    if (column == 0)
        this->layer->setName(colValue.toString().toStdString());
    if (column == 1)
        this->layer->setEnabled(colValue.toBool());
}

bool LayerItemData::setSeleted(Scene *scene){
    //activate layer
    return false;
}

QuadItemData::QuadItemData(Quad2D *quad2d){
    this->itemId = 2;
    this->quad2d = quad2d;
}

QuadItemData::~QuadItemData(){
}

QVariant QuadItemData::getData(int column){
    //qDebug("LayerItemData::getData:: col=%d\n", column);
    if (column == 0)
        return QVariant(QString(this->quad2d->getId().c_str()));
    if (column == 1)
        return QVariant(this->quad2d->isEnabled());
    return QVariant(QString("no data"));
}

void QuadItemData::setData(int column, QVariant colValue){
    qDebug("QuadItemData::setData:: col=%d, value=%s\n", column, colValue.toString().toStdString().c_str());
    if (column == 0)
        this->quad2d->setId(colValue.toString().toStdString());
    if (column == 1)
        this->quad2d->setEnabled(colValue.toBool());
}

bool QuadItemData::setSeleted(Scene *scene){
    //activate quad
    return false;
}

ObjectItemData::ObjectItemData(Object3D *object3d){
    this->itemId = 3;
    this->object3d = object3d;
}

ObjectItemData::~ObjectItemData(){
}

QVariant ObjectItemData::getData(int column){
    //qDebug("LayerItemData::getData:: col=%d\n", column);
    if (column == 0)
        return QVariant(QString(this->object3d->getId().c_str()));
    //if (column == 1)
        //return QVariant(this->quad->isEnabled());
    return QVariant(QString("no data"));
}

void ObjectItemData::setData(int column, QVariant colValue){
    qDebug("ObjectItemData::setData:: col=%d, value=%s\n", column, colValue.toString().toStdString().c_str());
    if (column == 0)
        this->object3d->setId(colValue.toString().toStdString());
    //if (column == 1)
        //this->quad->setEnabled(colValue.toBool());
}

bool ObjectItemData::setSeleted(Scene *scene){
    scene->activateObject(this->object3d->getId());
    return true;
}
