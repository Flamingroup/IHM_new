#include "communication.h"

Communication::Communication(QWidget* parent)
{
	this->parent=parent;
}

bool Communication::isConfigured() const
{
	return configured;
}

void Communication::unConfigure()
{
	configured=false;
}

Communication::Type Communication::getType() const
{
	return type;
}

void Communication::setCommand(std::string command){
	cmd=command;
}
