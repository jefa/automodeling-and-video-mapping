#include <QtGui>
#include <QVariant>
#include "midieffectslistmodel.h"

using namespace gui;

//! [0]
midiEffectsListModel::midiEffectsListModel(VmtModel *vmtModel, QObject *parent)
    : QAbstractItemModel(parent)
{
    this->vmtModel = vmtModel;
    setupModelData();
}
//! [0]

//! [1]
midiEffectsListModel::~midiEffectsListModel()
{
    //delete rootItem;
}
//! [1]

//! [2]
void midiEffectsListModel::setupModelData()
{
    //beginInsertRows();
    this->listItems.clear();
    map<char, string>::iterator midieffectsIt;
    /*map<char, string> midieffectsMap = this->vmtModel->getMidiEffects();
    for(keyeffectsIt = keyeffectsMap.begin(); keyeffectsIt != keyeffectsMap.end(); keyeffectsIt++) {
        keyEffectItem *lItem = new keyEffectItem(keyeffectsIt->second, keyeffectsIt->first);
        this->listItems.push_back(lItem);
    }*/
    emit layoutChanged();
    //endInsertRows();
}

VmtModel * midiEffectsListModel::getVmtModel(){
    return this->vmtModel;
}

QModelIndex midiEffectsListModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex midiEffectsListModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

QVariant midiEffectsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    midiEffectItem *item = getItem(index);

    return item->data(index.column());
}

midiEffectItem *midiEffectsListModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        midiEffectItem *item = this->listItems[index.row()];
        if (item) return item;
    }
    return getItem(QModelIndex());
}

int midiEffectsListModel::rowCount(const QModelIndex &parent) const
{
    return this->vmtModel->getMidiEffects().size();
}

int midiEffectsListModel::columnCount(const QModelIndex & parent ) const
{
    return 1;
}
