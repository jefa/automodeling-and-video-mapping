#ifndef QUADEDITORDIALOG_H
#define QUADEDITORDIALOG_H

#include "Quad2D.h"

#include <QDialog>
#include <QAction>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QTextEdit>
#include <QCheckBox>
#include <QSlider>

namespace gui {

//! [0]
class QuadEditorDialog : public QWidget
{
    Q_OBJECT

public:
    QuadEditorDialog(Quad2D *obj2d);

private slots:
    void acceptPressed();
    void rejectPressed();
    void x0ValueChanged(double);
    void y0ValueChanged(double);

    void x1ValueChanged(double);
    void y1ValueChanged(double);

    void x2ValueChanged(double);
    void y2ValueChanged(double);

    void x3ValueChanged(double);
    void y3ValueChanged(double);

    void enabledChanged(bool);
    void selectedChanged(bool);

private:
    void createFormGroupBox();
    void loadData();
    void undoChanges();

    enum { NumGridRows = 3, NumButtons = 11 };

    QGroupBox *formGroupBox;
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;

    QDoubleSpinBox *x0CoordSpinBox;
    QDoubleSpinBox *y0CoordSpinBox;
    QDoubleSpinBox *x1CoordSpinBox;
    QDoubleSpinBox *y1CoordSpinBox;
    QDoubleSpinBox *x2CoordSpinBox;
    QDoubleSpinBox *y2CoordSpinBox;
    QDoubleSpinBox *x3CoordSpinBox;
    QDoubleSpinBox *y3CoordSpinBox;

    QLineEdit *idLineEdit;
    QCheckBox *enabledBox;
    QCheckBox *selectedBox;

    Quad2D *object2d;
    string previousId;
    float previous0X, previous0Y, previous1X, previous1Y, previous2X, previous2Y, previous3X, previous3Y;
    bool previousSelected,previousEnabled;

};
//! [0]

}

#endif
