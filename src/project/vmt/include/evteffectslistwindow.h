#ifndef EVTEFFECTSLISTWINDOW_H
#define EVTEFFECTSLISTWINDOW_H

#include "VmtModel.h"
#include "evteffectitem.h"
#include "evteffectslistmodel.h"
#include "evteffecteditdialog.h"
#include "timeline.h"

#include <QModelIndex>
#include <QWidget>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QTime>

class QAction;
class QListView;

namespace gui {

class evtEffectsListWindow : public QWidget
{
    Q_OBJECT

public:
    evtEffectsListWindow(VmtModel *vmtModel);
    ~evtEffectsListWindow();

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
    evtEffectsListModel* getListViewModel();

public:
    QVBoxLayout *vboxLayout;
    QGridLayout *layout;

    QPushButton *newEffectAction;
    QPushButton *removeEffectAction;

    QListView *view;

    evtEffecteditdialog *evteffecteditdialog;
    timeline *timeLine;

    evtEffectItem *selectedItem;
};

}

#endif
