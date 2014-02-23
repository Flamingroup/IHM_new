#include "parseurenvoi.h"
#include <QStringList>

ParseurEnvoi::ParseurEnvoi()
{
}

std::string ParseurEnvoi::parseToQstring(QString sToParse)
{
	QStringList s = sToParse.split(';');
	QStringList::Iterator moving = s.begin();
	for(;moving != s.end(); ++moving){

	}
	std::string retour; // évite warning, a supprimer lors de creation du parseur
	return retour;
}
