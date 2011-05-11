#include <QtGui>

#include "additemdialog.h"
#include "treeitem.h"
#include "treemodel.h"
#include <limits>


using namespace gui;

//! [0]
addItemDialog::addItemDialog(string typeNodo)
{

    typeNodo = typeNodo;
    pathdata = new  QLineEdit();
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
void addItemDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Add"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Id/Name:")), idLineEdit);
    layout->addRow(new QLabel(tr("Path:")), pathdata);

    formGroupBox->setLayout(layout);
}
//! [12]

void addItemDialog::loadData(){



   if (typeNodo == "LIGHT"){
        pathdata->hide();
        idLineEdit->setText( "NewLight" );
    }
    if (typeNodo == "CAMERA"){
        pathdata->hide();
        idLineEdit->setText( "NewCamera" );
    }
    if (typeNodo == "OBJECTS" || typeNodo == "OBJECT"){

        idLineEdit->setText( "NewObject" );
    }
    if (typeNodo == "LAYER"){
        pathdata->hide();
        idLineEdit->setText( "NewLayer" );
    }
    if (typeNodo == "QUAD"){
        pathdata->hide();
        idLineEdit->setText( "NewQuad" );
    }





}


void addItemDialog::acceptPressed(){

    hide();
}

void addItemDialog::rejectPressed(){
    undoChanges();
    hide();
}

void addItemDialog::undoChanges(){

}
