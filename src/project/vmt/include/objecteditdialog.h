#ifndef OBJECTEDITORDIALOG_H
#define OBJECTEDITORDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

//! [0]
class ObjectEditorDialog : public QWidget
{
    Q_OBJECT

public:
    ObjectEditorDialog();

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
    QTextEdit *smallEditor;
    QTextEdit *bigEditor;
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;

    QMenu *fileMenu;
    QAction *exitAction;
};
//! [0]

#endif
