#ifndef TREEWINDOW_H
#define TREEWINDOW_H

#include "Scene.h"

#include <QModelIndex>
#include <QWidget>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>


class QAction;
class QTreeView;

namespace gui {

class TreeWindow : public QWidget
{
    Q_OBJECT

public:
    TreeWindow(Scene *scene);
    ~TreeWindow();
    QString inputText();

public slots:
    void updateActions(const QModelIndex &index = QModelIndex());
    void clickedTree(const QModelIndex &index);
    string ObtType(const QModelIndex &index);

private slots:
    void insertChild();
    bool insertColumn(const QModelIndex &parent = QModelIndex());
    void insertRow();
    bool removeColumn(const QModelIndex &parent = QModelIndex());
    void removeRow();
    void editObject();
    void quit();

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
