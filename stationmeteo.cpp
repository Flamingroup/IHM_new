#include "stationmeteo.h"
#include <ordermeteostation/order0r1.h>
#include <ordermeteostation/order0r2.h>
#include <ordermeteostation/order0r3.h>
#include <ordermeteostation/order0r5.h>

StationMeteo::StationMeteo(int idOrderMeteo)
	:idOrderMeteo(idOrderMeteo)
{
	t_or.push_back(new Order0R1);
	t_or.push_back(new Order0R2);
	t_or.push_back(new Order0R3);
	t_or.push_back(new Order0R5);
	for (char i = 0; i<15; ++i) {
		t_capteursStation.push_back(new Capteur());
		t_capteursStation[i]->setVisible(false);
	}

}

StationMeteo::~StationMeteo()
{
	for (Capteur* c : t_capteursStation){
		delete c;
	}
}

std::string StationMeteo::getOrderStation()
{
	return t_or[idOrderMeteo]->getOrder();
}

Capteur* StationMeteo::getCapt(TypeCapteur t)
{
	return t_capteursStation[t];
}

void StationMeteo::setPlot(QwtPlot* plot)
{
	for(Capteur* capteur : t_capteursStation){
		capteur->setPlot(plot);
	}
}
