#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <communication/communication.h>
#include <plot.h>
#include <stationmeteo.h>
#include <capteurs/capteur.h>
#include <QTimer>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT
	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private:
		Ui::MainWindow *ui;
		Communication* com = NULL;
		Plot* m_plot;
		StationMeteo meteo;
		vector<Capteur*> t_capteurs;
		QTimer timer;

	public slots:
		void createCommunicationSerie();
		void launchAcquisition();
		//void clearCurve();
		void saveData();
		void loadData();
		void about();
		void dialChangedSpin(double value);
		void dialChanged(int value);
		void pauseAcquisition();
		void stopAcquisition();
};

#endif // MAINWINDOW_H
