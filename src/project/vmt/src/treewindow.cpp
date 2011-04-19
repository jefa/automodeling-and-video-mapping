#include <QtGui>
#include <QCoreApplication>

#include "treewindow.h"
#include "treemodel.h"
#include "treeitem.h"
#include "colorlisteditor.h"
#include "objecteditdialog.h"

using namespace gui;


TreeWindow::TreeWindow(Scene *scene)
{
    setupUi(this);

    TreeModel *model = new TreeModel(scene, NULL);
    view->setModel(model);
    //for (int column = 0; column < model->columnCount(); ++column)
    //    view->resizeColumnToContents(column);
    view->setColumnWidth(0, 150);

    connect(exitAction, SIGNAL(clicked()), this, SLOT(quit()));
/*
    connect(view->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &,
                                    const QItemSelection &)),
            this, SLOT(updateActions()));
*/
    //connect(actionsMenu, SIGNAL(aboutToShow()), this, SLOT(updateActions()));
    connect(insertRowAction, SIGNAL(clicked()), this, SLOT(insertRow()));
    connect(insertColumnAction, SIGNAL(clicked()), this, SLOT(insertColumn()));
    connect(removeRowAction, SIGNAL(clicked()), this, SLOT(removeRow()));
    connect(removeColumnAction, SIGNAL(clicked()), this, SLOT(removeColumn()));
    connect(insertChildAction, SIGNAL(clicked()), this, SLOT(insertChild()));
    connect(editObjectAction, SIGNAL(clicked()), this, SLOT(editObject()));

    connect(view, SIGNAL(clicked(QModelIndex)), this, SLOT(clickedTree(QModelIndex)));

//    updateActions();
}
TreeWindow::~TreeWindow()
{
   // this->quit();
}
void TreeWindow::insertChild()
{
    QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }
/*
    if (!model->addElement(0, index))
        return;
*/
    for (int column = 0; column < model->columnCount(index); ++column) {
        QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"),
                                 Qt::EditRole);
    }

    view->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                            QItemSelectionModel::ClearAndSelect);
//    updateActions();
}

bool TreeWindow::insertColumn(const QModelIndex &parent)
{
    QAbstractItemModel *model = view->model();
    int column = view->selectionModel()->currentIndex().column();

    // Insert a column in the parent item.
    bool changed = model->insertColumn(column + 1, parent);
    if (changed)
        model->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"),
                             Qt::EditRole);

//    updateActions();

    return changed;
}

void TreeWindow::insertRow()
{
    QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();

    string TypeNodo;
    TypeNodo = ObtType(index);
    cout  << " TypeNodo : "<< TypeNodo;

    if (TypeNodo == "CAMERAS" || TypeNodo == "CAMERA" ){
        // add  Camera
    }
    if (TypeNodo == "OBJECTS" || TypeNodo == "OBJECT" ){
        // add  Object
    }
    if (TypeNodo == "LAYER" ){
        // add a Layer
    }
    if (TypeNodo == "QUAD" ){
        // add a Layer
    }
    QString name = inputText();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

//    updateActions();

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, /*QVariant("[No data]")*/name, Qt::EditRole);
    }
}

bool TreeWindow::removeColumn(const QModelIndex &parent)
{
    QAbstractItemModel *model = view->model();
    int column = view->selectionModel()->currentIndex().column();

    // Insert columns in each child of the parent item.
    bool changed = model->removeColumn(column, parent);

 //   if (!parent.isValid() && changed)
//        updateActions();

    return changed;
}

void TreeWindow::removeRow()
{
    QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();
 //   if (model->removeRow(index.row(), index.parent()))
//        updateActions();
}

string TreeWindow::ObtType(const QModelIndex &index)
{
    string TypeNodo;

    TreeModel *model = (TreeModel*) view->model();
    TreeItemData *itemData = model->getItem(index)->getItemData();
    if (itemData == NULL) {
           //cout<< "child number: "<<model->getItem(index)->childNumber();
           //0 CAMERAS  1 OBJECTS   2  Backgraund
           	switch(model->getItem(index)->childNumber())
                {
                case 0:TypeNodo = "CAMERAS";		 break;
                case 1:TypeNodo = "OBJECTS";		 break;
                case 2:TypeNodo = "BACKGRAUND";		 break;

                }
    }
    else{
      //  "CAMERA","LAYER", "QUAD","OBJECT"
       TreeItemData *itemData = model->getItem(index)->getItemData();
           	switch(itemData->itemId)
                {
                case 0:TypeNodo = "CAMERA";		 break;
                case 1:TypeNodo = "LAYER";		 break;
                case 2:TypeNodo = "QUAD";		 break;
                case 3:TypeNodo = "OBJECT";		 break;

                }
        }
    return TypeNodo;
}


void TreeWindow::updateActions(const QModelIndex &index)
{
//"CAMERAS", "OBJECTS","BACKGRAUND", "CAMERA","LAYER", "QUAD","OBJECT"
string TypeNodo;
    //printf("===== UPDATEACTIONS!!!\n");

        TypeNodo = ObtType(index);
        //cout  << " TypeNodo : "<< TypeNodo;

        if (TypeNodo == "CAMERAS")
        {
            editObjectAction->setEnabled(false);
            insertRowAction->setEnabled(true);
            removeRowAction->setEnabled(false);
        }
        if (TypeNodo == "CAMERA")
        {
            editObjectAction->setEnabled(true);
            insertRowAction->setEnabled(true);
            removeRowAction->setEnabled(true);
        }
        if (TypeNodo == "OBJECTS")
        {
            editObjectAction->setEnabled(false);
            insertRowAction->setEnabled(true);
            removeRowAction->setEnabled(false);
        }
        if (TypeNodo == "OBJECT")
        {
            editObjectAction->setEnabled(true);
            insertRowAction->setEnabled(true);
            removeRowAction->setEnabled(true);
        }
        if (TypeNodo == "BACKGRAUND" )
        {
            editObjectAction->setEnabled(true);
            insertRowAction->setEnabled(false);
            removeRowAction->setEnabled(false);
        }
        if (TypeNodo == "LAYER" )
        {
            editObjectAction->setEnabled(true);
            insertRowAction->setEnabled(true);
            removeRowAction->setEnabled(true);
        }
        if (TypeNodo == "QUAD" )
        {
            editObjectAction->setEnabled(true);
            insertRowAction->setEnabled(true);
            removeRowAction->setEnabled(true);
        }



/*    bool hasSelection = !view->selectionModel()->selection().isEmpty();
    removeRowAction->setEnabled(hasSelection);
    removeColumnAction->setEnabled(hasSelection);

    bool hasCurrent = view->selectionModel()->currentIndex().isValid();
    insertRowAction->setEnabled(hasCurrent);
    insertColumnAction->setEnabled(hasCurrent);

    if (hasCurrent) {
        view->closePersistentEditor(view->selectionModel()->currentIndex());

        int row = view->selectionModel()->currentIndex().row();
        int column = view->selectionModel()->currentIndex().column();
        if (view->selectionModel()->currentIndex().parent().isValid())
            statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
        else
            statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
    }*/



}

void TreeWindow::setupUi(QWidget *treeWindow)
{
    if (treeWindow->objectName().isEmpty())
        treeWindow->setObjectName(QString::fromUtf8("treeWindow"));
    treeWindow->resize(400, 400);
    treeWindow->move(20,20);
    exitAction = new QPushButton();
    exitAction->setObjectName(QString::fromUtf8("exitAction"));
    insertRowAction = new QPushButton();
    insertRowAction->setObjectName(QString::fromUtf8("insertRowAction"));
    insertRowAction->setEnabled(false);
    removeRowAction = new QPushButton();
    removeRowAction->setObjectName(QString::fromUtf8("removeRowAction"));
    removeRowAction->setEnabled(false);
    insertColumnAction = new QPushButton();
    insertColumnAction->setObjectName(QString::fromUtf8("insertColumnAction"));
    insertColumnAction->setEnabled(false);
    removeColumnAction = new QPushButton();
    removeColumnAction->setObjectName(QString::fromUtf8("removeColumnAction"));
    removeColumnAction->setEnabled(false);
    insertChildAction = new QPushButton();
    insertChildAction->setObjectName(QString::fromUtf8("insertChildAction"));
    insertChildAction->setEnabled(false);
    editObjectAction = new QPushButton();
    editObjectAction->setObjectName(QString::fromUtf8("editObjectAction"));
    editObjectAction->setEnabled(false);
    treeWindow->setObjectName(QString::fromUtf8("centralwidget"));
    vboxLayout = new QVBoxLayout(treeWindow);
    vboxLayout->setSpacing(0);
    vboxLayout->setContentsMargins(0, 0, 0, 0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    view = new QTreeView(treeWindow);
    view->setObjectName(QString::fromUtf8("view"));
    view->setAlternatingRowColors(true);
    view->setSelectionBehavior(QAbstractItemView::SelectItems);
    view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    view->setAnimated(false);
    view->setAllColumnsShowFocus(true);

    vboxLayout->addWidget(view);

    layout = new QGridLayout;
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(0,200);
    layout->setColumnMinimumWidth(1, 200);
    layout->addWidget(insertRowAction, 0, 1);
    layout->addWidget(removeRowAction, 1, 1);
    //layout->addWidget(insertColumnAction, 1, 0);
    //layout->addWidget(insertChildAction, 2, 0);
    layout->addWidget(editObjectAction, 0, 0);

    vboxLayout->addLayout(layout);
    vboxLayout->addWidget(exitAction);

    //treeWindow->setCentralWidget(centralwidget);
    //menubar = new QMenuBar(treeWindow);
    //menubar->setObjectName(QString::fromUtf8("menubar"));
    //menubar->setGeometry(QRect(0, 0, 573, 31));
    //fileMenu = new QMenu(menubar);
    //fileMenu->setObjectName(QString::fromUtf8("fileMenu"));
    //actionsMenu = new QMenu(menubar);
    //actionsMenu->setObjectName(QString::fromUtf8("actionsMenu"));
    //treeWindow->setMenuBar(menubar);
    //statusbar = new QStatusBar(treeWindow);
    //statusbar->setObjectName(QString::fromUtf8("statusbar"));
    //treeWindow->setStatusBar(statusbar);

    //menubar->addAction(fileMenu->menuAction());
    //menubar->addAction(actionsMenu->menuAction());
    //fileMenu->addAction(exitAction);
    //actionsMenu->addAction(insertRowAction);
    //actionsMenu->addAction(insertColumnAction);
    //actionsMenu->addSeparator();
    //actionsMenu->addAction(removeRowAction);
    //actionsMenu->addAction(removeColumnAction);
    //actionsMenu->addSeparator();
    //actionsMenu->addAction(insertChildAction);

    retranslateUi(treeWindow);

    //QMetaObject::connectSlotsByName(treeWindow);
} // setupUi

void TreeWindow::retranslateUi(QWidget *treeWindow)
{
    treeWindow->setWindowTitle(QApplication::translate("treeWindow", "ToolBar", 0, QApplication::UnicodeUTF8));
    exitAction->setText(QApplication::translate("treeWindow", "E&xit", 0, QApplication::UnicodeUTF8));
    exitAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
    insertRowAction->setText(QApplication::translate("treeWindow", "Add", 0, QApplication::UnicodeUTF8));
    insertRowAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+I, R", 0, QApplication::UnicodeUTF8));
    removeRowAction->setText(QApplication::translate("treeWindow", "Remove", 0, QApplication::UnicodeUTF8));
    removeRowAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+R, R", 0, QApplication::UnicodeUTF8));
    insertColumnAction->setText(QApplication::translate("treeWindow", "Insert Column", 0, QApplication::UnicodeUTF8));
    insertColumnAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+I, C", 0, QApplication::UnicodeUTF8));
    removeColumnAction->setText(QApplication::translate("treeWindow", "Remove Column", 0, QApplication::UnicodeUTF8));
    removeColumnAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+R, C", 0, QApplication::UnicodeUTF8));
    insertChildAction->setText(QApplication::translate("treeWindow", "Insert Child", 0, QApplication::UnicodeUTF8));
    insertChildAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));

    editObjectAction->setText(QApplication::translate("treeWindow", "Edit", 0, QApplication::UnicodeUTF8));
    editObjectAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));

    //fileMenu->setTitle(QApplication::translate("treeWindow", "&File", 0, QApplication::UnicodeUTF8));
    //actionsMenu->setTitle(QApplication::translate("treeWindow", "&Actions", 0, QApplication::UnicodeUTF8));
} // retranslateUi

QString TreeWindow::inputText()
{
    qDebug("---- en input text...");
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    qDebug("---- en input text SALIDA=%s\n", text.toStdString().c_str());
    if (ok && !text.isEmpty())
        return text;

    return "no text";
}

void TreeWindow::clickedTree(const QModelIndex &index)
{
    TreeModel *model = (TreeModel*) view->model();
    model->getItem(index)->setSeleted(model->getScene());
    updateActions(index);
    /*
    TreeItemData *itemData = model->getItem(index)->getItemData();
    if (itemData != NULL) {
        cout<<"index "<< itemData->itemId;
        if (itemData->itemId == 0){ //es camara
            CameraItemData *cid = (CameraItemData*)itemData;
            string str = cid->getData(0).toString().toStdString();
            cout<<"\tcamaraID "<< str;

        }
    }*/
}

void TreeWindow::editObject()
{
    TreeModel *model = (TreeModel*) view->model();
    ObjectEditorDialog *d = new ObjectEditorDialog(model->getScene()->getActiveObject());
    d->show();
}

void TreeWindow::quit()
{


}

void registerColorItemEditorFactory(){
    QItemEditorFactory *factory = new QItemEditorFactory;

    QItemEditorCreatorBase *colorListCreator =
        new QStandardItemEditorCreator<ColorListEditor>();

    factory->registerEditor(QVariant::Color, colorListCreator);

    QItemEditorFactory::setDefaultFactory(factory);
}

