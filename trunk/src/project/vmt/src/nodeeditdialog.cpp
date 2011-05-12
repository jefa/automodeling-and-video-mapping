#include <QtGui>

#include "nodeeditdialog.h"
#include <limits>

using namespace gui;

//! [0]
NodeEditorDialog::NodeEditorDialog(VmtModel *modelobj, string idNode)
{
    this->model = modelobj;
    idNode = idNode;

    isActiveBox = new  QCheckBox();
    idLineEdit = new QLineEdit();
    addressEdit = new QLineEdit();
    cameraIdEdit =  new QLineEdit();
    portEdit =  new QLineEdit();

    loadData();

    createFormGroupBox();
//! [0]

//! [1]
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(acceptPressed()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(rejectPressed()));

    connect(isActiveBox, SIGNAL(clicked(bool)), this, SLOT(isActive(bool)));


//! [1]

//! [2]
    QVBoxLayout *mainLayout = new QVBoxLayout;
//! [2] //! [3]
    //mainLayout->setMenuBar(menuBar);
//! [3] //! [4]
    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(buttonBox);

//! [4] //! [5]
    setLayout(mainLayout);

    setWindowTitle(tr("Node Properties"));

}

//! [5]

//! [12]
void NodeEditorDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Node properties"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Id/Name:")), idLineEdit);
    layout->addRow(new QLabel(tr("Is Active:")), isActiveBox);
    layout->addRow(new QLabel(tr("Address:")), addressEdit);
    layout->addRow(new QLabel(tr("CameraId:")), cameraIdEdit);
    layout->addRow(new QLabel(tr("Port:")), portEdit);

    formGroupBox->setLayout(layout);
}
//! [12]

void NodeEditorDialog::loadData(){
    Node *node = this->model->getNode(idNode);
    idLineEdit->setText(QString(node->id.c_str()));
    idLineEdit->setReadOnly(true);
}

void NodeEditorDialog::isActive(bool newVal){
}

void NodeEditorDialog::acceptPressed(){

    hide();
}

void NodeEditorDialog::rejectPressed(){
    undoChanges();
    hide();
}

void NodeEditorDialog::undoChanges(){

}
