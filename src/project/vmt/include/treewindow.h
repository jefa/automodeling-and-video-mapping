#ifndef TREEWINDOW_H
#define TREEWINDOW_H

#include "Scene.h"

#include <QModelIndex>
#include <QWidget>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QPushButton>

class QAction;
class QTreeView;

namespace gui {

class TreeWindow : public QWidget
{
    Q_OBJECT

public:
    TreeWindow(Scene *scene);
    QString inputText();

public slots:
    void updateActions();
    void clickedTree(const QModelIndex &index);

private slots:
    void insertChild();
    bool insertColumn(const QModelIndex &parent = QModelIndex());
    void insertRow();
    bool removeColumn(const QModelIndex &parent = QModelIndex());
    void removeRow();
    void editObject();

private:
    void setupUi(QWidget *);
    void retranslateUi(QWidget *);

public:
    QPushButton *exitAction;
    QPushButton *insertRowAction;
    QPushButton *removeRowAction;
    QPushButton *insertColumnAction;
    QPushButton *removeColumnAction;
    QPushButton *insertChildAction;
    QPushButton *editObjectAction;
    QVBoxLayout *vboxLayout;
    QGridLayout *layout;
    QTreeView *view;
};

}

#endif
