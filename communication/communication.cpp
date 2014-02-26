#include "communication.h"

Communication::Communication(QWidget* parent)
{
	this->parent=parent;
}

bool Communication::isConfigured()
{
	return configured;
}

void Communication::unConfigure()
{
	configured=false;
}

Communication::Type Communication::getType()
{
	return type;
}
