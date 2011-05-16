#include "timeline.h"
#include <stdio.h>

timeline::timeline(VmtModel *vmtModel, QWidget *parent)
    : QWidget(parent)
{

    this->vmtModel = vmtModel;

	layout= new QVBoxLayout(this);

	progressBar = new QProgressBar(this);
	progressBar->setRange(0, 100);

    slider = new QSlider(Qt::Horizontal);
    slider->setMaximum(100);
    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(changePositionSlider(int)));

    timerLabel = new QLabel();
    timerLabel->setText("0");

	//  Construct a 5-second timeline with a frame range of 0 - 100
	timeLine = new QTimeLine(/*5000*/vmtModel->getTotalTime(), this);
	timeLine->setFrameRange(0, 100);
	connect(timeLine, SIGNAL(frameChanged(int)), progressBar, SLOT(setValue(int)));
	connect(timeLine, SIGNAL(frameChanged(int)), slider, SLOT(setValue(int)));


	// Clicking the push button will start the progress bar animation
	pushButton = new QPushButton(tr("Start"), this);
    pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	connect(pushButton, SIGNAL(clicked()), timeLine, SLOT(start()));
	connect(pushButton, SIGNAL(clicked()), this, SLOT(start()));

    connect(timeLine, SIGNAL(valueChanged(qreal)), this, SLOT(valueChanged(qreal)));
    connect(timeLine, SIGNAL(stateChanged(QTimeLine::State)), this, SLOT(stateChanged(QTimeLine::State)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(finished()));
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(frameChangedTimeline(int)));

	layout->addWidget(progressBar);
	layout->addWidget(timerLabel);
	layout->addWidget(slider);
	layout->addWidget(pushButton);
	setLayout(layout);
}

timeline::~timeline()
{
}

void timeline::valueChanged(qreal x){
    //printf("=== valueChanged: %f\n", x);
    //printf("\t=== valueChanged: %s\n", QString::number(x).toStdString().c_str());
    timerLabel->setText(QString::number(x));
}

void timeline::frameChangedTimeline(int frameCount){
    printf("=== frameChangedTimeline: %d\n", frameCount);
}

void timeline::stateChanged(QTimeLine::State newState){
    //printf("=== stateChanged: %d\n", newState);
}

void timeline::changePositionSlider(int pos){
    //printf("=== changePositionSlider: %d\n", pos);
}

void timeline::start(){
    //printf("=== START!!!\n");
    this->vmtModel->startTimeManager(ONE_TIME);
}

void timeline::finished(){
    //printf("=== FINISHED\n");
}
