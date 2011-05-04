#include <QtGui>

#include "lighteditdialog.h"
#include <limits>

using namespace gui;

//! [0]
LightEditorDialog::LightEditorDialog(ofxLight *lightobj)
{
    light = lightobj;
    onBox = new  QCheckBox();
    idLineEdit = new QLineEdit();

    loadData();

    createFormGroupBox();
//! [0]

//! [1]
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(acceptPressed()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(rejectPressed()));

    connect(onBox, SIGNAL(clicked(bool)), this, SLOT(enabledChange(bool)));


//! [1]

//! [2]
    QVBoxLayout *mainLayout = new QVBoxLayout;
//! [2] //! [3]

//! [3] //! [4]
    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(buttonBox);

//! [4] //! [5]
    setLayout(mainLayout);

    setWindowTitle(tr("Light Properties"));

}
//! [5]

//! [12]
void LightEditorDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Light properties"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Id/Name:")), idLineEdit);
    layout->addRow(new QLabel(tr("ON:")), onBox);
    formGroupBox->setLayout(layout);
}
//! [12]

void LightEditorDialog::loadData(){
    Qt::CheckState state;
    state= Qt::Unchecked;
    if (this->light != NULL) {
        previousId = this->light->getId();
        previousValueON = this->light->ison();
        if (previousValueON) {  state=Qt::Checked;}

        idLineEdit->setText(QString(previousId.c_str()));
        onBox->setCheckState(state);

    }
}

void LightEditorDialog::enabledChange(bool newVal){
    if (this->light != NULL)
        if (newVal)   this->light->on();
        else this->light->off();

}

void LightEditorDialog::acceptPressed(){
    if (this->light != NULL)
        this->light->setId((idLineEdit->text()).toStdString());
        //if (onBox->isChecked()) this->light->on();
        //else this->light->off();

    hide();
}

void LightEditorDialog::rejectPressed(){
    undoChanges();
    hide();
}

void LightEditorDialog::undoChanges(){
    if (this->light != NULL) {
        this->light->setId(previousId);
        if (previousValueON)   this->light->on();
        else this->light->off();

    }
}
