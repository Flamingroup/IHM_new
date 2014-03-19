#include "stationmeteo.h"
#include "saveload.h"



StationMeteo::StationMeteo(int idOrderMeteo)
	:idOrderMeteo(idOrderMeteo)
{
	for (unsigned char i=0; i<15; ++i) {
		t_capteursStation.push_back(new Capteur());
        //default colors
		t_capteursStation[i]->setColor(default_c[i]);
		t_capteursStation[i]->setVisible(false);
		//test values
//		t_capteursStation[i]->addValue(5,2*i);
//		t_capteursStation[i]->addValue(20,3*i);
	}
	initMapUnite();
}

void StationMeteo::initMapUnite(){
	map_Unite[TypeCapteur::airPressure].append("Pa");
	map_Unite[TypeCapteur::airPressure].append("hPa");
	map_Unite[TypeCapteur::airPressure].append("bar");

	map_Unite[TypeCapteur::airTemperture].append("C");
	map_Unite[TypeCapteur::airTemperture].append("F");
	map_Unite[TypeCapteur::airTemperture].append("K");

	map_Unite[TypeCapteur::heatTemperature].append("C");
	map_Unite[TypeCapteur::heatTemperature].append("F");
	map_Unite[TypeCapteur::heatTemperature].append("K");

	map_Unite[TypeCapteur::heatVoltage].append("V");
	map_Unite[TypeCapteur::heatVoltage].append("mV");

	map_Unite[TypeCapteur::rainAccumulation].append("mm");
	map_Unite[TypeCapteur::rainAccumulation].append("in");

	map_Unite[TypeCapteur::refVoltage].append("V");
	map_Unite[TypeCapteur::refVoltage].append("mV");

	map_Unite[TypeCapteur::supplyVoltage].append("V");
	map_Unite[TypeCapteur::supplyVoltage].append("mV");
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

QStringList StationMeteo::getItem(StationMeteo::TypeCapteur t)
{
	return map_Unite[t];
}

void StationMeteo::saveData(std::ofstream& stream)
{
	int i=0;
	for(Capteur* c : t_capteursStation){
		SaveLoad::saveCapteur(c, stream, i);
		++i;
	}
}

void StationMeteo::clear()
{
	for (Capteur* c : t_capteursStation){
		c->clear();
	}
}

int StationMeteo::size()
{
	return t_capteursStation.size();
}
