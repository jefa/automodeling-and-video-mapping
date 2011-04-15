#include <QtGui>

#include "objecteditdialog.h"
//#include "Object3D.h"

using namespace gui;

//! [0]
ObjectEditorDialog::ObjectEditorDialog(Object3D *obj3d)
    //: QWidget(parent)
{
    object3d = obj3d;
    xCoordSpinBox = new QSpinBox();
    yCoordSpinBox = new QSpinBox();
    zCoordSpinBox = new QSpinBox();
    idLineEdit = new QLineEdit();
    textureComboBox = new QComboBox();

    //createMenu();
    //createHorizontalGroupBox();
    //createGridGroupBox();
    createFormGroupBox();
//! [0]

//! [1]
    //bigEditor = new QTextEdit;
    //bigEditor->setPlainText(tr("This widget takes up all the remaining space "
                               //"in the top-level layout."));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    connect(xCoordSpinBox, SIGNAL(valueChanged(int)), this, SLOT(xValueChanged(int)));
    connect(yCoordSpinBox, SIGNAL(valueChanged(int)), this, SLOT(yValueChanged(int)));
    connect(zCoordSpinBox, SIGNAL(valueChanged(int)), this, SLOT(zValueChanged(int)));

//! [1]

//! [2]
    QVBoxLayout *mainLayout = new QVBoxLayout;
//! [2] //! [3]
    //mainLayout->setMenuBar(menuBar);
//! [3] //! [4]
    //mainLayout->addWidget(horizontalGroupBox);
    //mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(formGroupBox);
    //mainLayout->addWidget(bigEditor);
    mainLayout->addWidget(buttonBox);
//! [4] //! [5]
    setLayout(mainLayout);

    setWindowTitle(tr("Basic Layouts"));

}
//! [5]

//! [12]
void ObjectEditorDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Object properties"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Id/Name:")), idLineEdit);
    layout->addRow(new QLabel(tr("Texture:")), textureComboBox);
    layout->addRow(new QLabel(tr("Coord. X:")), xCoordSpinBox);
    layout->addRow(new QLabel(tr("Coord. Y:")), yCoordSpinBox);
    layout->addRow(new QLabel(tr("Coord. Z:")), zCoordSpinBox);
    formGroupBox->setLayout(layout);
}
//! [12]

void ObjectEditorDialog::xValueChanged(int newVal){
    //printf("\tX CHANGED: %d\n", newVal);
    if (this->object3d != NULL)
        this->object3d->set(POS_X, newVal);
        //this->object3d->setPosition(newVal, 200, 200);
}

void ObjectEditorDialog::yValueChanged(int newVal){
    //printf("\tY CHANGED: %d\n", newVal);
    if (this->object3d != NULL)
        this->object3d->set(POS_Y, newVal);
}

void ObjectEditorDialog::zValueChanged(int newVal){
    //printf("\tZ CHANGED: %d\n", newVal);
    if (this->object3d != NULL)
        this->object3d->set(POS_Z, newVal);
}
