#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_panner.h>
#include <string>
#include <list>

using std::string;
using std::list;

class QwtPlotMarker;
class QwtPlotDirectPainter;

class Plot : public QwtPlot
{
    Q_OBJECT

public:
    Plot( QWidget * parent = NULL );
    virtual ~Plot();
    void updCurve(const float p);
    void saveCurve(string filepath);
    void clearCurve(void);
protected:
	QwtPlotPanner* panner;
    QVector<QPointF> m_points;
	float m_currentX; // a passer en double pour le temps.
    float m_pas;

	list<QwtPlotCurve*> m_curves;
};


#endif // PLOT_H
