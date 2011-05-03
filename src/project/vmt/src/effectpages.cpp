#include "effectpages.h"
#include "Object3D.h"
#include "ofxVectorMath.h"
#include "uiutils.h"
#include <map>

PositionEffectPage::PositionEffectPage(VmtModel *vmtModel, Effect *ef, QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *configGroup = new QGroupBox(tr("Configuration"));
    QLabel *effectIdLabel = new QLabel(tr("Effect Id:"));
    effectIdTxt = new QLineEdit;
    QLabel *objectIdLabel = new QLabel(tr("Object Id:"));
    objectCombo = new QComboBox;

    map<string, Object3D*>::iterator objects3DIt;
    map<string, Object3D*> objsMap = vmtModel->getObjects3D();
    for(objects3DIt = objsMap.begin(); objects3DIt != objsMap.end(); objects3DIt++) {
        Object3D *obj = (Object3D*) objects3DIt->second;
        objectCombo->addItem(tr(obj->getId().c_str()));
    }

    //Coordiantes panel
    QLabel *xLabel1 = new QLabel(tr("X:"));
    QLabel *xLabel2 = new QLabel(tr("X:"));
    QLabel *yLabel1 = new QLabel(tr("Y:"));
    QLabel *yLabel2 = new QLabel(tr("Y:"));
    QLabel *zLabel1 = new QLabel(tr("Z:"));
    QLabel *zLabel2 = new QLabel(tr("Z:"));
    QLabel *posIniLabel = new QLabel(tr("Ini:"));
    xIniSpinBox = UiUtils::createCoordinateSpinBox();
    yIniSpinBox = UiUtils::createCoordinateSpinBox();
    zIniSpinBox = UiUtils::createCoordinateSpinBox();
    QLabel *posFinLabel = new QLabel(tr("Fin:"));
    xFinSpinBox = UiUtils::createCoordinateSpinBox();
    yFinSpinBox = UiUtils::createCoordinateSpinBox();
    zFinSpinBox = UiUtils::createCoordinateSpinBox();

    QGroupBox *coordinatesGroup = new QGroupBox(tr("Coordinates"));
    QGridLayout *coordinatesLayout = new QGridLayout;
    coordinatesLayout->addWidget(posIniLabel, 0, 0);
    coordinatesLayout->addWidget(xLabel1, 0, 1);
    coordinatesLayout->addWidget(xIniSpinBox, 0, 2);
    coordinatesLayout->addWidget(yLabel1, 0, 3);
    coordinatesLayout->addWidget(yIniSpinBox, 0, 4);
    coordinatesLayout->addWidget(zLabel1, 0, 5);
    coordinatesLayout->addWidget(zIniSpinBox, 0, 6);
    coordinatesLayout->addWidget(posFinLabel, 1, 0);
    coordinatesLayout->addWidget(xLabel2, 1, 1);
    coordinatesLayout->addWidget(xFinSpinBox, 1, 2);
    coordinatesLayout->addWidget(yLabel2, 1, 3);
    coordinatesLayout->addWidget(yFinSpinBox, 1, 4);
    coordinatesLayout->addWidget(zLabel2, 1, 5);
    coordinatesLayout->addWidget(zFinSpinBox, 1, 6);

    coordinatesGroup->setLayout(coordinatesLayout);

    //Delay panel
    QGroupBox *delayGroup = new QGroupBox(tr("Delay"));
    delaySpinBox = new QDoubleSpinBox;
    delaySpinBox->setPrefix(tr("Start after "));
    delaySpinBox->setSuffix(tr(" milliseconds"));
    delaySpinBox->setSpecialValueText(tr("Start immediatelly"));
    //delaySpinBox->setMinimum(1);
    //delaySpinBox->setMaximum(10000);
    delaySpinBox->setSingleStep(.5);

    QVBoxLayout *delayLayout = new QVBoxLayout;
    delayLayout->addWidget(delaySpinBox);
    delayGroup->setLayout(delayLayout);

    QHBoxLayout *effectLayout = new QHBoxLayout;
    effectLayout->addWidget(effectIdLabel);
    effectLayout->addWidget(effectIdTxt);

    QHBoxLayout *objectLayout = new QHBoxLayout;
    objectLayout->addWidget(objectIdLabel);
    objectLayout->addWidget(objectCombo);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(effectLayout);
    configLayout->addLayout(objectLayout);
    configGroup->setLayout(configLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addWidget(coordinatesGroup);
    mainLayout->addWidget(delayGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    this->vmtModel = vmtModel;
    if (ef != NULL && ef->getType() == POSITION_EFFECT)
        this->effect = (PositionEffect*) ef;
    else
        this->effect = NULL;

    loadEffect();
}

void PositionEffectPage::loadEffect(){
    if (this->effect != NULL){

        effectIdTxt->setText(QString(effect->getId().c_str()));

        setComboIndexForText(objectCombo, effect->getObject3D()->getId());

        xIniSpinBox->setValue(effect->getPosIni()[0]);
        yIniSpinBox->setValue(effect->getPosIni()[1]);
        zIniSpinBox->setValue(effect->getPosIni()[2]);
        xFinSpinBox->setValue(effect->getPosFin()[0]);
        yFinSpinBox->setValue(effect->getPosFin()[1]);
        zFinSpinBox->setValue(effect->getPosFin()[2]);

        delaySpinBox->setValue(effect->getDelay());
    }
}

void setComboIndexForText(QComboBox *combo, string txt){
    for (int i=0; i < combo->count(); i++){
        if (combo->itemText(i).toStdString().compare(txt) == 0){
            combo->setCurrentIndex(i);
            break;
        }
    }
}

void PositionEffectPage::saveEffect(){
    if (this->effect == NULL){
        QString objId = objectCombo->currentText();

        /*printf("PositionEffectPage::saveEffect ADDING EFFECT. %s, %s, %f, %f, %f, %f, %f, %f, %f\n",
               effectIdTxt->text().toStdString().c_str(), objId.toStdString().c_str(),
               xIniSpinBox->value(), yIniSpinBox->value(), zIniSpinBox->value(),
               xFinSpinBox->value(), yFinSpinBox->value(), zFinSpinBox->value(),
               delaySpinBox->value());*/

        this->vmtModel->addPositionEffect(effectIdTxt->text().toStdString(), objId.toStdString(),
                                          ofxVec3f(xIniSpinBox->value(), yIniSpinBox->value(), zIniSpinBox->value()),
                                          ofxVec3f(xFinSpinBox->value(), yFinSpinBox->value(), zFinSpinBox->value()),
                                          delaySpinBox->value());
    } else {
        this->effect->setId(effectIdTxt->text().toStdString());
        this->effect->setPosIni(ofxVec3f(xIniSpinBox->value(), yIniSpinBox->value(), zIniSpinBox->value()));
        this->effect->setPosFin(ofxVec3f(xFinSpinBox->value(), yFinSpinBox->value(), zFinSpinBox->value()));
        this->effect->setDelay(delaySpinBox->value());
    }
}

FadeEffectPage::FadeEffectPage(VmtModel *vmtModel, Effect *ef, QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *updateGroup = new QGroupBox(tr("Package selection"));
    QCheckBox *systemCheckBox = new QCheckBox(tr("Update system"));
    QCheckBox *appsCheckBox = new QCheckBox(tr("Update applications"));
    QCheckBox *docsCheckBox = new QCheckBox(tr("Update documentation"));

    QGroupBox *packageGroup = new QGroupBox(tr("Existing packages"));

    QListWidget *packageList = new QListWidget;
    QListWidgetItem *qtItem = new QListWidgetItem(packageList);
    qtItem->setText(tr("Qt"));
    QListWidgetItem *qsaItem = new QListWidgetItem(packageList);
    qsaItem->setText(tr("QSA"));
    QListWidgetItem *teamBuilderItem = new QListWidgetItem(packageList);
    teamBuilderItem->setText(tr("Teambuilder"));

    QPushButton *startUpdateButton = new QPushButton(tr("Start update"));

    QVBoxLayout *updateLayout = new QVBoxLayout;
    updateLayout->addWidget(systemCheckBox);
    updateLayout->addWidget(appsCheckBox);
    updateLayout->addWidget(docsCheckBox);
    updateGroup->setLayout(updateLayout);

    QVBoxLayout *packageLayout = new QVBoxLayout;
    packageLayout->addWidget(packageList);
    packageGroup->setLayout(packageLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(updateGroup);
    mainLayout->addWidget(packageGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startUpdateButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

TextureEffectPage::TextureEffectPage(VmtModel *vmtModel, Effect *ef, QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *packagesGroup = new QGroupBox(tr("Look for packages"));

    QLabel *nameLabel = new QLabel(tr("Name:"));
    QLineEdit *nameEdit = new QLineEdit;

    QLabel *dateLabel = new QLabel(tr("Released after:"));
    QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate());

    QCheckBox *releasesCheckBox = new QCheckBox(tr("Releases"));
    QCheckBox *upgradesCheckBox = new QCheckBox(tr("Upgrades"));

    QSpinBox *hitsSpinBox = new QSpinBox;
    hitsSpinBox->setPrefix(tr("Return up to "));
    hitsSpinBox->setSuffix(tr(" results"));
    hitsSpinBox->setSpecialValueText(tr("Return only the first result"));
    hitsSpinBox->setMinimum(1);
    hitsSpinBox->setMaximum(100);
    hitsSpinBox->setSingleStep(10);

    QPushButton *startQueryButton = new QPushButton(tr("Start query"));

    QGridLayout *packagesLayout = new QGridLayout;
    packagesLayout->addWidget(nameLabel, 0, 0);
    packagesLayout->addWidget(nameEdit, 0, 1);
    packagesLayout->addWidget(dateLabel, 1, 0);
    packagesLayout->addWidget(dateEdit, 1, 1);
    packagesLayout->addWidget(releasesCheckBox, 2, 0);
    packagesLayout->addWidget(upgradesCheckBox, 3, 0);
    packagesLayout->addWidget(hitsSpinBox, 4, 0, 1, 2);
    packagesGroup->setLayout(packagesLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(packagesGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startQueryButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}
