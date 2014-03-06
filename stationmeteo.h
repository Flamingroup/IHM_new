#ifndef STATIONMETEO_H
#define STATIONMETEO_H
#include <vector>
#include <capteurs/capteur.h>
#include <string>

class StationMeteo
{
	private:
		std::vector<Capteur*> t_capteursStation;
		int idOrderMeteo;
	public:
		enum TypeCapteur{
			airPressure=0,
			airTemperture=1,
			hailAccumulation=2,
			hailDuration=3,
			hailIntensity=4,
			heatTemperature=5,
			heatVoltage=6,
			rainAccumulation=7,
			rainDuration=8,
			rainIntensity=9,
			refVoltage=10,
			relativeHumidity=11,
			supplyVoltage=12,
			windDirectionAvrg=13,
			windSpeedAverage=14
        };
        QColor default_c[15]={
            QColor(Qt::blue),
            QColor(Qt::red),
            QColor(Qt::cyan),
            QColor(Qt::green),
            QColor(Qt::gray),
            QColor(Qt::magenta),
            QColor(Qt::yellow),
            QColor(Qt::darkBlue),
            QColor(Qt::darkCyan),
            QColor(Qt::darkGreen),
            QColor(Qt::darkMagenta),
            QColor(Qt::darkRed),
            QColor(Qt::darkYellow),
            QColor(Qt::darkGray),
            QColor(30,60,90,255)
        };
		StationMeteo(int idOrderMeteo = 5);
		~StationMeteo();
		std::string getOrderStation();
		Capteur* getCapt(TypeCapteur t);
        void setPlot(QwtPlot* plot);
};

#endif // STATIONMETEO_H
