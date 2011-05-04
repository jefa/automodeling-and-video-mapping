#ifndef BACKGRAUNDEDITORDIALOG_H
#define BACKGRAUNDEDITORDIALOG_H

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
#include <QColorDialog>

namespace gui {

//! [0]
class BackgraundEditorDialog : public QWidget
{
    Q_OBJECT

public:
    BackgraundEditorDialog(VmtModel *modelobj);

private slots:
    void acceptPressed();
    void rejectPressed();
    void enabledChange(QColor newVal);

private:
    void createFormGroupBox();
    void loadData();
    void undoChanges();

    enum { NumGridRows = 2, NumButtons = 1 };

    QGroupBox *formGroupBox;
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];

    QColorDialog* colorBox;

    VmtModel* model;
    int previousr, previousg, previousb;

};
//! [0]

}

#endif
