#ifndef STATIONMETEO_H
#define STATIONMETEO_H
#include <vector>
#include <ordermeteostation/ordermeteostation.h>

class StationMeteo
{
	private:
		std::vector<OrderMeteoStation*> t_or;
	public:
		StationMeteo();
};

#endif // STATIONMETEO_H
