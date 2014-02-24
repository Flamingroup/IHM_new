#include "communication.h"

Communication::Communication(QWidget* parent)
{
	this->parent=parent;
}

bool Communication::isConfigured()
{
	return configured;
}
