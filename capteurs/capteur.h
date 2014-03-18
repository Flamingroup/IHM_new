#ifndef CAPTEUR_H
#define CAPTEUR_H
#include <QVector>
#include <QPoint>
#include <qwt_plot_curve.h>
#include <QObject>

using std::ostream;

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

		void setColor(QColor nColor);
		void setVisible(bool b);
		void setPlot(QwtPlot* plot);

        bool isAttached() const;
        bool isVisible() const;
        QVector<QPointF>& getTimes();
        QColor getColor() const;
		void clear();
		~Capteur();
};

#endif // CAPTEUR_H
