#include <QtGui>

#include "treeitem.h"
#include "treemodel.h"

using namespace gui;

//! [0]
TreeModel::TreeModel(Scene *scene, QObject *parent)
    : QAbstractItemModel(parent)
{
    this->scene = scene;
    setupSceneModelData();
    setupLayersModelData(rootItem->child(0));
    //setupObjectsModelData(rootItem->child(1));
}
//! [0]

//! [1]
TreeModel::~TreeModel()
{
    delete rootItem;
}
//! [1]

//! [2]
int TreeModel::columnCount(const QModelIndex & parent ) const
{
    return 2; //rootItem->columnCount();
}
//! [2]

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem *item = getItem(index);

    return item->data(index.column());
}

//! [3]
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
//! [3]

//! [4]
TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    //qDebug("\t=== getItem: indexValid=%d, indexCol=%d, indexRow=%d\n", index.isValid(), index.column(), index.row());
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item) return item;
    }
    return rootItem;
}
//! [4]

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

//! [5]
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();
//! [5]

//! [6]
    TreeItem *parentItem = getItem(parent);

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}
//! [6]

/*bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}*/

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);

    Layer2D *newLayer = this->scene->getActiveCamera()->addLayer2D("New Layer");
    newLayer->setEnabled(false);
    LayerItemData *layerItemData = new LayerItemData(newLayer);

    success = parentItem->insertChildren(position, rows, /*rootItem->columnCount()*/ layerItemData);
    endInsertRows();

    return success;
}

//! [7]
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}
//! [7]

/*bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}*/

//! [8]
int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem = getItem(parent);

    return parentItem->childCount();
}
//! [8]

bool TreeModel::setData(const QModelIndex &index, const QVariant &value,
                        int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

void TreeModel::setupLayersModelData(TreeItem *parent)
{
    int positionCamera = 0;

    map<string, ofxCamera*> camerasMap = this->scene->getCameras();
    map<string, ofxCamera*>::iterator camerasIt;
    for(camerasIt = camerasMap.begin(); camerasIt != camerasMap.end(); camerasIt++) {
        ofxCamera* camera = camerasIt->second;
        CameraItemData *cameraItem = new CameraItemData(camera);

        parent->insertChildren(positionCamera, 1, cameraItem, "");
        TreeItem *childItemCamera = parent->child(positionCamera);

        int positionLayer = 0;

        map<string, Layer2D*> layersMap = camera->getLayers2D();
        map<string, Layer2D*>::iterator layersIt;
        for(layersIt = layersMap.begin(); layersIt != layersMap.end(); layersIt++) {

            Layer2D* currentLayer = layersIt->second;
            LayerItemData *layerItem = new LayerItemData(currentLayer);

            childItemCamera->insertChildren(positionLayer, 1, layerItem, "");
            TreeItem *childItemLayer = childItemCamera->child(positionLayer);

            vector<Quad2D*> quadsMap = currentLayer->getQuads2D();
            int positionQuad =0;
            vector<Quad2D*>::iterator quadsIt;
            for (quadsIt = quadsMap.begin(); quadsIt != quadsMap.end(); quadsIt++) {

                Quad2D *currentQuad = (*quadsIt);
                QuadItemData *quadItem = new QuadItemData(currentQuad);
                childItemLayer->insertChildren(positionQuad, 1, quadItem, "dummyquadstr");
                positionQuad++;
            }
            positionLayer++;
        }
    }
}

void TreeModel::setupSceneModelData()
{
    rootItem = new TreeItem(NULL, NULL, "Scene");
    rootItem->insertChildren(0, 1, NULL, "LAYERS");
    rootItem->insertChildren(1, 1, NULL, "OBJECTS");
    rootItem->insertChildren(2, 1, NULL, "Background");

    //int positionScene = 0;
    //PropertyItemData *propItem = new PropertyItemData(currentQuad);
    //childItemLayer->insertChildren(positionScene, 1, propItem, "dummyquadstr");
    //positionScene++;

}

void TreeModel::setupObjectsModelData(TreeItem *parent)
{
    int positionObject = 0;
    map<string, Object3D*> objectsMap = this->scene->getObjects3D();
    map<string, Object3D*>::iterator objectsIt;
    for(objectsIt = objectsMap.begin(); objectsIt != objectsMap.end(); objectsIt++) {
        Object3D* object = objectsIt->second;
        ObjectItemData *objectItem = new ObjectItemData(object);

        parent->insertChildren(positionObject, 1, objectItem, "");
        TreeItem *childItemObject = parent->child(positionObject);
        positionObject++;
    }
}

Scene* TreeModel::getScene(){
    return this->scene;
}
