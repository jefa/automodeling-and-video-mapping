#ifndef LIGHTEDITORDIALOG_H
#define LIGHTEDITORDIALOG_H

#include "ofxLight.h"
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
class LightEditorDialog : public QWidget
{
    Q_OBJECT

public:
    LightEditorDialog(VmtModel *modelobj, string idlight);

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

    QCheckBox *onBox;
    QLineEdit *idLineEdit;

    string idlight;
    VmtModel *model;
    string previousId;
    bool previousValueON;

};
//! [0]

}

#endif
