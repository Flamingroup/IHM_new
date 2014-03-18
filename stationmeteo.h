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
            airTemperture,
            hailAccumulation,
            hailDuration,
            hailIntensity,
			heatTemperature=5,
            heatVoltage,
            rainAccumulation,
            rainDuration,
            rainIntensity,
            refVoltage=10,
            relativeHumidity,
            supplyVoltage,
            windDirectionAvrg,
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
            QColor(30,60,90)
        };
		StationMeteo(int idOrderMeteo = 5);
		~StationMeteo();
		std::string getOrderStation();
		Capteur* getCapt(TypeCapteur t);
        void setPlot(QwtPlot* plot);
		void saveData(std::ofstream& stream);
		void clear();
		int size();
};

#endif // STATIONMETEO_H
