#include <QtGui>

#include "quadeditdialog.h"
#include <limits>

using namespace gui;

//! [0]
QuadEditorDialog::QuadEditorDialog(Quad2D *obj2D)
{
    object2d = obj2D;
    x0CoordSpinBox = new QDoubleSpinBox();
    y0CoordSpinBox = new QDoubleSpinBox();

    x1CoordSpinBox = new QDoubleSpinBox();
    y1CoordSpinBox = new QDoubleSpinBox();

    enabledBox = new  QCheckBox();
    selectedBox = new  QCheckBox();
    idLineEdit = new QLineEdit();

    x0CoordSpinBox->setMouseTracking(true);
    x0CoordSpinBox->setMaximum(numeric_limits<double>::max());
    x0CoordSpinBox->setMinimum((numeric_limits<double>::max())*(-1));
    x0CoordSpinBox->setSingleStep(.5);
    y0CoordSpinBox->setMouseTracking(true);
    y0CoordSpinBox->setMaximum(numeric_limits<double>::max());
    y0CoordSpinBox->setMinimum((numeric_limits<double>::max())*(-1));
    y0CoordSpinBox->setSingleStep(.5);

    x1CoordSpinBox->setMouseTracking(true);
    x1CoordSpinBox->setMaximum(numeric_limits<double>::max());
    x1CoordSpinBox->setMinimum((numeric_limits<double>::max())*(-1));
    x1CoordSpinBox->setSingleStep(.5);

    y1CoordSpinBox->setMouseTracking(true);
    y1CoordSpinBox->setMaximum(numeric_limits<double>::max());
    y1CoordSpinBox->setMinimum((numeric_limits<double>::max())*(-1));
    y1CoordSpinBox->setSingleStep(.5);

    loadData();

    createFormGroupBox();
//! [0]

//! [1]
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(acceptPressed()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(rejectPressed()));

    connect(x0CoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(x0ValueChanged(double)));
    connect(y0CoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(y0ValueChanged(double)));

    connect(x1CoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(x1ValueChanged(double)));
    connect(y1CoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(y1ValueChanged(double)));

    connect(enabledBox, SIGNAL(clicked(bool)), this, SLOT(enabledChanged(bool)));
    connect(selectedBox, SIGNAL(clicked(bool)), this, SLOT(selectedChanged(bool)));

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

    setWindowTitle(tr("Quad Properties"));

}
//! [5]

//! [12]
void QuadEditorDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Quad properties"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Id/Name:")), idLineEdit);
    layout->addRow(new QLabel(tr("Is Enabled:")), enabledBox);
    layout->addRow(new QLabel(tr("Is Selected:")), selectedBox);
    layout->addRow(new QLabel(tr("Point 0 Coord. X:")), x0CoordSpinBox);
    layout->addRow(new QLabel(tr("Point 0 Coord. Y:")), y0CoordSpinBox);
    layout->addRow(new QLabel(tr("Point 1 Coord. X:")), x1CoordSpinBox);
    layout->addRow(new QLabel(tr("Point 1 Coord. Y:")), y1CoordSpinBox);

    formGroupBox->setLayout(layout);
}
//! [12]

void QuadEditorDialog::loadData(){
    Qt::CheckState state;
    state= Qt::Unchecked;
    if (this->object2d != NULL) {
        previousId = this->object2d->getId();
        idLineEdit->setText(QString(previousId.c_str()));

        previousEnabled = this->object2d->isEnabled();
        if (previousEnabled) {  state=Qt::Checked;}
        enabledBox->setCheckState(state);

        state= Qt::Unchecked;
        previousSelected = this->object2d->isSelected();
        if (previousSelected) {  state=Qt::Checked;}
        selectedBox->setCheckState(state);


        previous0X = this->object2d->getPoint(0).x;
        previous0Y = this->object2d->getPoint(0).y;

        x0CoordSpinBox->setValue(previous0X);
        y0CoordSpinBox->setValue(previous0Y);

        previous1X = this->object2d->getPoint(1).x;
        previous1Y = this->object2d->getPoint(1).y;

        x1CoordSpinBox->setValue(previous1X);
        y1CoordSpinBox->setValue(previous1Y);

    }
}
void QuadEditorDialog::enabledChanged(bool newVal){
    if (this->object2d != NULL)
        this ->object2d->setEnabled(newVal);
}
void QuadEditorDialog::selectedChanged(bool newVal){
    if (this->object2d != NULL)
        this ->object2d->setSelected(newVal);
}
void QuadEditorDialog::x0ValueChanged(double newVal){
    if (this->object2d != NULL)
        this->object2d->setPoint(0, newVal, previous0Y);
}

void QuadEditorDialog::y0ValueChanged(double newVal){
    if (this->object2d != NULL)
        this->object2d->setPoint(0, previous0X, newVal);
}
void QuadEditorDialog::x1ValueChanged(double newVal){
    if (this->object2d != NULL)
        this->object2d->setPoint(1, newVal, previous1Y);
}

void QuadEditorDialog::y1ValueChanged(double newVal){
    if (this->object2d != NULL)
        this->object2d->setPoint(1, previous1X, newVal);
}


void QuadEditorDialog::acceptPressed(){
    this->object2d->setId((idLineEdit->text()).toStdString());
    this ->object2d->setEnabled(enabledBox->isChecked());
    this ->object2d->setSelected(selectedBox->isChecked());
    hide();
}

void QuadEditorDialog::rejectPressed(){
    undoChanges();
    hide();
}

void QuadEditorDialog::undoChanges(){
    if (this->object2d != NULL) {
        this->object2d->setId(previousId);
        this ->object2d->setEnabled(previousEnabled);
        this ->object2d->setSelected(previousSelected);
        this->object2d->setPoint(0, previous0X, previous0Y);
    }
}
