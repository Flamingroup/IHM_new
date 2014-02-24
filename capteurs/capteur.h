#ifndef CAPTEUR_H
#define CAPTEUR_H
#include <QVector>
#include <QPoint>
#include <qwt_plot_curve.h>
#include <QObject>

class Capteur : public QObject
{
	private:
		QVector<QPointF*> times;
		QwtPlotCurve curve;
		QColor color;
	public:
		Capteur();
		void addValue(double instantMesure, double value);
		void setColor(QColor nColor);
};

#endif // CAPTEUR_H
