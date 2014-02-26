#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <QWidget>

using namespace std;

class Communication : public QWidget
{
		Q_OBJECT
	protected :
		QWidget* parent;
		bool configured = false;
	public:
		enum Type{
			Undefined=0,
			Serie=1,
			Bluetooth=2
		};
		Type type = Type::Undefined;
		Communication(QWidget* parent = 0);
		virtual void configurer() = 0;
		virtual void stopReading() = 0;
		virtual QByteArray readAll() = 0;
		virtual bool isConfigured();
		void unConfigure();
		Type getType();
	public slots:
		virtual void sendCommand() = 0;
		virtual void startReading() = 0;
		virtual void onDataReceived() = 0;
		virtual void validateConfig() = 0;
	signals:
		void readyRead();
};

#endif // COMMUNICATION_H
