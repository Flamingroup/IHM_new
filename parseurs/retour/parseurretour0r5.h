#ifndef PARSEURRETOUR0R5_H
#define PARSEURRETOUR0R5_H
#include "parseurretour.h"
#include <QString>
#include <memory>

class ParseurRetour0R5 : public ParseurRetour
{
	public:
		ParseurRetour0R5();
		QList< QList<QString*>* >* parse(QString str);
};

#endif // PARSEURRETOUR0R5_H
