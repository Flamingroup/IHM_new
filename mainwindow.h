#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <communication/communication.h>
#include <parseurs/retour/parseurretour.h>
#include <plot.h>
#include <stationmeteo.h>
#include <capteurs/capteur.h>
#include <QTimer>
#include <qwt_compass_rose.h>
#include <qwt_dial_needle.h>
#include <QColorDialog>

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
		Plot* p_plot;
		StationMeteo meteo;
		vector<Capteur*> t_capteurs;
		QTimer timer;
		QwtSimpleCompassRose *rose;
		QwtCompassWindArrow *needle;
		Capteur analog1;
		int nbChecked = 0;
		bool c_AllCheckedManually = false;
		ParseurRetour* p = NULL;
		void connections();
        void defaultButtonColor();

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

		void changeCurveColor();

		/** Gestion des checkboxes **/
		void airPressureToggled(bool);
		void airTemperatureToggled(bool);
		void hailAccumulationToggled(bool);
		void hailDurationToggled(bool);
		void hailIntensity(bool);
		void heatTemperatureToggled(bool);
		void heatVoltageToggled(bool);
		void rainAccumulationToggled(bool);
		void rainDurationToggled(bool);
		void rainIntensityToggled(bool);
		void refVoltageToggled(bool);
		void relativeHumidityToggled(bool);
		void supplyVoltageToggled(bool);
		void windDirectionAvrgToggled(bool);
		void windSpeedAverageToggled(bool);
		void analog1Toggled(bool);
		void toggleAll(bool);
		void lireRetour();
};

#endif // MAINWINDOW_H
