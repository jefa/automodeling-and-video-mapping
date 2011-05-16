#include <QtGui>

#include "evteffecteditdialog.h"
#include "uiutils.h"
#include <limits>


using namespace gui;

//! [0]
evtEffecteditdialog::evtEffecteditdialog(VmtModel *vmtModel)
{
    this->vmtModel = vmtModel;
    TimeBox = new QDoubleSpinBox();
    TimeBox->setMouseTracking(true);
    TimeBox->setMaximum(numeric_limits<double>::max());
    TimeBox->setMinimum((numeric_limits<double>::max())*(0));
    TimeBox->setSingleStep(1);
    TimeBox->setMaximumWidth(70);

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
    float timeShedule;
    timeShedule = TimeBox->value();
    this->vmtModel->scheduleEvent(timeShedule, (idLineEdit->text()).toStdString());

    emit dataChanged();

    hide();
}

void evtEffecteditdialog::rejectPressed(){
    undoChanges();
    hide();
}

void evtEffecteditdialog::undoChanges(){
}
