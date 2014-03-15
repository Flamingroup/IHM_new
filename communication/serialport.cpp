#include "serialport.h"
#include "portselection.h"
#include <QMessageBox>
#include <mainwindow.h>
#include <iostream>


SerialPort::SerialPort(QWidget* parent)
	:Communication(parent)
{
	type=Type::Serie;
	m_port = new QextSerialPort();
}

void SerialPort::configurer()
{
	tmp_port = new QextSerialPort();
	PortSelection* s = new PortSelection(tmp_port, this);
	s->exec();
	//Bar-> setText(tr("Port %1 configured.").arg(m_port->portName()));
}

/**
  @bug comme appelé par QTimer::timeout(), si erreur, elle n'arrete pas d'apparaitre et bloque complétement le programme
*/
void SerialPort::sendCommand()
{
	if (!m_port->isOpen()) {
		if(!m_port->open(QIODevice::ReadWrite))	{
            QMessageBox::warning(0, "Error !", tr("Can't open port with specified settings !"));
			return;
		}
		else {
            connect(m_port, SIGNAL(readyRead()), this, SLOT(onDataReceived())); // ATTENTION : boucle infinie (readyRead lance onDataReceived qui émet readyRead....)
		}
	}
	if (!cmd.empty()) {
		cmd.append("\n");
		m_port->write(cmd.c_str());
	}
	else {
		QMessageBox::warning(0, "Error !", tr("Problem, the command is empty"));
	}
}

void SerialPort::startReading()
{
	if(!m_port->open(QIODevice::ReadWrite))
	{
        QMessageBox::warning(0, "Error !", tr("Can't open port with specified settings !"));
	}

	else
	{
		//m_status->setText(tr("Port %1 open, reading in process").arg(m_port->portName()));
        connect(m_port, SIGNAL(readyRead()), this, SLOT(onDataReceived())); // ATTENTION : boucle infinie (readyRead lance onDataReceived qui émet readyRead....)
	}
}

void SerialPort::stopReading()
{
	//m_status->setText(tr("Reading stopped on port %1").arg(m_port->portName()));
	m_port->close();
}

QByteArray SerialPort::readAll()
{
	return m_port->readAll();
}

void SerialPort::onDataReceived()
{
	emit readyRead();
}

void SerialPort::validateConfig()
{
	m_port->close();
	delete m_port;
	m_port = tmp_port;
	tmp_port=NULL;
	configured=true;
}
