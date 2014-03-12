#ifndef SAVELOAD_H
#define SAVELOAD_H

#include <capteurs/capteur.h>
#include <fstream>

using std::ofstream;

class SaveLoad
{
	public:
		SaveLoad();
		static void saveCapteur(Capteur* c, ofstream& stream, int numcapt);
};

#endif // SAVELOAD_H
