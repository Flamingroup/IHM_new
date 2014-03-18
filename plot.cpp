#include "plot.h"
#include <fstream>
#include <iostream>

Plot::Plot( QWidget *parent ):
    QwtPlot( parent )
{

	panner = new QwtPlotPanner(this->canvas());
	panner->setMouseButton(Qt::LeftButton);
    this->setAutoReplot(true);
	m_currentX = 0;
}

Plot::~Plot()
{
	delete panner;
}
