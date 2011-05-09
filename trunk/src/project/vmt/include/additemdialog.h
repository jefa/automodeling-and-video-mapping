#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H



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
using namespace std;

namespace gui {

//! [0]
class addItemDialog : public QWidget
{
    Q_OBJECT

public:
    addItemDialog(string typeNodo);

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

    QLineEdit *pathdata;
    QLineEdit *idLineEdit;


    string typeNodo;



};
//! [0]

}

#endif
