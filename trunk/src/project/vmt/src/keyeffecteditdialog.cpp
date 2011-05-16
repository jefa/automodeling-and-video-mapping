#include <QtGui>

#include "keyeffecteditdialog.h"
#include "uiutils.h"
#include <limits>


using namespace gui;

//! [0]
keyEffecteditdialog::keyEffecteditdialog(VmtModel *vmtModel)
{
    this->vmtModel = vmtModel;

    idLineEdit = new QLineEdit();
    idKeyEdit = new QLineEdit();


    loadData();

    createFormGroupBox();
//! [0]

//! [1]
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(acceptPressed()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(rejectPressed()));



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

    setWindowTitle(tr("Add"));

}
//! [5]

//! [12]
void keyEffecteditdialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Add"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Id/Efect:")), idLineEdit);
    layout->addRow(new QLabel(tr("Id Key:")), idKeyEdit);

    formGroupBox->setLayout(layout);
}
//! [12]

void keyEffecteditdialog::loadData(){

}


void keyEffecteditdialog::acceptPressed(){
    char key;// =((idKeyEdit->text()).toStdString()).c_ctr()[0];
    this->vmtModel->addKeyEvent(key, (idLineEdit->text()).toStdString());
    emit dataChanged();
    hide();
}

void keyEffecteditdialog::rejectPressed(){
    undoChanges();
    hide();
}

void keyEffecteditdialog::undoChanges(){
}
