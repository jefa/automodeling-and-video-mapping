#ifndef TREEITEM_H
#define TREEITEM_H

#include "Layer2D.h"
#include "Quad2D.h"

#include <QList>
#include <QVariant>
#include <QVector>

using namespace std;

namespace gui {

class TreeItemData;

//! [0]
class TreeItem
{
public:
    TreeItem(TreeItemData *data = 0, TreeItem *parent = 0,
            string label = 0);
    ~TreeItem();

    TreeItem *child(int number);
    int childCount() const;
    //int columnCount() const;
    QVariant data(int column) /*const*/;
    bool insertChildren(int position, int count, /*int columns*/ TreeItemData *itemData, string label = 0 );
    //bool insertColumns(int position, int columns);
    TreeItem *parent();
    bool removeChildren(int position, int count);
    //bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, /*TreeItemData *value*/const QVariant &value);

private:
    string itemLabel;
    QList<TreeItem*> childItems;
    /*QVector<QVariant>*/TreeItemData *itemData;
    TreeItem *parentItem;
};
//! [0]

class TreeItemData {
    public:
    virtual QVariant getData(int column)=0;
    virtual void setData(int column, QVariant colValue)=0;
};

class LayerItemData : public TreeItemData {

    public:
    LayerItemData(Layer2D *layer2D);
    ~LayerItemData();

    QVariant getData(int column);
    void setData(int column, QVariant colValue);

    private:
    Layer2D *layer;
};

class ObjectItemData : public TreeItemData {

    public:
    ObjectItemData(Quad2D *quad2D);
    ~ObjectItemData();

    QVariant getData(int column);
    void setData(int column, QVariant colValue);

    private:
    Quad2D *quad;
};


}
#endif
