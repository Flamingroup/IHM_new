#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <QWidget>

using namespace std;

class Communication : public QWidget
{
		Q_OBJECT
	private :
		QWidget* parent;
	public:
		Communication(QWidget* parent = 0);
		virtual void configurer() = 0;
		virtual void sendCommand() = 0;
		virtual void startReading() = 0;
		virtual void stopReading() = 0;
		virtual QByteArray readAll() = 0;
	public slots:
		virtual void onDataReceived() = 0;
		virtual void validateConfig() = 0;
	signals:
		void readyRead();
};

#endif // COMMUNICATION_H
