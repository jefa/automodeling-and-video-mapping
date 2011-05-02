#include <QtGui>
#include <QCoreApplication>

#include "effectslistwindow.h"
#include "effectslistmodel.h"

using namespace gui;

EffectsListWindow::EffectsListWindow(VmtModel *vmtModel)
{
    setupUi(this);

    EffectsListModel *model = new EffectsListModel(vmtModel, NULL);
    view->setModel(model);

    connect(view, SIGNAL(clicked(QModelIndex)), this, SLOT(clickedList(QModelIndex)));
	connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClickedList(QModelIndex)));
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

    layout = new QGridLayout;
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(0, 100);
    layout->setColumnMinimumWidth(1, 100);

    vboxLayout->addLayout(layout);

    retranslateUi(listWindow);

} // setupUi

void EffectsListWindow::retranslateUi(QWidget *listWindow)
{
    listWindow->setWindowTitle(QApplication::translate("listWindow", "Effects", 0, QApplication::UnicodeUTF8));
} // retranslateUi


void EffectsListWindow::clickedList(const QModelIndex &index)
{
/*    EffectsListModel *model = (EffectsListModel*) view->model();
    EffectItem *item = model->getItem(index);
    printf("CLICKED LIST:: %d, %d. EVENTTYPE=%d, EVENTID=%s\n", index.column(), index.row(),
           item->getItemData()->getType(), item->getItemData()->getId().c_str());
*/
}

void EffectsListWindow::doubleClickedList(const QModelIndex &index)
{
    EffectsListModel *model = (EffectsListModel*) view->model();
    EffectItem *item = model->getItem(index);

    //printf("\t DOUBLE CLICKED LIST::%d, %d. EVENTTYPE=%d, EVENTID=%s\n", index.column(), index.row(),
    //       item->getItemData()->getType(), item->getItemData()->getId().c_str());

    model->getVmtModel()->testEffect(item->getItemData()->getId());


}
