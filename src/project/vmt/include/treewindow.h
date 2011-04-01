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

private slots:
    void insertChild();
    bool insertColumn(const QModelIndex &parent = QModelIndex());
    void insertRow();
    bool removeColumn(const QModelIndex &parent = QModelIndex());
    void removeRow();

private:
    void setupUi(QWidget *);
    void retranslateUi(QWidget *);

public:
    /*QAction*/QPushButton *exitAction;
    /*QAction*/QPushButton *insertRowAction;
    /*QAction*/QPushButton *removeRowAction;
    /*QAction*/QPushButton *insertColumnAction;
    /*QAction*/QPushButton *removeColumnAction;
    /*QAction*/QPushButton *insertChildAction;
    //QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QGridLayout *layout;
    QTreeView *view;
    //QMenuBar *menubar;
    //QMenu *fileMenu;
    //QMenu *actionsMenu;
    //QStatusBar *statusbar;
};

}

#endif
