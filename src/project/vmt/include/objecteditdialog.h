#ifndef OBJECTEDITORDIALOG_H
#define OBJECTEDITORDIALOG_H

#include "Object3D.h"

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
#include <QSpinBox>
#include <QTextEdit>

/*QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE*/

namespace gui {

//! [0]
class ObjectEditorDialog : public QWidget
{
    Q_OBJECT

public:
    ObjectEditorDialog(Object3D *obj3d);

private slots:
    void xValueChanged(int);
    void yValueChanged(int);
    void zValueChanged(int);

private:
    //void createMenu();
    //void createHorizontalGroupBox();
    //void createGridGroupBox();
    void createFormGroupBox();

    enum { NumGridRows = 3, NumButtons = 4 };

    //QMenuBar *menuBar;
    //QGroupBox *horizontalGroupBox;
    //QGroupBox *gridGroupBox;
    QGroupBox *formGroupBox;
    //QTextEdit *smallEditor;
    //QTextEdit *bigEditor;
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;

    //QMenu *fileMenu;
    //QAction *exitAction;

    QSpinBox *xCoordSpinBox;
    QSpinBox *yCoordSpinBox;
    QSpinBox *zCoordSpinBox;
    QLineEdit *idLineEdit;
    QComboBox *textureComboBox;

    Object3D *object3d;

};
//! [0]

}

#endif
