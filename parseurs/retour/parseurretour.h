#ifndef PARSEURRETOUR_H
#define PARSEURRETOUR_H

#include <QStringList>

class ParseurRetour
{
	public:
		ParseurRetour();
		static QList< QList<QString*>* >* parse(QString str);
};

#endif // PARSEURRETOUR_H
