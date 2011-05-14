#include <QtGui>

#include "cameraeditdialog.h"
#include <limits>

using namespace gui;

//! [0]
CameraEditorDialog::CameraEditorDialog(VmtModel *modelobj, string id)
{
    this->model = modelobj;
    cameraId = id;
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
    if (this->model != NULL) {
        Qt::CheckState state;
        state= Qt::Unchecked;
        ofxCamera *camera = this->model->getCameras()[cameraId];

        idLineEdit->setText(QString(cameraId.c_str()));
        idLineEdit->setReadOnly(true);

        previousprojector = camera->isProjector();
        if (previousprojector) {  state=Qt::Checked;}
        projector->setCheckState(state);

        previousX = camera->getPosition().x;
        previousY = camera->getPosition().y;
        previousZ = camera->getPosition().z;

        xCoordSpinBox->setValue(previousX);
        yCoordSpinBox->setValue(previousY);
        zCoordSpinBox->setValue(previousZ);

        previousEyeX = camera->getEye().x;
        previousEyeY = camera->getEye().y;
        previousEyeZ = camera->getEye().z;

        xCoordSpinEyeBox->setValue(previousEyeX);
        yCoordSpinEyeBox->setValue(previousEyeY);
        zCoordSpinEyeBox->setValue(previousEyeZ);

        previousUpX = camera->getUp().x;
        previousUpY = camera->getUp().y;
        previousUpZ = camera->getUp().z;

        xCoordSpinUpBox->setValue(previousUpX);
        yCoordSpinUpBox->setValue(previousUpY);
        zCoordSpinUpBox->setValue(previousUpZ);

        previousaspectRatio = camera->getaspectRatio();
        aspectRatio->setValue(previousaspectRatio);

        previousfieldOfView = camera->getfieldOfView();
        fieldOfView->setValue(previousfieldOfView);

        previouszFar = camera->getzFar();
        zFar->setValue(previouszFar);

        previouszNear = camera->getzNear();
        zNear->setValue(previouszNear);

        }

}

void CameraEditorDialog::xValueChanged(double newVal){
     if(this->model != NULL)
        this->model->setCameraPos(cameraId,newVal, previousY, previousZ);
}

void CameraEditorDialog::yValueChanged(double newVal){
     if(this->model != NULL)
        this->model->setCameraPos(cameraId,previousX, newVal, previousZ);
}

void CameraEditorDialog::zValueChanged(double newVal){
     if(this->model != NULL)
        this->model->setCameraPos(cameraId,previousX, previousY, newVal);
}

void CameraEditorDialog::xValueChangedEye(double newVal){
     if(this->model != NULL)
        this->model->setCameraEye(cameraId,newVal, previousEyeY, previousEyeZ);
}
void CameraEditorDialog::yValueChangedEye(double newVal){
     if(this->model != NULL)
        this->model->setCameraEye(cameraId,previousEyeX, newVal, previousEyeZ);
}
void CameraEditorDialog::zValueChangedEye(double newVal){
     if(this->model != NULL)
        this->model->setCameraEye(cameraId,previousEyeX, previousEyeY, newVal);
}
void CameraEditorDialog::xValueChangedUp(double newVal){
     if(this->model != NULL)
        this->model->setCameraUp(cameraId,newVal, previousUpY, previousUpZ);
}
void CameraEditorDialog::yValueChangedUp(double newVal){
     if(this->model != NULL)
        this->model->setCameraUp(cameraId,previousUpX, newVal, previousUpZ);
}
void CameraEditorDialog::zValueChangedUp(double newVal){
     if(this->model != NULL)
        this->model->setCameraUp(cameraId,previousUpX, previousUpY, newVal);
}

void CameraEditorDialog::fieldOfViewValueChanged(double newVal){
        if(this->model != NULL)
        this->model->setPerspective(cameraId, newVal, previousaspectRatio, previouszNear,previouszFar);
}
void CameraEditorDialog::aspectRatioValueChanged(double newVal){
        if(this->model != NULL)
        this->model->setPerspective(cameraId, previousfieldOfView, newVal, previouszNear,previouszFar);
}
void CameraEditorDialog::zNearValueChanged(double newVal){
        if(this->model != NULL)
        this->model->setPerspective(cameraId, previousfieldOfView, previousaspectRatio, newVal,previouszFar);
}
void CameraEditorDialog::zFarValueChanged(double newVal){
        if(this->model != NULL)
        this->model->setPerspective(cameraId, previousfieldOfView, previousaspectRatio, previouszNear,newVal);
}
void CameraEditorDialog::proyectorChange(bool newVal){
        if(this->model != NULL)
        this->model->setIsProjector(cameraId,newVal);
}


void CameraEditorDialog::acceptPressed(){
    if (this->model != NULL)
    this->model->setIsProjector(cameraId, projector->isChecked());
    hide();
}

void CameraEditorDialog::rejectPressed(){
    undoChanges();
    hide();
}

void CameraEditorDialog::undoChanges(){
    if (this->model != NULL) {
        this->model->setIsProjector(cameraId, previousprojector);
        this->model->setPerspective(cameraId, previousfieldOfView, previousaspectRatio, previouszNear,previouszFar);
        this->model->setCameraUp(cameraId,previousUpX, previousUpY, previousUpZ);
        this->model->setCameraEye(cameraId,previousEyeX, previousEyeY, previousEyeZ);
        this->model->setCameraPos(cameraId,previousX, previousY, previousZ);

    }
}
