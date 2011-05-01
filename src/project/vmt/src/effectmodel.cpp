#include <QtGui>
#include <QVariant>
#include "listmodel.h"

using namespace gui;

//! [0]
ListModel::ListModel(VmtModel *vmtModel, QObject *parent)
    : QAbstractItemModel(parent)
{
    this->vmtModel = vmtModel;
    setupSceneModelData();
}
//! [0]

//! [1]
ListModel::~ListModel()
{
    //delete rootItem;
}
//! [1]

//! [2]
void ListModel::setupSceneModelData()
{
    map<string, Effect*>::iterator effectsIt;
    map<string, Effect*> effectsMap = this->vmtModel->getEffects();
    for(effectsIt = effectsMap.begin(); effectsIt != effectsMap.end(); effectsIt++) {
        ListItem *lItem = new ListItem(effectsIt->second, effectsIt->first);
        this->listItems.push_back(lItem);
    }
}

VmtModel * ListModel::getVmtModel(){
    return this->vmtModel;
}

QModelIndex ListModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex ListModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    ListItem *item = getItem(index);

    return item->data(index.column());
}

ListItem *ListModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        //ListItem *item = static_cast<ListItem*>(index.internalPointer());
        ListItem *item = this->listItems[index.row()];
        if (item) return item;
    }
    return getItem(QModelIndex());
}

int ListModel::rowCount(const QModelIndex &parent) const
{
    return this->vmtModel->getEffects().size();
}

int ListModel::columnCount(const QModelIndex & parent ) const
{
    return 1;
}
