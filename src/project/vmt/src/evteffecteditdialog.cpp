#include <QtGui>

#include "evteffecteditdialog.h"
#include <limits>


using namespace gui;

//! [0]
evtEffecteditdialog::evtEffecteditdialog()
{

    TimeBox = new  QTimeEdit();
    idLineEdit = new QLineEdit();


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
void evtEffecteditdialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Add"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Id/Efect:")), idLineEdit);
    layout->addRow(new QLabel(tr("Time:")), TimeBox);

    formGroupBox->setLayout(layout);
}
//! [12]

void evtEffecteditdialog::loadData(){


}


void evtEffecteditdialog::acceptPressed(){

    hide();
}

void evtEffecteditdialog::rejectPressed(){
    undoChanges();
    hide();
}

void evtEffecteditdialog::undoChanges(){

}
