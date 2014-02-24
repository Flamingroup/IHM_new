#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <communication/communication.h>
#include <plot.h>
#include <stationmeteo.h>
#include <capteurs/capteur.h>

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

	public slots:
		void createCommunication();
		void launchAcquisition();
		//void clearCurve();
		void saveData();
		void loadData();
		void about();

};

#endif // MAINWINDOW_H
