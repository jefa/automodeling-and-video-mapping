#include <QtGui>

#include "objecteditdialog.h"

//! [0]
ObjectEditorDialog::ObjectEditorDialog()
{
    //createMenu();
    //createHorizontalGroupBox();
    //createGridGroupBox();
    createFormGroupBox();
//! [0]

//! [1]
    bigEditor = new QTextEdit;
    bigEditor->setPlainText(tr("This widget takes up all the remaining space "
                               "in the top-level layout."));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
//! [1]

//! [2]
    QVBoxLayout *mainLayout = new QVBoxLayout;
//! [2] //! [3]
    //mainLayout->setMenuBar(menuBar);
//! [3] //! [4]
    //mainLayout->addWidget(horizontalGroupBox);
    //mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(bigEditor);
    mainLayout->addWidget(buttonBox);
//! [4] //! [5]
    setLayout(mainLayout);

    setWindowTitle(tr("Basic Layouts"));
}
//! [5]

//! [12]
void ObjectEditorDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Form layout"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Line 1:")), new QLineEdit);
    layout->addRow(new QLabel(tr("Line 2, long text:")), new QComboBox);
    layout->addRow(new QLabel(tr("Line 3:")), new QSpinBox);
    formGroupBox->setLayout(layout);
}
//! [12]
