#ifndef EVTEFFECTEDITDIALOG_H
#define EVTEFFECTEDITDIALOG_H



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
#include <string>
#include <QModelIndex>

using namespace std;

namespace gui {

//! [0]
class evtEffecteditdialog : public QWidget
{
    Q_OBJECT

public:
    evtEffecteditdialog();

private slots:
    void acceptPressed();
    void rejectPressed();


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

    QLineEdit *TimeBox;
    QLineEdit *idLineEdit;


};
//! [0]

}

#endif
