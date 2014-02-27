#include "capteur.h"

Capteur::Capteur()
{
}

void Capteur::addValue(double instantMesure, double value)
{
	times.append(QPointF(instantMesure, value));
	curve.setSamples(times);
}

void Capteur::setColor(QColor nColor)
{
	color=nColor;
	QPen pen = curve.pen();
	pen.setColor(color);
	curve.setPen(pen);
}

void Capteur::setVisible(bool b)
{
	curve.setVisible(b);
}

void Capteur::setPlot(QwtPlot* plot)
{
	curve.attach(plot);
	attached=true;
}

bool Capteur::isAttached()
{
	return attached;
}

Capteur::~Capteur()
{
	if (isAttached()){
		curve.detach();
	}
}
