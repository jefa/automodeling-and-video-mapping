#include <QtGui>

#include "keyeffecteditdialog.h"
#include "uiutils.h"
#include <limits>


using namespace gui;

//! [0]
keyEffecteditdialog::keyEffecteditdialog(VmtModel *vmtModel)
{
    this->vmtModel = vmtModel;

    idLineEdit = new QComboBox();
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
    map<string, Effect*>::iterator effectsIt;
    map<string, Effect*> effectsMap = this->vmtModel->getEffects();
    for(effectsIt = effectsMap.begin(); effectsIt != effectsMap.end(); effectsIt++) {
        idLineEdit->addItem(QString(effectsIt->second->getId().c_str()),QString(effectsIt->second->getId().c_str()));
    }
}


void keyEffecteditdialog::acceptPressed(){
    char * key;
    key =((idKeyEdit->text()).toLocal8Bit()).data() ;
    this->vmtModel->addKeyEvent(key[0], (idLineEdit->currentText()).toStdString());
    emit dataChanged();
    hide();
}

void keyEffecteditdialog::rejectPressed(){
    undoChanges();
    hide();
}

void keyEffecteditdialog::undoChanges(){
}
