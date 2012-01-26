#ifndef MIDIEFFECTSLISTWINDOW_H
#define MIDIEFFECTSLISTWINDOW_H

#include "vmtmodel.h"
#include "midieffectitem.h"
#include "midieffectslistmodel.h"
#include "midieffecteditdialog.h"

#include <QModelIndex>
#include <QWidget>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QTime>
#include <QCoreApplication>

class QAction;
class QListView;

namespace gui {

class midiEffectsListWindow : public QWidget
{
    Q_OBJECT

public:
    midiEffectsListWindow(VmtModel *vmtModel);
    ~midiEffectsListWindow();

public slots:
    void effectsChanged();
    void clickedList(const QModelIndex &index);
    void doubleClickedList(const QModelIndex &index);
    void newEffect();
    void removeEffect();

private slots:

private:
    void setupUi(QWidget *);
    void retranslateUi(QWidget *);
    midiEffectsListModel* getListViewModel();

public:
    //QVBoxLayout *vboxLayout;

    QPushButton *newEffectAction;
    QPushButton *removeEffectAction;

    QListView *view;

    midiEffecteditdialog *midieffecteditdialog;

    midiEffectItem *selectedItem;
};

}

#endif
