#include "stationmeteo.h"

StationMeteo::StationMeteo(int idOrderMeteo)
	:idOrderMeteo(idOrderMeteo)
{
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
