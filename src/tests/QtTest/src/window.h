 #ifndef WINDOW_H
 #define WINDOW_H

 #include <QWidget>
 //#include "testApp.h"

 class QCheckBox;
 class QComboBox;
 class QGroupBox;
 class QLabel;
 class QSpinBox;
 class QStackedWidget;

 class SlidersGroup;

 class Window : public QWidget
 {
     Q_OBJECT

 public:
     Window();
     //Window(testApp *mainWindow );

 public slots:
    void sliderValueChanged(int);

 private:
     void createControls(const QString &title);

     SlidersGroup *horizontalSliders;
     SlidersGroup *verticalSliders;
     QStackedWidget *stackedWidget;

     QGroupBox *controlsGroup;
     QLabel *minimumLabel;
     QLabel *maximumLabel;
     QLabel *valueLabel;
     QCheckBox *invertedAppearance;
     QCheckBox *invertedKeyBindings;
     QSpinBox *minimumSpinBox;
     QSpinBox *maximumSpinBox;
     QSpinBox *valueSpinBox;
     QComboBox *orientationCombo;
 };

 #endif
