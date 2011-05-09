#include <QtGui>

#include "nodeeditdialog.h"
#include <limits>

using namespace gui;

//! [0]
NodeEditorDialog::NodeEditorDialog(VmtModel *modelobj)
{
    this->model = modelobj;

    layerEnabledBox = new  QCheckBox();
    idLineEdit = new QLineEdit();

    loadData();

    createFormGroupBox();
//! [0]

//! [1]
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(acceptPressed()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(rejectPressed()));

    connect(layerEnabledBox, SIGNAL(clicked(bool)), this, SLOT(enabledChange(bool)));


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
    layout->addRow(new QLabel(tr("Is Enabled:")), layerEnabledBox);
    formGroupBox->setLayout(layout);
}
//! [12]

void NodeEditorDialog::loadData(){
  /*  Qt::CheckState state;
    state= Qt::Unchecked;
    if (this->model != NULL) {
        previousValueEnabled = this->model->getLayer2D(idLayer)->isEnabled();
        if (previousValueEnabled) {  state=Qt::Checked;}

        idLineEdit->setText(QString((this->layer2D->getName()).c_str()));

        layerEnabledBox->setCheckState(state);

    }*/
}

void NodeEditorDialog::enabledChange(bool newVal){
 /*   if (this->model != NULL)
        this->model->enableLayer(idCamera, idLayer, newVal);  */
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
