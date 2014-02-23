#include "stationmeteo.h"
#include <ordermeteostation/order0r1.h>
#include <ordermeteostation/order0r2.h>
#include <ordermeteostation/order0r3.h>
#include <ordermeteostation/order0r5.h>

StationMeteo::StationMeteo()
{
	t_or.push_back(new Order0R1);
	t_or.push_back(new Order0R2);
	t_or.push_back(new Order0R3);
	t_or.push_back(new Order0R5);

}
