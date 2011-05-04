#include <QtGui>
#include <QVariant>
#include "treeitem.h"
#include "treemodel.h"

using namespace gui;

//! [0]
TreeModel::TreeModel(VmtModel *vmtModel, QObject *parent)
    : QAbstractItemModel(parent)
{
    this->vmtModel = vmtModel;
    setupSceneModelData();
    setupLayersModelData(rootItem->child(0));
    setupObjectsModelData(rootItem->child(1));
    setupLightsModelData(rootItem->child(2));
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
    //return 2;
    return rootItem->columnCount();
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

 bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
 {
     bool success;

     beginInsertColumns(parent, position, position + columns - 1);
     success = rootItem->insertColumns(position, columns);
     endInsertColumns();

     return success;
 }

string TreeModel::ObtType(const QModelIndex &index)
{
    string TypeNodo;

    TreeItemData *itemData = getItem(index)->getItemData();
    if (itemData == NULL) {
           //cout<< "child number: "<<model->getItem(index)->childNumber();
           //0 CAMERAS  1 OBJECTS   2  Backgraund
           	switch(getItem(index)->childNumber())
                {
                case 0:TypeNodo = "CAMERAS";		 break;
                case 1:TypeNodo = "OBJECTS";		 break;
                case 2:TypeNodo = "LIGHTS";		     break;
                case 3:TypeNodo = "BACKGRAUND";		 break;


                }
    }
    else{
      //  "CAMERA","LAYER", "QUAD","OBJECT"

           	switch(itemData->itemId)
                {
                case 0:TypeNodo = "CAMERA";		 break;
                case 1:TypeNodo = "LAYER";		 break;
                case 2:TypeNodo = "QUAD";		 break;
                case 3:TypeNodo = "OBJECT";		 break;
                case 4:TypeNodo = "LIGHT";		 break;

                }
        }
    return TypeNodo;
}


 bool TreeModel::insertRows(int position, int rows, const QModelIndex &index)
 {
     QModelIndex parent;
     parent = index.parent();
     TreeItem *parentItem = getItem(parent);
     TreeItem *currentItem = getItem(index);
     bool success;

    string TypeNodo;
    TypeNodo = ObtType(index);
    cout << " TypeNodo: "<< TypeNodo;
    beginInsertRows(parent, position, position + rows - 1);


    if (TypeNodo == "CAMERAS" ){
        // add  Camera
        this->vmtModel->addCamera("NewCamera");
        ofxCamera *newCamera = this->vmtModel->getCameras()["NewCamera"];
        //newCamera->set... ;
        CameraItemData *cameraItem = new CameraItemData(newCamera);

        success = currentItem->insertChildren(position, rows, cameraItem,"NewCamera");

    }
    if (TypeNodo == "LIGHTS" ){
        // add  light
        this->vmtModel->addLight("NewLight");
        ofxLight *newLight = this->vmtModel->getLight("NewLight");
        LightItemData *lightItem = new LightItemData(newLight);

        success = currentItem->insertChildren(position, rows, lightItem,"NewLight");

    }
    if (TypeNodo == "OBJECTS" || TypeNodo == "OBJECT" ){
        // add  Object

        QString path = "C:\ADRIANA\Proyecto\SVN_Proyecto\src\project\vmt\bin\data";
        this->vmtModel->addObject3D("NewObject", path.toStdString());
        Object3D *newObject = this->vmtModel->getObject3D("NewCamera");
        //newObject->set....;
        ObjectItemData *objectItem = new ObjectItemData(newObject);

        success = currentItem->insertChildren(position, rows, objectItem,"NewObject");
    }
    if (TypeNodo == "CAMERA"){
        // add a Layer

        Layer2D *newLayer = this->vmtModel->getActiveCamera()->addLayer2D("NewLayer");
        newLayer->setEnabled(false);
        LayerItemData *layerItem = new LayerItemData(newLayer);
        //cout<< " position  "<< position <<"   row " <<rows;
        success = currentItem->insertChildren(position, rows, layerItem,"NewLayer");
    }
    if ( TypeNodo == "LAYER"  || TypeNodo == "QUAD" ){
        // add a quad
        QVariant camId;
        QVariant layerId;
        string layerId2;
        string camId2;

            if (TypeNodo == "LAYER"){
                layerId = getItem(index)->getItemData()->getData(0);
                layerId2= layerId.toString().toStdString();

                camId = getItem(index.parent())->getItemData()->getData(0);
                camId2= camId.toString().toStdString();

            }
            else{
                layerId = getItem(index.parent())->getItemData()->getData(0);
                layerId2= layerId.toString().toStdString();

                camId = getItem(index.parent().parent())->getItemData()->getData(0);
                camId2= camId.toString().toStdString();

            }
                string quadId = "NewQuad";
                Quad2D *newQuad = this->vmtModel->getCameras()[camId2]->getLayer2D(layerId2)->addQuad2D(quadId);
                newQuad->setEnabled(false);
                QuadItemData *quadItem = new QuadItemData(newQuad);
                //cout<< " position  "<< position <<"   row " <<rows;
                if (TypeNodo == "QUAD"){
                    success = parentItem->insertChildren(position, rows, quadItem,"NewQuad");
                }
                else{
                    success = currentItem->insertChildren(position, rows, quadItem,"NewQuad");
                }


    }

     endInsertRows();

     return success;
 }

/*
bool TreeModel::addElement(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);

    Layer2D *newLayer = this->scene->getActiveCamera()->addLayer2D("New Layer");
    newLayer->setEnabled(false);
    LayerItemData *layerItemData = new LayerItemData(newLayer);

    success = parentItem->insertChildren(position, rows, /*rootItem->columnCount()*//* layerItemData);
    endInsertRows();

    return success;
}*/

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

bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
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

}

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

    map<string, ofxCamera*> camerasMap = this->vmtModel->getCameras();
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

            //vector<Quad2D*> quadsMap = currentLayer->getQuads2D();
            map<string, Quad2D*> quadsMap = currentLayer->getQuads2D();
            int positionQuad =0;
            //vector<Quad2D*>::iterator quadsIt;
            map<string, Quad2D*>::const_iterator quadsIt;
            for (quadsIt = quadsMap.begin(); quadsIt != quadsMap.end(); quadsIt++) {

                //Quad2D *currentQuad = (*quadsIt);
                Quad2D *currentQuad = quadsIt->second;
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
    rootItem->insertChildren(0, 1, NULL, "CAMERAS");
    rootItem->insertChildren(1, 1, NULL, "OBJECTS");
    rootItem->insertChildren(2, 1, NULL, "LIGHTS");
    rootItem->insertChildren(3, 1, NULL, "Background");

    //int positionScene = 0;
    //PropertyItemData *propItem = new PropertyItemData(currentQuad);
    //childItemLayer->insertChildren(positionScene, 1, propItem, "dummyquadstr");
    //positionScene++;

}

void TreeModel::setupObjectsModelData(TreeItem *parent)
{
    int positionObject = 0;
    map<string, Object3D*> objectsMap = this->vmtModel->getObjects3D();
    map<string, Object3D*>::iterator objectsIt;
    for(objectsIt = objectsMap.begin(); objectsIt != objectsMap.end(); objectsIt++) {
        Object3D* object = objectsIt->second;
        ObjectItemData *objectItem = new ObjectItemData(object);

        parent->insertChildren(positionObject, 1, objectItem, "");
        TreeItem *childItemObject = parent->child(positionObject);
        positionObject++;
    }
}


void TreeModel::setupLightsModelData(TreeItem *parent)
{
    int positionLight = 0;
    map<string, ofxLight*> lightsMap = this->vmtModel->getScene()->getLights();
    map<string, ofxLight*>::iterator lightsIt;
    for(lightsIt = lightsMap.begin(); lightsIt != lightsMap.end(); lightsIt++) {
        ofxLight* light = lightsIt->second;
        LightItemData *lightItem = new LightItemData(light);

        parent->insertChildren(positionLight, 1, lightItem, "");
        TreeItem *childItemLight = parent->child(positionLight);
        positionLight++;
    }
}


VmtModel * TreeModel::getVmtModel(){
return this->vmtModel;
}






