#include <QtGui>
#include <QCoreApplication>

#include "effectslistwindow.h"
#include "effectslistmodel.h"

using namespace gui;

EffectsListWindow::EffectsListWindow(VmtModel *vmtModel)
{
    this->selectedItem = NULL;

    setupUi(this);

    EffectsListModel *model = new EffectsListModel(vmtModel, NULL);
    view->setModel(model);

    connect(view, SIGNAL(clicked(QModelIndex)), this, SLOT(clickedList(QModelIndex)));
	connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClickedList(QModelIndex)));

    connect(newEffectAction, SIGNAL(clicked()), this, SLOT(newEffect()));
    connect(editEffectAction, SIGNAL(clicked()), this, SLOT(editEffect()));
    connect(removeEffectAction, SIGNAL(clicked()), this, SLOT(removeEffect()));
    connect(testEffectAction, SIGNAL(clicked()), this, SLOT(testEffect()));

}

EffectsListWindow::~EffectsListWindow()
{

}

void EffectsListWindow::setupUi(QWidget *listWindow)
{
    if (listWindow->objectName().isEmpty())
        listWindow->setObjectName(QString::fromUtf8("listWindow"));
    listWindow->resize(200, 450);
    listWindow->move(ofGetScreenWidth()-300,40);
    vboxLayout = new QVBoxLayout(listWindow);
    vboxLayout->setSpacing(0);
    vboxLayout->setContentsMargins(0, 0, 0, 0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    view = new QListView(listWindow);
    view->setObjectName(QString::fromUtf8("view"));
    view->setAlternatingRowColors(true);
    view->setSelectionBehavior(QAbstractItemView::SelectItems);
    view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    vboxLayout->addWidget(view);

    newEffectAction = new QPushButton();
    newEffectAction->setObjectName(QString::fromUtf8("newEffectAction"));
    editEffectAction = new QPushButton();
    editEffectAction->setObjectName(QString::fromUtf8("editEffectAction"));
    removeEffectAction = new QPushButton();
    removeEffectAction->setObjectName(QString::fromUtf8("removeEffectAction"));
    testEffectAction = new QPushButton();
    testEffectAction->setObjectName(QString::fromUtf8("testEffectAction"));

    layout = new QGridLayout;
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(0, 100);
    layout->setColumnMinimumWidth(1, 100);

    vboxLayout->addLayout(layout);
    vboxLayout->addWidget(newEffectAction);
    vboxLayout->addWidget(editEffectAction);
    vboxLayout->addWidget(removeEffectAction);
    vboxLayout->addWidget(testEffectAction);

    retranslateUi(listWindow);

} // setupUi

void EffectsListWindow::retranslateUi(QWidget *listWindow)
{
    listWindow->setWindowTitle(QApplication::translate("listWindow", "Effects", 0, QApplication::UnicodeUTF8));

    newEffectAction->setText(QApplication::translate("treeWindow", "New", 0, QApplication::UnicodeUTF8));
    editEffectAction->setText(QApplication::translate("treeWindow", "Edit", 0, QApplication::UnicodeUTF8));
    removeEffectAction->setText(QApplication::translate("treeWindow", "Remove", 0, QApplication::UnicodeUTF8));
    testEffectAction->setText(QApplication::translate("treeWindow", "Test", 0, QApplication::UnicodeUTF8));

} // retranslateUi


void EffectsListWindow::clickedList(const QModelIndex &index)
{
    EffectsListModel *model = (EffectsListModel*) view->model();
    EffectItem *item = model->getItem(index);
    //printf("CLICKED LIST:: %d, %d. EVENTTYPE=%d, EVENTID=%s\n", index.column(), index.row(),
    //       item->getItemData()->getType(), item->getItemData()->getId().c_str());
    this->selectedItem = item;
}

void EffectsListWindow::doubleClickedList(const QModelIndex &index)
{
    EffectsListModel *model = (EffectsListModel*) view->model();
    EffectItem *item = model->getItem(index);
    model->getVmtModel()->testEffect(item->getItemData()->getId());
}

void EffectsListWindow::newEffect(){
}

void EffectsListWindow::editEffect(){
    if (this->selectedItem == NULL)
        return;
}

void EffectsListWindow::removeEffect(){
    if (this->selectedItem == NULL)
        return;
}

void EffectsListWindow::testEffect(){
    if (this->selectedItem == NULL)
        return;

    getListViewModel()->getVmtModel()->testEffect(this->selectedItem->getItemData()->getId());
}

EffectsListModel* EffectsListWindow::getListViewModel(){
    return (EffectsListModel*) view->model();
}
