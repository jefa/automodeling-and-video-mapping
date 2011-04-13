#include <QtGui>

#include "treewindow.h"
#include "treemodel.h"
#include "treeitem.h"
//#include "colorlisteditor.h"

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

    connect(view->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &,
                                    const QItemSelection &)),
            this, SLOT(updateActions()));

    //connect(actionsMenu, SIGNAL(aboutToShow()), this, SLOT(updateActions()));
    connect(insertRowAction, SIGNAL(clicked()), this, SLOT(insertRow()));
    connect(insertColumnAction, SIGNAL(clicked()), this, SLOT(insertColumn()));
    connect(removeRowAction, SIGNAL(clicked()), this, SLOT(removeRow()));
    connect(removeColumnAction, SIGNAL(clicked()), this, SLOT(removeColumn()));
    connect(insertChildAction, SIGNAL(clicked()), this, SLOT(insertChild()));
    connect(editObjectAction, SIGNAL(clicked()), this, SLOT(editObject()));

    connect(view, SIGNAL(clicked(QModelIndex)), this, SLOT(clickedTree(QModelIndex)));

    updateActions();
}

void TreeWindow::insertChild()
{
    QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {
        QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"),
                                 Qt::EditRole);
    }

    view->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                            QItemSelectionModel::ClearAndSelect);
    updateActions();
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

    updateActions();

    return changed;
}

void TreeWindow::insertRow()
{
    QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();

    QString name = inputText();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    updateActions();

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

    if (!parent.isValid() && changed)
        updateActions();

    return changed;
}

void TreeWindow::removeRow()
{
    QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();
}

void TreeWindow::updateActions()
{
    printf("===== UPDATEACTIONS!!!\n");
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
    treeWindow->resize(500, 400);
    treeWindow->move(10,10);
    exitAction = new QPushButton();
    exitAction->setObjectName(QString::fromUtf8("exitAction"));
    insertRowAction = new QPushButton();
    insertRowAction->setObjectName(QString::fromUtf8("insertRowAction"));
    removeRowAction = new QPushButton();
    removeRowAction->setObjectName(QString::fromUtf8("removeRowAction"));
    insertColumnAction = new QPushButton();
    insertColumnAction->setObjectName(QString::fromUtf8("insertColumnAction"));
    removeColumnAction = new QPushButton();
    removeColumnAction->setObjectName(QString::fromUtf8("removeColumnAction"));
    insertChildAction = new QPushButton();
    insertChildAction->setObjectName(QString::fromUtf8("insertChildAction"));
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
    //layout->setColumnMinimumWidth(1, 250);
    layout->addWidget(exitAction, 0, 0);
    layout->addWidget(insertRowAction, 0, 1);
    layout->addWidget(removeRowAction, 1, 0);
    layout->addWidget(insertColumnAction, 1, 1);
    layout->addWidget(insertChildAction, 2, 0);
    layout->addWidget(editObjectAction, 2, 1);

    vboxLayout->addLayout(layout);

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
    treeWindow->setWindowTitle(QApplication::translate("treeWindow", "Barra de herramientas", 0, QApplication::UnicodeUTF8));
    exitAction->setText(QApplication::translate("treeWindow", "E&xit", 0, QApplication::UnicodeUTF8));
    exitAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
    insertRowAction->setText(QApplication::translate("treeWindow", "Insert Row", 0, QApplication::UnicodeUTF8));
    insertRowAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+I, R", 0, QApplication::UnicodeUTF8));
    removeRowAction->setText(QApplication::translate("treeWindow", "Remove Row", 0, QApplication::UnicodeUTF8));
    removeRowAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+R, R", 0, QApplication::UnicodeUTF8));
    insertColumnAction->setText(QApplication::translate("treeWindow", "Insert Column", 0, QApplication::UnicodeUTF8));
    insertColumnAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+I, C", 0, QApplication::UnicodeUTF8));
    removeColumnAction->setText(QApplication::translate("treeWindow", "Remove Column", 0, QApplication::UnicodeUTF8));
    removeColumnAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+R, C", 0, QApplication::UnicodeUTF8));
    insertChildAction->setText(QApplication::translate("treeWindow", "Insert Child", 0, QApplication::UnicodeUTF8));
    insertChildAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));

    editObjectAction->setText(QApplication::translate("treeWindow", "Edit Object", 0, QApplication::UnicodeUTF8));
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
    printf("============== index: %d\n", index.row());

    //QStandardItem *item = myStandardItemModel->itemFromIndex(index);
    //TreeItem *item = view->model()->index(index.row(), index.column(), index.parent());
    TreeModel *model = (TreeModel*) view->model();
    TreeItem *item = model->getItem(index);
    item->setSeleted(model->getScene());
}

void registerColorItemEditorFactory(){
    QItemEditorFactory *factory = new QItemEditorFactory;

  //  QItemEditorCreatorBase *colorListCreator =
    //    new QStandardItemEditorCreator<ColorListEditor>();

//    factory->registerEditor(QVariant::Color, colorListCreator);

    QItemEditorFactory::setDefaultFactory(factory);
}

void editObject(){

}
