#ifndef MIDIEFFECTEDITDIALOG_H
#define MIDIEFFECTEDITDIALOG_H

#include <vmtmodel.h>

#include <QDoubleSpinBox>
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
#include <QTimeEdit>
#include <string>
#include <QModelIndex>

using namespace std;

namespace gui {

//! [0]
class midiEffecteditdialog : public QWidget
{
    Q_OBJECT

public:
    midiEffecteditdialog(VmtModel *vmtModel);

private slots:
    void acceptPressed();
    void rejectPressed();


Q_SIGNALS:
    void dataChanged();

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

    VmtModel *vmtModel;
    QLineEdit *idKeyEdit;
    QLineEdit *idLineEdit;


};
//! [0]

}

#endif
