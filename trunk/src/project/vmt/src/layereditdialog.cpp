#include <QtGui>

#include "layereditdialog.h"
#include <limits>

using namespace gui;

//! [0]
LayerEditorDialog::LayerEditorDialog(Layer2D *lay2D)
{
    layer2D = lay2D;
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

    setWindowTitle(tr("Layer Properties"));

}
//! [5]

//! [12]
void LayerEditorDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Layer properties"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Id/Name:")), idLineEdit);
    layout->addRow(new QLabel(tr("Is Enabled:")), layerEnabledBox);
    formGroupBox->setLayout(layout);
}
//! [12]

void LayerEditorDialog::loadData(){
    Qt::CheckState state;
    state= Qt::Unchecked;
    if (this->layer2D != NULL) {
        previousId = this->layer2D->getName();
        previousValueEnabled = this->layer2D->isEnabled();
        if (previousValueEnabled) {  state=Qt::Checked;}

        idLineEdit->setText(QString(previousId.c_str()));
        layerEnabledBox->setCheckState(state);

    }
}

void LayerEditorDialog::enabledChange(bool newVal){
    if (this->layer2D != NULL)
        this->layer2D->setEnabled(newVal);
}

void LayerEditorDialog::acceptPressed(){
    if (this->layer2D != NULL)
        this->layer2D->setName((idLineEdit->text()).toStdString());
        this->layer2D->setEnabled(layerEnabledBox->isChecked());
    hide();
}

void LayerEditorDialog::rejectPressed(){
    undoChanges();
    hide();
}

void LayerEditorDialog::undoChanges(){
    if (this->layer2D != NULL) {
        this->layer2D->setName(previousId);
        this->layer2D->setEnabled(previousValueEnabled);

    }
}
