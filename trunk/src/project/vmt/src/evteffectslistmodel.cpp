#include <QtGui>
#include <QVariant>
#include "evteffectslistmodel.h"

using namespace gui;

//! [0]
evtEffectsListModel::evtEffectsListModel(VmtModel *vmtModel, QObject *parent)
    : QAbstractItemModel(parent)
{
    this->vmtModel = vmtModel;
    setupModelData();
}
//! [0]

//! [1]
evtEffectsListModel::~evtEffectsListModel()
{
    //delete rootItem;
}
//! [1]

//! [2]
void evtEffectsListModel::setupModelData()
{
    //beginInsertRows();
    QTime time;
    string formatori="hh:mm:ss";

    this->listItems.clear();
    map<string, string>::iterator evteffectsIt;
    map<string, string> evteffectsMap = this->vmtModel->getEvtEffects();
    for(evteffectsIt = evteffectsMap.begin(); evteffectsIt != evteffectsMap.end(); evteffectsIt++) {
        time = QTime::fromString(QString((evteffectsIt->second).c_str()), QString(formatori.c_str()));
        //cout<< "  datos evteffectitem "  <<evteffectsIt->first;
        evtEffectItem *lItem = new evtEffectItem(evteffectsIt->first, time );
        this->listItems.push_back(lItem);
    }

    emit layoutChanged();
    //endInsertRows();
}

VmtModel * evtEffectsListModel::getVmtModel(){
    return this->vmtModel;
}

QModelIndex evtEffectsListModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex evtEffectsListModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

QVariant evtEffectsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    evtEffectItem *item = getItem(index);

    return item->data(index.column());
}

evtEffectItem *evtEffectsListModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        evtEffectItem *item = this->listItems[index.row()];
        if (item) return item;
    }
    return getItem(QModelIndex());
}

int evtEffectsListModel::rowCount(const QModelIndex &parent) const
{
    return this->vmtModel->getEffects().size();
}

int evtEffectsListModel::columnCount(const QModelIndex & parent ) const
{
    return 1;
}
