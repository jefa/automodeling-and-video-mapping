#ifndef EFFECTSLISTWINDOW_H
#define EFFECTSLISTWINDOW_H

#include "VmtModel.h"

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

private slots:

private:
    void setupUi(QWidget *);
    void retranslateUi(QWidget *);

public:
    QVBoxLayout *vboxLayout;
    QGridLayout *layout;
    QListView *view;
};

}

#endif
