#include "effectpages.h"
#include "Object3D.h"
#include "ofxVectorMath.h"
#include "uiutils.h"
#include <map>
#include <QtGui>

PositionEffectPage::PositionEffectPage(VmtModel *vmtModel, Effect *ef, QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *configGroup = new QGroupBox(tr("Apply to Object"));

    QLabel *serverLabel = new QLabel(tr("Id:"));
    QComboBox *serverCombo = new QComboBox;

    map<string, Object3D*>::iterator objects3DIt;
    map<string, Object3D*> objsMap = vmtModel->getObjects3D();
    for(objects3DIt = objsMap.begin(); objects3DIt != objsMap.end(); objects3DIt++) {
        Object3D *obj = (Object3D*) objects3DIt->second;
        serverCombo->addItem(tr(obj->getId().c_str()));
    }

    //Coordiantes panel
    QLabel *xLabel1 = new QLabel(tr("X:"));
    QLabel *xLabel2 = new QLabel(tr("X:"));
    QLabel *yLabel1 = new QLabel(tr("Y:"));
    QLabel *yLabel2 = new QLabel(tr("Y:"));
    QLabel *zLabel1 = new QLabel(tr("Z:"));
    QLabel *zLabel2 = new QLabel(tr("Z:"));
    QLabel *posIniLabel = new QLabel(tr("Ini:"));
    QDoubleSpinBox *xIniSpinBox = UiUtils::createCoordinateSpinBox();
    QDoubleSpinBox *yIniSpinBox = UiUtils::createCoordinateSpinBox();
    QDoubleSpinBox *zIniSpinBox = UiUtils::createCoordinateSpinBox();
    QLabel *posFinLabel = new QLabel(tr("Fin:"));
    QDoubleSpinBox *xFinSpinBox = UiUtils::createCoordinateSpinBox();
    QDoubleSpinBox *yFinSpinBox = UiUtils::createCoordinateSpinBox();
    QDoubleSpinBox *zFinSpinBox = UiUtils::createCoordinateSpinBox();


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
    QSpinBox *delaySpinBox = new QSpinBox;
    delaySpinBox->setPrefix(tr("Start after "));
    delaySpinBox->setSuffix(tr(" milliseconds"));
    delaySpinBox->setSpecialValueText(tr("Start immediatelly"));
    delaySpinBox->setMinimum(1);
    delaySpinBox->setMaximum(10000);
    delaySpinBox->setSingleStep(1);

    QVBoxLayout *delayLayout = new QVBoxLayout;
    delayLayout->addWidget(delaySpinBox);
    delayGroup->setLayout(delayLayout);

    QHBoxLayout *serverLayout = new QHBoxLayout;
    serverLayout->addWidget(serverLabel);
    serverLayout->addWidget(serverCombo);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(serverLayout);
    configGroup->setLayout(configLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addWidget(coordinatesGroup);
    mainLayout->addWidget(delayGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
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
