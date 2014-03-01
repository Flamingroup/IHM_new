#ifndef STATIONMETEO_H
#define STATIONMETEO_H
#include <vector>
#include <ordermeteostation/ordermeteostation.h>
#include <capteurs/capteur.h>
#include <string>

class StationMeteo
{
	private:
		std::vector<OrderMeteoStation*> t_or;
		std::vector<Capteur*> t_capteursStation;
		int idOrderMeteo;
	public:
		enum TypeCapteur{
            airPressure=15,
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
		StationMeteo(int idOrderMeteo = 5);
		~StationMeteo();
		std::string getOrderStation();
		Capteur* getCapt(TypeCapteur t);
		void setPlot(QwtPlot* plot);
        void changeCurveColor(int nocapt, QColor newColor);
};

#endif // STATIONMETEO_H
