#include "evteffectslistwindow.h"

#include <QtGui>
#include <QCoreApplication>

using namespace gui;

evtEffectsListWindow::evtEffectsListWindow(VmtModel *vmtModel)
{
    this->selectedItem = NULL;
    this->evteffecteditdialog= new evtEffecteditdialog();

    setupUi(this);

    evtEffectsListModel *model = new evtEffectsListModel(vmtModel, NULL);
    view->setModel(model);

    connect(view, SIGNAL(clicked(QModelIndex)), this, SLOT(clickedList(QModelIndex)));
	connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClickedList(QModelIndex)));

	connect(evteffecteditdialog, SIGNAL(dataChanged()), this, SLOT(effectsChanged()));

    connect(newEffectAction, SIGNAL(clicked()), this, SLOT(newEffect()));
    connect(editEffectAction, SIGNAL(clicked()), this, SLOT(editEffect()));
    connect(removeEffectAction, SIGNAL(clicked()), this, SLOT(removeEffect()));

}

evtEffectsListWindow::~evtEffectsListWindow()
{
    delete(selectedItem);
    delete(evteffecteditdialog);
}

void evtEffectsListWindow::setupUi(QWidget *listWindow)
{
    if (listWindow->objectName().isEmpty())
        listWindow->setObjectName(QString::fromUtf8("listWindow2"));
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


    layout = new QGridLayout;
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(0, 100);
    layout->setColumnMinimumWidth(1, 100);

    vboxLayout->addLayout(layout);
    vboxLayout->addWidget(newEffectAction);
    vboxLayout->addWidget(editEffectAction);
    vboxLayout->addWidget(removeEffectAction);


    retranslateUi(listWindow);

} // setupUi

void evtEffectsListWindow::retranslateUi(QWidget *listWindow)
{
    listWindow->setWindowTitle(QApplication::translate("listWindow2", "TimeEvents-Effects", 0, QApplication::UnicodeUTF8));

    newEffectAction->setText(QApplication::translate("treeWindow", "New", 0, QApplication::UnicodeUTF8));
    editEffectAction->setText(QApplication::translate("treeWindow", "Edit", 0, QApplication::UnicodeUTF8));
    removeEffectAction->setText(QApplication::translate("treeWindow", "Remove", 0, QApplication::UnicodeUTF8));


} // retranslateUi


void evtEffectsListWindow::clickedList(const QModelIndex &index)
{
    evtEffectsListModel *model = (evtEffectsListModel*) view->model();
    this->selectedItem = model->getItem(index);
}

void evtEffectsListWindow::doubleClickedList(const QModelIndex &index)
{

    evteffecteditdialog->show();
}

void evtEffectsListWindow::newEffect(){

    evteffecteditdialog->show();
}

void evtEffectsListWindow::editEffect(){
    if (this->selectedItem == NULL)
        return;

    evteffecteditdialog->show();
}

void evtEffectsListWindow::removeEffect(){
    if (this->selectedItem == NULL)
        return;
}


evtEffectsListModel* evtEffectsListWindow::getListViewModel(){
    return (evtEffectsListModel*) view->model();
}

void evtEffectsListWindow::effectsChanged(){
    evtEffectsListModel *model = (evtEffectsListModel*) view->model();
    model->setupModelData();
    view->update();
    this->repaint();
}
