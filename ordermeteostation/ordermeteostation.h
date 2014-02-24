#ifndef ORDERMETEOSTATION_H
#define ORDERMETEOSTATION_H
#include <parseurs/retour/parseurretour.h>
#include <string>

class OrderMeteoStation
{
	protected:
		ParseurRetour* p;
		std::string order;
	public:
		OrderMeteoStation();
		virtual std::string getOrder();
};

#endif // ORDERMETEOSTATION_H
