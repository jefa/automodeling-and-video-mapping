#ifndef EFFECTPAGES_H
#define EFFECTPAGES_H

#include <QtGui>

class ProcessDialog : public QWidget
{
    Q_OBJECT

public:
    ProcessDialog(QWidget *parent = 0);
    void saveEffect();

public slots:
    void acceptPressed();
    void rejectPressed();
    void setOpenFileName();

private:
    void init();

    QDialogButtonBox *buttonBox;

    QLineEdit *filePathEdit;

    QPushButton *searchButton;
    QSpinBox *sampleNumSpinBox;
    QDoubleSpinBox *radiusSpinBox;
    QCheckBox *subsampleCheckBox;

    QSpinBox *neigborsSpinBox;
    QCheckBox *flipFlagCheckBox;

    QSpinBox *octdepthSpinBox;
    QSpinBox *solverdivideSpinBox;
    QDoubleSpinBox *samplespernodeSpinBox;
    QDoubleSpinBox *offsetSpinBox;

};

#endif
