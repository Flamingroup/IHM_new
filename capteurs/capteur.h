#ifndef CAPTEUR_H
#define CAPTEUR_H
#include <map>

class Capteur
{
	private:
		std::map<double, double> resultat;
		u_int16_t minvalue;
		u_int16_t maxvalue;
	public:
		Capteur();
};

#endif // CAPTEUR_H
