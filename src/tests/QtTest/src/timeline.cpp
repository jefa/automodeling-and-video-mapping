#include "timeline.h"
#include <stdio.h>

timeline::timeline(QWidget *parent)
    : QWidget(parent)
{
	layout= new QVBoxLayout(this);

	progressBar = new QProgressBar(this);
	progressBar->setRange(0, 100);

    slider = new QSlider(Qt::Horizontal);
    slider->setMaximum(100);
    QObject::connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(changePositionSlider(int)));


	//  Construct a 5-second timeline with a frame range of 0 - 100
	timeLine = new QTimeLine(5000, this);
	timeLine->setFrameRange(0, 100);
    connect(timeLine, SIGNAL(frameChanged(int)), progressBar, SLOT(setValue(int)));
	connect(timeLine, SIGNAL(frameChanged(int)), slider, SLOT(setValue(int)));


	// Clicking the push button will start the progress bar animation
	pushButton = new QPushButton(tr("Start animation"), this);
	connect(pushButton, SIGNAL(clicked()), timeLine, SLOT(start()));

    connect(timeLine, SIGNAL(valueChanged(qreal)), this, SLOT(valueChanged(qreal)));
    connect(timeLine, SIGNAL(stateChanged(QTimeLine::State)), this, SLOT(stateChanged(QTimeLine::State)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(finished()));
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(frameChangedTimeline(int)));

	layout->addWidget(progressBar);
	layout->addWidget(slider);
	layout->addWidget(pushButton);
	setLayout(layout);
}

timeline::~timeline()
{
}

void timeline::valueChanged(qreal x){
    printf("=== valueChanged: %f\n", x);
}

void timeline::frameChangedTimeline(int frameCount){
    printf("=== frameChangedTimeline: %d\n", frameCount);
}

void timeline::stateChanged(QTimeLine::State newState){
    printf("=== stateChanged: %d\n", newState);
}

void timeline::finished(){
    printf("=== FINISHED\n");
}

void timeline::changePositionSlider(int pos){
    printf("=== changePositionSlider: %d\n", pos);
}
