#include "uiutils.h"

#include <limits>

QDoubleSpinBox* UiUtils::createCoordinateSpinBox(){
    QDoubleSpinBox *coordSpinBox = new QDoubleSpinBox();
    coordSpinBox->setMouseTracking(true);
    coordSpinBox->setMaximum(numeric_limits<double>::max());
    coordSpinBox->setMinimum((numeric_limits<double>::max())*(-1));
    coordSpinBox->setSingleStep(.5);
    coordSpinBox->setMaximumWidth(70);
    return coordSpinBox;
}
