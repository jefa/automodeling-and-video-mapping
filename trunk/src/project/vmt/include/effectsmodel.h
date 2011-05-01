#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "listitem.h"
#include "VmtModel.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <vector>

namespace gui {

//! [0]
class ListModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ListModel(VmtModel *vmtModel, QObject *parent = 0);
    ~ListModel();

    QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const ;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const ;


    ListItem *getItem(const QModelIndex &index) const;
    VmtModel *getVmtModel();

private:
    void setupSceneModelData();

    VmtModel *vmtModel;
    vector<ListItem*> listItems;
};
//! [2]

}
#endif
