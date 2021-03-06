#include "parseurretour.h"

ParseurRetour::ParseurRetour()
{
}


/* En mémoire à mon cerveau :
	std::shared_ptr<QList<std::shared_ptr<QList<std::shared_ptr<QString> > > > > retour (QList<std::shared_ptr<QList<std::shared_ptr<QString>>>>());
*/

QList< QList<QString*>* >* ParseurRetour::parse(QString str){
    QList<QList<QString*>*>* retour = new QList< QList<QString*>* >(); // auto * ?
	QString* car;
	QStringList strlist = str.split(',');

    int lastCharPos;
    for (auto it = strlist.begin(); it != strlist.end(); ++it){
        lastCharPos=0;
		QStringList nomEValeur = it->split('=');
		retour->push_back(new QList<QString*>);
		retour->last()->push_back(new QString(nomEValeur[0]));
		lastCharPos=nomEValeur[1].size()-1;
		car = new QString(nomEValeur[1][lastCharPos]);
		nomEValeur[1].remove(lastCharPos, 1);
		retour->last()->push_back((new QString(nomEValeur[1])));
		retour->last()->push_back(car);
	}
	return retour;
}

//récupération des valeures :
//QList<QList<QString*>*>* retour = parsetest("Th=76.1F,Vh=11.5N,Vs=11.5V,Vr=3.51V\n\r");
//QList<QList<QString*>*>::Iterator itRetour = retour->begin();
//for (; itRetour!= retour->end(); ++itRetour){
//	QList<QString*>::Iterator itListe = (*itRetour)->begin();
//	for (; itListe != (*itRetour)->end(); ++itListe){
//		std::cout << (*itListe)->toStdString() << std::endl;
//	}
//}
