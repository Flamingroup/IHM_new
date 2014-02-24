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
		StationMeteo(int idOrderMeteo = 5);
		std::string getOrderStation();
};

#endif // STATIONMETEO_H
