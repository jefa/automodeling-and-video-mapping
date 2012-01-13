#ifndef LAYEREDITORDIALOG_H
#define LAYEREDITORDIALOG_H

#include "Layer2D.h"
#include "vmtmodel.h"

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
#include <QCheckBox>
#include <QTextEdit>

namespace gui {

//! [0]
class LayerEditorDialog : public QWidget
{
    Q_OBJECT

public:
    LayerEditorDialog(VmtModel* modelobj, string Camera, string Layer);

private slots:
    void acceptPressed();
    void rejectPressed();
    void enabledChange(bool state);

private:
    void createFormGroupBox();
    void loadData();
    void undoChanges();

    enum { NumGridRows = 2, NumButtons = 2 };

    QGroupBox *formGroupBox;
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;

    QCheckBox *layerEnabledBox;
    QLineEdit *idLineEdit;

    VmtModel *model;
    Layer2D *layer2D;
    string idCamera, idLayer;
    bool previousValueEnabled;

};
//! [0]

}

#endif
