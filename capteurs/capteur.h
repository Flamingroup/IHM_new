#ifndef CAPTEUR_H
#define CAPTEUR_H
#include <QVector>
#include <QPoint>
#include <qwt_plot_curve.h>
#include <QObject>

class Capteur : public QObject
{
	private:
		QVector<QPointF> times;
		QwtPlotCurve curve;
		QColor color;
		bool attached = false;
	public:
		Capteur();
		void addValue(double instantMesure, double value);
        QColor getColor();
		void setColor(QColor nColor);
		void setVisible(bool b);
		void setPlot(QwtPlot* plot);
		bool isAttached();
		~Capteur();
};

#endif // CAPTEUR_H
