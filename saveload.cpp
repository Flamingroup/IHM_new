#include "saveload.h"
#include <iostream>

SaveLoad::SaveLoad()
{
}

void SaveLoad::saveCapteur(Capteur* c, std::ofstream& stream, int numcapt)
{
	stream << numcapt << std::endl;
	for (QPointF point : c->getTimes()){
		stream << point.x() << ';' << point.y() << std::endl;
	}
	stream << std::endl;
}
