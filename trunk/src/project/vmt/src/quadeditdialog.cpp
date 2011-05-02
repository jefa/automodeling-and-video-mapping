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

    x2CoordSpinBox = new QDoubleSpinBox();
    y2CoordSpinBox = new QDoubleSpinBox();

    x3CoordSpinBox = new QDoubleSpinBox();
    y3CoordSpinBox = new QDoubleSpinBox();

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

    x2CoordSpinBox->setMouseTracking(true);
    x2CoordSpinBox->setMaximum(numeric_limits<double>::max());
    x2CoordSpinBox->setMinimum((numeric_limits<double>::max())*(-1));
    x2CoordSpinBox->setSingleStep(.5);

    y2CoordSpinBox->setMouseTracking(true);
    y2CoordSpinBox->setMaximum(numeric_limits<double>::max());
    y2CoordSpinBox->setMinimum((numeric_limits<double>::max())*(-1));
    y2CoordSpinBox->setSingleStep(.5);

    x3CoordSpinBox->setMouseTracking(true);
    x3CoordSpinBox->setMaximum(numeric_limits<double>::max());
    x3CoordSpinBox->setMinimum((numeric_limits<double>::max())*(-1));
    x3CoordSpinBox->setSingleStep(.5);

    y3CoordSpinBox->setMouseTracking(true);
    y3CoordSpinBox->setMaximum(numeric_limits<double>::max());
    y3CoordSpinBox->setMinimum((numeric_limits<double>::max())*(-1));
    y3CoordSpinBox->setSingleStep(.5);

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

    connect(x2CoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(x2ValueChanged(double)));
    connect(y2CoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(y2ValueChanged(double)));

    connect(x3CoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(x3ValueChanged(double)));
    connect(y3CoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(y3ValueChanged(double)));

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
    //layout->addRow(new QLabel(tr("Is Selected:")), selectedBox);
    layout->addRow(new QLabel(tr("Point 0 Coord. X:")), x0CoordSpinBox);
    layout->addRow(new QLabel(tr("Point 0 Coord. Y:")), y0CoordSpinBox);
    layout->addRow(new QLabel(tr("Point 1 Coord. X:")), x1CoordSpinBox);
    layout->addRow(new QLabel(tr("Point 1 Coord. Y:")), y1CoordSpinBox);
    layout->addRow(new QLabel(tr("Point 2 Coord. X:")), x2CoordSpinBox);
    layout->addRow(new QLabel(tr("Point 2 Coord. Y:")), y2CoordSpinBox);
    layout->addRow(new QLabel(tr("Point 3 Coord. X:")), x3CoordSpinBox);
    layout->addRow(new QLabel(tr("Point 3 Coord. Y:")), y3CoordSpinBox);

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

        previous2X = this->object2d->getPoint(2).x;
        previous2Y = this->object2d->getPoint(2).y;

        x2CoordSpinBox->setValue(previous2X);
        y2CoordSpinBox->setValue(previous2Y);

        previous3X = this->object2d->getPoint(3).x;
        previous3Y = this->object2d->getPoint(3).y;

        x3CoordSpinBox->setValue(previous3X);
        y3CoordSpinBox->setValue(previous3Y);

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
void QuadEditorDialog::x2ValueChanged(double newVal){
    if (this->object2d != NULL)
        this->object2d->setPoint(2, newVal, previous2Y);
}

void QuadEditorDialog::y2ValueChanged(double newVal){
    if (this->object2d != NULL)
        this->object2d->setPoint(2, previous2X, newVal);
}
void QuadEditorDialog::x3ValueChanged(double newVal){
    if (this->object2d != NULL)
        this->object2d->setPoint(3, newVal, previous3Y);
}

void QuadEditorDialog::y3ValueChanged(double newVal){
    if (this->object2d != NULL)
        this->object2d->setPoint(3, previous3X, newVal);
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
        this->object2d->setPoint(1, previous1X, previous1Y);
        this->object2d->setPoint(2, previous2X, previous2Y);
        this->object2d->setPoint(3, previous3X, previous3Y);
    }
}
