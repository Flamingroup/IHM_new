#ifndef SERIALPORT_H
#define SERIALPORT_H
#include <QDialog>
#include <communication/communication.h>
#include "qextserialport.h"
#include <map>
#include <string>

using std::map;
using std::string;

class SerialPort : public Communication
{
		Q_OBJECT
	private:
		QextSerialPort* m_port;
		QextSerialPort* tmp_port;
	public:
		SerialPort(QWidget* parent);
		void configurer();
		void sendCommand();
		void startReading();
		void stopReading();
		QByteArray readAll();
	public slots:
		void onDataReceived();
		void validateConfig();
	signals:
		void readyRead();
};

#endif // SERIALPORT_H
