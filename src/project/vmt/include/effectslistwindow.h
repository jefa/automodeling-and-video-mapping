#ifndef EFFECTSLISTWINDOW_H
#define EFFECTSLISTWINDOW_H

#include "VmtModel.h"
#include "effectitem.h"
#include "effectslistmodel.h"

#include <QModelIndex>
#include <QWidget>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>

class QAction;
class QListView;

namespace gui {

class EffectsListWindow : public QWidget
{
    Q_OBJECT

public:
    EffectsListWindow(VmtModel *vmtModel);
    ~EffectsListWindow();

public slots:
    void clickedList(const QModelIndex &index);
    void doubleClickedList(const QModelIndex &index);
    void newEffect();
    void editEffect();
    void removeEffect();
    void testEffect();

private slots:

private:
    void setupUi(QWidget *);
    void retranslateUi(QWidget *);
    EffectsListModel* getListViewModel();

public:
    QVBoxLayout *vboxLayout;
    QGridLayout *layout;

    QPushButton *newEffectAction;
    QPushButton *editEffectAction;
    QPushButton *removeEffectAction;
    QPushButton *testEffectAction;

    QListView *view;

    EffectItem *selectedItem;
};

}

#endif
