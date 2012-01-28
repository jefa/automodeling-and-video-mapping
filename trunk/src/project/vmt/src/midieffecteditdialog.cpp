#include <QtGui>

#include "midieffecteditdialog.h"
#include "uiutils.h"
#include <limits>


using namespace gui;

//! [0]
midiEffecteditdialog::midiEffecteditdialog(VmtModel *vmtModel)
{
    this->vmtModel = vmtModel;


    idEffectEdit = new QLineEdit();
    idMidiEdit = new QLineEdit();

    valueMidiEdit = new QLineEdit();

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
void midiEffecteditdialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Add"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Id/Efect:")), idEffectEdit);
    layout->addRow(new QLabel(tr("Id MIDI:")), idMidiEdit);
    layout->addRow(new QLabel(tr("Value MIDI:")), valueMidiEdit);

    formGroupBox->setLayout(layout);
}
//! [12]

void midiEffecteditdialog::loadData(){

}


void midiEffecteditdialog::acceptPressed(){
    emit dataChanged();
    hide();
}

void midiEffecteditdialog::rejectPressed(){
    undoChanges();
    hide();
}

void midiEffecteditdialog::undoChanges(){
}

void midiEffecteditdialog::newMidiMessage(ofxMidiEventArgs& eventArgs){
    cout<<"midiEffecteditdialog::newMidiMessage"<<eventArgs.id <<" "<< eventArgs.value  << '\n';
    idMidiEdit->setText(QString(eventArgs.id));
    valueMidiEdit->setText(QString(eventArgs.value));

    cout<<"midiEffecteditdialog::datos"<<idMidiEdit->text().toInt()<<" "<< valueMidiEdit->text().toInt()  << '\n';



}
