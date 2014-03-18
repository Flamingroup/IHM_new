#include "capteur.h"

Capteur::Capteur()
{
}

void Capteur::addValue(double instantMesure, double value)
{
    times.append(QPointF(instantMesure, value));
    curve.setSamples(times);
}

QColor Capteur::getColor() const
{
	return color;
}

void Capteur::clear()
{
	times.clear();
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

bool Capteur::isAttached() const
{
    return attached;
}

bool Capteur::isVisible() const
{
    return curve.isVisible();
}

QVector<QPointF>& Capteur::getTimes()
{
    return times;
}

Capteur::~Capteur()
{
	if (isAttached()){
		curve.detach();
	}
}
