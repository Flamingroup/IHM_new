#ifndef PARSEURENVOI_H
#define PARSEURENVOI_H
#include <string>
#include <QString>

using namespace std;

class ParseurEnvoi
{
	public:
		ParseurEnvoi();
		std::string parseToQstring(QString sToParse);
};

#endif // PARSEURENVOI_H
