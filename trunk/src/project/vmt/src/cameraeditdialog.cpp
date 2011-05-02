#include <QtGui>

#include "cameraeditdialog.h"
#include <limits>

using namespace gui;

//! [0]
CameraEditorDialog::CameraEditorDialog(ofxCamera *objcamera)
{
    camera = objcamera;
    xCoordSpinBox = new QDoubleSpinBox();
    yCoordSpinBox = new QDoubleSpinBox();
    zCoordSpinBox = new QDoubleSpinBox();

    xCoordSpinEyeBox = new QDoubleSpinBox();
    yCoordSpinEyeBox = new QDoubleSpinBox();
    zCoordSpinEyeBox = new QDoubleSpinBox();

    xCoordSpinUpBox = new QDoubleSpinBox();
    yCoordSpinUpBox = new QDoubleSpinBox();
    zCoordSpinUpBox = new QDoubleSpinBox();

    fieldOfView = new QDoubleSpinBox();
    aspectRatio = new QDoubleSpinBox();
    zNear = new QDoubleSpinBox();
    zFar = new QDoubleSpinBox();

    projector = new  QCheckBox();

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


    xCoordSpinEyeBox->setMouseTracking(true);
    xCoordSpinEyeBox->setMaximum(numeric_limits<double>::max());
    xCoordSpinEyeBox->setMinimum((numeric_limits<double>::max())*(-1));
    xCoordSpinEyeBox->setSingleStep(.5);

    yCoordSpinEyeBox->setMouseTracking(true);
    yCoordSpinEyeBox->setMaximum(numeric_limits<double>::max());
    yCoordSpinEyeBox->setMinimum((numeric_limits<double>::max())*(-1));
    yCoordSpinEyeBox->setSingleStep(.5);

    zCoordSpinEyeBox->setMouseTracking(true);
    zCoordSpinEyeBox->setMaximum(numeric_limits<double>::max());
    zCoordSpinEyeBox->setMinimum((numeric_limits<double>::max())*(-1));
    zCoordSpinEyeBox->setSingleStep(.5);

    xCoordSpinUpBox->setMouseTracking(true);
    xCoordSpinUpBox->setMaximum(numeric_limits<double>::max());
    xCoordSpinUpBox->setMinimum((numeric_limits<double>::max())*(-1));
    xCoordSpinUpBox->setSingleStep(.5);

    yCoordSpinUpBox->setMouseTracking(true);
    yCoordSpinUpBox->setMaximum(numeric_limits<double>::max());
    yCoordSpinUpBox->setMinimum((numeric_limits<double>::max())*(-1));
    yCoordSpinUpBox->setSingleStep(.5);

    zCoordSpinUpBox->setMouseTracking(true);
    zCoordSpinUpBox->setMaximum(numeric_limits<double>::max());
    zCoordSpinUpBox->setMinimum((numeric_limits<double>::max())*(-1));
    zCoordSpinUpBox->setSingleStep(.5);


    fieldOfView->setMouseTracking(true);
    fieldOfView->setMaximum(numeric_limits<double>::max());
    fieldOfView->setMinimum((numeric_limits<double>::max())*(-1));
    fieldOfView->setSingleStep(.5);

    aspectRatio->setMouseTracking(true);
    aspectRatio->setMaximum(numeric_limits<double>::max());
    aspectRatio->setMinimum((numeric_limits<double>::max())*(-1));
    aspectRatio->setSingleStep(.5);

    zNear->setMouseTracking(true);
    zNear->setMaximum(numeric_limits<double>::max());
    zNear->setMinimum((numeric_limits<double>::max())*(-1));
    zNear->setSingleStep(.5);

    zFar->setMouseTracking(true);
    zFar->setMaximum(numeric_limits<double>::max());
    zFar->setMinimum((numeric_limits<double>::max())*(-1));
    zFar->setSingleStep(.5);



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

    connect(xCoordSpinEyeBox, SIGNAL(valueChanged(double)), this, SLOT(xValueChangedEye(double)));
    connect(yCoordSpinEyeBox, SIGNAL(valueChanged(double)), this, SLOT(yValueChangedEye(double)));
    connect(zCoordSpinEyeBox, SIGNAL(valueChanged(double)), this, SLOT(zValueChangedEye(double)));

    connect(xCoordSpinUpBox, SIGNAL(valueChanged(double)), this, SLOT(xValueChangedUp(double)));
    connect(yCoordSpinUpBox, SIGNAL(valueChanged(double)), this, SLOT(yValueChangedUp(double)));
    connect(zCoordSpinUpBox, SIGNAL(valueChanged(double)), this, SLOT(zValueChangedUp(double)));

    connect(fieldOfView, SIGNAL(valueChanged(double)), this, SLOT(fieldOfViewValueChanged(double)));
    connect(aspectRatio, SIGNAL(valueChanged(double)), this, SLOT(aspectRatioValueChanged(double)));
    connect(zNear, SIGNAL(valueChanged(double)), this, SLOT(zNearValueChanged(double)));
    connect(zFar, SIGNAL(valueChanged(double)), this, SLOT(zFarValueChanged(double)));

    connect(projector, SIGNAL(clicked(bool)), this, SLOT(proyectorChange(bool)));


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

    setWindowTitle(tr("Camera Properties"));

}
//! [5]

//! [12]
void CameraEditorDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Camera properties"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Id/Name:")), idLineEdit);
    layout->addRow(new QLabel(tr("Position Coord. X:")), xCoordSpinBox);
    layout->addRow(new QLabel(tr("Position Coord. Y:")), yCoordSpinBox);
    layout->addRow(new QLabel(tr("Position Coord. Z:")), zCoordSpinBox);

    layout->addRow(new QLabel(tr("Eye Coord. X:")), xCoordSpinEyeBox);
    layout->addRow(new QLabel(tr("Eye Coord. Y:")), yCoordSpinEyeBox);
    layout->addRow(new QLabel(tr("Eye Coord. Z:")), zCoordSpinEyeBox);

    layout->addRow(new QLabel(tr("Up Coord. X:")), xCoordSpinUpBox);
    layout->addRow(new QLabel(tr("Up Coord. Y:")), yCoordSpinUpBox);
    layout->addRow(new QLabel(tr("Up Coord. Z:")), zCoordSpinUpBox);

    layout->addRow(new QLabel(tr("fieldOfView :")), fieldOfView);
    layout->addRow(new QLabel(tr("aspectRatio :")), aspectRatio);
    layout->addRow(new QLabel(tr("zNear :")), zNear);
    layout->addRow(new QLabel(tr("zFar :")), zFar);

    layout->addRow(new QLabel(tr("Is Proyector:")), projector);


    formGroupBox->setLayout(layout);
}
//! [12]

void CameraEditorDialog::loadData(){
    if (this->camera != NULL) {
        Qt::CheckState state;
        state= Qt::Unchecked;
        previousId = this->camera->getId();
        idLineEdit->setText(QString(previousId.c_str()));

        previousprojector = this->camera->isProjector();
        if (previousprojector) {  state=Qt::Checked;}
        projector->setCheckState(state);

        previousX = this->camera->getPosition().x;
        previousY = this->camera->getPosition().y;
        previousZ = this->camera->getPosition().z;

        xCoordSpinBox->setValue(previousX);
        yCoordSpinBox->setValue(previousY);
        zCoordSpinBox->setValue(previousZ);

        previousEyeX = this->camera->getEye().x;
        previousEyeY = this->camera->getEye().y;
        previousEyeZ = this->camera->getEye().z;

        xCoordSpinEyeBox->setValue(previousEyeX);
        yCoordSpinEyeBox->setValue(previousEyeY);
        zCoordSpinEyeBox->setValue(previousEyeZ);

        previousUpX = this->camera->getUp().x;
        previousUpY = this->camera->getUp().y;
        previousUpZ = this->camera->getUp().z;

        xCoordSpinUpBox->setValue(previousUpX);
        yCoordSpinUpBox->setValue(previousUpY);
        zCoordSpinUpBox->setValue(previousUpZ);

        previousaspectRatio = this->camera->getaspectRatio();
        aspectRatio->setValue(previousaspectRatio);

        previousfieldOfView = this->camera->getfieldOfView();
        fieldOfView->setValue(previousfieldOfView);

        previouszFar = this->camera->getzFar();
        zFar->setValue(previouszFar);

        previouszNear = this->camera->getzNear();
        zNear->setValue(previouszNear);

        }

}

void CameraEditorDialog::xValueChanged(double newVal){
     if(this->camera != NULL)
        this->camera->position(newVal, previousY, previousZ);
}

void CameraEditorDialog::yValueChanged(double newVal){
     if(this->camera != NULL)
        this->camera->position(previousX, newVal, previousZ);
}

void CameraEditorDialog::zValueChanged(double newVal){
     if(this->camera != NULL)
        this->camera->position(previousX, previousY, newVal);
}

void CameraEditorDialog::xValueChangedEye(double newVal){
     if(this->camera != NULL)
        this->camera->eye(newVal, previousEyeY, previousEyeZ);
}
void CameraEditorDialog::yValueChangedEye(double newVal){
     if(this->camera != NULL)
        this->camera->eye(previousEyeX, newVal, previousEyeZ);
}
void CameraEditorDialog::zValueChangedEye(double newVal){
    if(this->camera != NULL)
        this->camera->eye(previousEyeX, previousEyeY, newVal);
}
void CameraEditorDialog::xValueChangedUp(double newVal){
    if(this->camera != NULL)
        this->camera->up(newVal, previousUpY, previousUpZ);
}
void CameraEditorDialog::yValueChangedUp(double newVal){
    if(this->camera != NULL)
        this->camera->up(previousUpX, newVal, previousUpZ);
}
void CameraEditorDialog::zValueChangedUp(double newVal){
    if(this->camera != NULL)
        this->camera->up(previousUpX, previousUpY, newVal);
}

void CameraEditorDialog::fieldOfViewValueChanged(double newVal){
        if(this->camera != NULL)
        this->camera->perspective(newVal, previousaspectRatio, previouszNear,previouszFar);
}
void CameraEditorDialog::aspectRatioValueChanged(double newVal){
        if(this->camera != NULL)
        this->camera->perspective(previousfieldOfView, newVal, previouszNear,previouszFar);
}
void CameraEditorDialog::zNearValueChanged(double newVal){
        if(this->camera != NULL)
        this->camera->perspective(previousfieldOfView, previousaspectRatio, newVal,previouszFar);
}
void CameraEditorDialog::zFarValueChanged(double newVal){
        if(this->camera != NULL)
        this->camera->perspective(previousfieldOfView, previousaspectRatio, previouszNear,newVal);
}
void CameraEditorDialog::proyectorChange(bool newVal){
        if(this->camera != NULL)
        this->camera->setIsProjector(newVal);
}


void CameraEditorDialog::acceptPressed(){
    if (this->camera != NULL)
    this->camera->setId((idLineEdit->text()).toStdString());
    this->camera->setIsProjector(projector->isChecked());
    hide();
}

void CameraEditorDialog::rejectPressed(){
    undoChanges();
    hide();
}

void CameraEditorDialog::undoChanges(){
    if (this->camera != NULL) {
        this->camera->setId(previousId);
        this->camera->setIsProjector(previousprojector);
        this->camera->perspective(previousfieldOfView, previousaspectRatio, previouszNear,previouszFar);
        this->camera->up(previousUpX, previousUpY, previousUpZ);
        this->camera->eye(previousEyeX, previousEyeY, previousEyeZ);
        this->camera->position(previousX, previousY, previousZ);
       // this->object3d->set(POS_Z, previousZ);
    }
}
