#include <QtGui>

#include "objecteditdialog.h"
#include <limits>

using namespace gui;

//! [0]
ObjectEditorDialog::ObjectEditorDialog(Object3D *obj3d)
{
    object3d = obj3d;
    xCoordSpinBox = new QDoubleSpinBox();
    yCoordSpinBox = new QDoubleSpinBox();
    zCoordSpinBox = new QDoubleSpinBox();
    idLineEdit = new QLineEdit();

    xCoordSpinBox->setMouseTracking(true);
    xCoordSpinBox->setMaximum(numeric_limits<double>::max());
    xCoordSpinBox->setMinimum((numeric_limits<double>::max())*(-1));
    xCoordSpinBox->setSingleStep(.5);
    yCoordSpinBox->setMouseTracking(true);
    yCoordSpinBox->setMaximum(numeric_limits<double>::max());
    yCoordSpinBox->setMinimum((numeric_limits<double>::max())*(-1));
    yCoordSpinBox->setSingleStep(.5);
    zCoordSpinBox->setMouseTracking(true);
    zCoordSpinBox->setMaximum(numeric_limits<double>::max());
    zCoordSpinBox->setMinimum((numeric_limits<double>::max())*(-1));
    zCoordSpinBox->setSingleStep(.5);

    loadData();

    createFormGroupBox();
//! [0]

//! [1]
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(acceptPressed()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(rejectPressed()));

    connect(xCoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(xValueChanged(double)));
    connect(yCoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(yValueChanged(double)));
    connect(zCoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(zValueChanged(double)));

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

    setWindowTitle(tr("Object Properties"));

}
//! [5]

//! [12]
void ObjectEditorDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Object properties"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Id/Name:")), idLineEdit);
    layout->addRow(new QLabel(tr("Coord. X:")), xCoordSpinBox);
    layout->addRow(new QLabel(tr("Coord. Y:")), yCoordSpinBox);
    layout->addRow(new QLabel(tr("Coord. Z:")), zCoordSpinBox);
    formGroupBox->setLayout(layout);
}
//! [12]

void ObjectEditorDialog::loadData(){
    if (this->object3d != NULL) {
        previousId = this->object3d->getId();
        previousX = this->object3d->get(POS_X);
        previousY = this->object3d->get(POS_Y);
        previousZ = this->object3d->get(POS_Z);

        idLineEdit->setText(QString(previousId.c_str()));
        idLineEdit->setReadOnly(true);
        xCoordSpinBox->setValue(previousX);
        yCoordSpinBox->setValue(previousY);
        zCoordSpinBox->setValue(previousZ);

    }
}

void ObjectEditorDialog::xValueChanged(double newVal){
    if (this->object3d != NULL)
        this->object3d->set(POS_X, newVal);
}

void ObjectEditorDialog::yValueChanged(double newVal){
    if (this->object3d != NULL)
        this->object3d->set(POS_Y, newVal);
}

void ObjectEditorDialog::zValueChanged(double newVal){
    if (this->object3d != NULL)
        this->object3d->set(POS_Z, newVal);
}

void ObjectEditorDialog::acceptPressed(){
    if (this->object3d != NULL)
        this->object3d->setId((idLineEdit->text()).toStdString());
    hide();
}

void ObjectEditorDialog::rejectPressed(){
    undoChanges();
    hide();
}

void ObjectEditorDialog::undoChanges(){
    if (this->object3d != NULL) {
        this->object3d->setId(previousId);
        this->object3d->set(POS_X, previousX);
        this->object3d->set(POS_Y, previousY);
        this->object3d->set(POS_Z, previousZ);
    }
}
