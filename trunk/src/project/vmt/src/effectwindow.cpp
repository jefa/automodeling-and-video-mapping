#include <QtGui>
#include <QCoreApplication>

#include "listwindow.h"
#include "listmodel.h"
//#include "treeitem.h"

using namespace gui;

ListWindow::ListWindow(VmtModel *vmtModel)
{
    setupUi(this);

    ListModel *model = new ListModel(vmtModel, NULL);
    view->setModel(model);

    connect(view, SIGNAL(clicked(QModelIndex)), this, SLOT(clickedList(QModelIndex)));
}

ListWindow::~ListWindow()
{

}

void ListWindow::setupUi(QWidget *listWindow)
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

void ListWindow::retranslateUi(QWidget *listWindow)
{
    listWindow->setWindowTitle(QApplication::translate("listWindow", "Effects", 0, QApplication::UnicodeUTF8));
} // retranslateUi


void ListWindow::clickedList(const QModelIndex &index)
{

}
