#ifndef TIMELINE_H
#define TIMELINE_H

#include <QtGui/QWidget>
//#include "ui_timeline.h"
#include <QVBoxLayout>
#include <QTimeLine>
#include <QProgressBar>
#include <QSlider>
#include <QPushButton>
class timeline : public QWidget
{
    Q_OBJECT

public:
	timeline(QWidget *parent = 0);
    ~timeline();

public slots:
    void valueChanged(qreal x);
    void frameChangedTimeline(int);
    void stateChanged(QTimeLine::State newState);
    void finished();

    void changePositionSlider(int);

private:
	QPushButton *pushButton;
	QTimeLine *timeLine;
	QProgressBar *progressBar;
	QSlider *slider;
    QVBoxLayout *layout;
};

#endif // TIMELINE_H
