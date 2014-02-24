#include "capteur.h"

Capteur::Capteur()
{
}

void Capteur::addValue(double instantMesure, double value)
{
	times.append(new QPointF(instantMesure, value));
}

void Capteur::setColor(QColor nColor)
{
	color=nColor;
	QPen pen = curve.pen();
	pen.setColor(color);
	curve.setPen(pen);
}
