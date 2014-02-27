#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <communication/serialport.h>
#include <QMessageBox>
#include <iostream>
#include <Q_INT32>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->m_portSerie, SIGNAL(triggered()), this, SLOT(createCommunication()));
	// A connecter avec plot et non avec this
	//connect(ui->m_clearCurve, SIGNAL(triggered()), this, SLOT(clearCurve()));
	p_plot = new Plot();
	analog1.setPlot(p_plot);
	meteo.setPlot(p_plot);
	ui->plotLayout->addWidget(p_plot, 1, 0);
	ui->dial_delai_acquisitionSpin->setMinimum(0.1);
	ui->dial_delai_acquisitionSpin->setMaximum(3600.00);
	ui->dial_delai_acquisition->setMinimum(1);
	ui->dial_delai_acquisition->setMaximum(36000);
	connect(ui->b_play, SIGNAL(clicked()), this, SLOT(launchAcquisition()));
	connect(ui->b_pause, SIGNAL(clicked()), this, SLOT(pauseAcquisition()));
	connect(ui->b_arret, SIGNAL(clicked()), this, SLOT(stopAcquisition()));
	connect(ui->m_portSerie, SIGNAL(triggered()), this, SLOT(createCommunicationSerie()));
	connect(ui->m_saveData, SIGNAL(triggered()), this, SLOT(saveData()));
	connect(ui->m_loadData, SIGNAL(triggered()), this, SLOT(loadData()));
	connect(ui->m_about, SIGNAL(triggered()), this, SLOT(about()));
	connect(ui->m_aboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect(ui->dial_delai_acquisitionSpin, SIGNAL(valueChanged(double)), this, SLOT(dialChangedSpin(double)));
	connect(ui->dial_delai_acquisition, SIGNAL(valueChanged(int)), this, SLOT(dialChanged(int)));

	connect(ui->c_airPressure, SIGNAL(toggled(bool)), this, SLOT(airPressureToggled(bool)));
	connect(ui->c_airTemperture, SIGNAL(toggled(bool)), this, SLOT(airTemperatureToggled(bool)));
	connect(ui->c_hailAccumulation, SIGNAL(toggled(bool)), this, SLOT(hailAccumulationToggled(bool)));
	connect(ui->c_hailDuration, SIGNAL(toggled(bool)), this, SLOT(hailDurationToggled(bool)));
	connect(ui->c_hailIntensity, SIGNAL(toggled(bool)), this, SLOT(hailIntensity(bool)));
	connect(ui->c_heatTemperature, SIGNAL(toggled(bool)), this, SLOT(heatTemperatureToggled(bool)));
	connect(ui->c_heatVoltage, SIGNAL(toggled(bool)), this, SLOT(heatVoltageToggled(bool)));
	connect(ui->c_rainAccumulation, SIGNAL(toggled(bool)), this, SLOT(rainAccumulationToggled(bool)));
	connect(ui->c_rainDuration, SIGNAL(toggled(bool)), this, SLOT(rainDurationToggled(bool)));
	connect(ui->c_rainIntensity, SIGNAL(toggled(bool)), this, SLOT(rainIntensityToggled(bool)));
	connect(ui->c_refVoltage, SIGNAL(toggled(bool)), this, SLOT(refVoltageToggled(bool)));
	connect(ui->c_relativeHumidity, SIGNAL(toggled(bool)), this, SLOT(relativeHumidityToggled(bool)));
	connect(ui->c_supplyVoltage, SIGNAL(toggled(bool)), this, SLOT(supplyVoltageToggled(bool)));
	connect(ui->c_windDirectionAvrg, SIGNAL(toggled(bool)), this, SLOT(windDirectionAvrgToggled(bool)));
	connect(ui->c_windSpeedAverage, SIGNAL(toggled(bool)), this, SLOT(windSpeedAverageToggled(bool)));

	connect(ui->c_analog1, SIGNAL(toggled(bool)), this, SLOT(analog1Toggled(bool)));

	connect(ui->c_all, SIGNAL(toggled(bool)), this, SLOT(toggleAll(bool)));

	rose = new QwtSimpleCompassRose(16,2);
	needle = new QwtCompassWindArrow(QwtCompassWindArrow::Style2,Qt::black,Qt::red);
	ui->Compass->setValue(180);
	ui->Compass->setNeedle(needle);
	ui->Compass->setReadOnly(true);
}

MainWindow::~MainWindow()
{
	delete needle;
	delete rose;
	delete ui;
}

void MainWindow::createCommunicationSerie()
{
	if (com == NULL)
		com = new SerialPort(this);
	if (com->getType() != Communication::Type::Serie){
		delete com;
		com = new SerialPort(this);
	}
	if (!com->isConfigured()){
		com->configurer();
	}
}

void MainWindow::launchAcquisition()
{
	if (com == NULL || !com->isConfigured()){
		// a remplacer par un create communication lorsqu'il sera créé
		this->createCommunicationSerie();
	}
	if (!com->isConfigured()){
		QMessageBox::warning(0, "Error !", "Veuillez configurer la communication avant de commencer des mesures");
		return;
	}
	if (timer.isActive())
		return;
	timer.start();
	com->sendCommand();

//	meteo.getCapt(StationMeteo::TypeCapteur::airPressure)->addValue(10, 50);
//	meteo.getCapt(StationMeteo::TypeCapteur::airPressure)->addValue(20, 50);
//	meteo.getCapt(StationMeteo::TypeCapteur::airPressure)->addValue(30, 50);
//	meteo.getCapt(StationMeteo::TypeCapteur::airPressure)->addValue(40, 50);
}

void MainWindow::saveData()
{

}

void MainWindow::loadData()
{

}

void MainWindow::about()
{
	QMessageBox::warning(0, "About", "Programme créé par Yan, Raphaël, Ayemeric et Loïc");
}

void MainWindow::dialChangedSpin(double value)
{
	ui->dial_delai_acquisition->setValue(qint32(value*10));
	timer.setInterval(value);
}

void MainWindow::dialChanged(int value)
{
	ui->dial_delai_acquisitionSpin->setValue(double(value/10.0));
	// A décommenter si on supprime dans le dialChangedSpin();
	//timer.setInterval(ui->dial_delai_acquisitionSpin->value()*1000);
}

void MainWindow::pauseAcquisition()
{
	timer.stop();
}

void MainWindow::stopAcquisition()
{
	timer.stop();
	if ( com != NULL)
		com->unConfigure();
}

void MainWindow::airPressureToggled(bool ischecked)
{
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::airPressure);
	capt->setVisible(ischecked);
}

void MainWindow::airTemperatureToggled(bool ischecked)
{
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::airTemperture);
	capt->setVisible(ischecked);
}

void MainWindow::hailAccumulationToggled(bool ischecked)
{
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::hailAccumulation);
	capt->setVisible(ischecked);
}

void MainWindow::hailDurationToggled(bool ischecked)
{
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::hailDuration);
	capt->setVisible(ischecked);
}

void MainWindow::hailIntensity(bool ischecked)
{
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::hailIntensity);
	capt->setVisible(ischecked);
}

void MainWindow::heatTemperatureToggled(bool ischecked)
{
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::heatTemperature);
	capt->setVisible(ischecked);
}

void MainWindow::heatVoltageToggled(bool ischecked)
{
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::heatVoltage);
	capt->setVisible(ischecked);
}

void MainWindow::rainAccumulationToggled(bool ischecked)
{
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::rainAccumulation);
	capt->setVisible(ischecked);
}

void MainWindow::rainDurationToggled(bool ischecked)
{
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::rainDuration);
	capt->setVisible(ischecked);
}

void MainWindow::rainIntensityToggled(bool ischecked)
{
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::rainIntensity);
	capt->setVisible(ischecked);
}

void MainWindow::refVoltageToggled(bool ischecked)
{
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::refVoltage);
	capt->setVisible(ischecked);
}

void MainWindow::relativeHumidityToggled(bool ischecked)
{
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::relativeHumidity);
	capt->setVisible(ischecked);
}

void MainWindow::supplyVoltageToggled(bool ischecked)
{
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::supplyVoltage);
	capt->setVisible(ischecked);
}

void MainWindow::windDirectionAvrgToggled(bool ischecked)
{
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::windDirectionAvrg);
	capt->setVisible(ischecked);
}

void MainWindow::windSpeedAverageToggled(bool ischecked)
{
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::windSpeedAverage);
	capt->setVisible(ischecked);
}

void MainWindow::analog1Toggled(bool ischecked)
{
	analog1.setVisible(ischecked);
}

void MainWindow::toggleAll(bool ischecked)
{
	ui->c_airPressure->setChecked(ischecked);
	ui->c_airTemperture->setChecked(ischecked);
	ui->c_hailAccumulation->setChecked(ischecked);
	ui->c_hailDuration->setChecked(ischecked);
	ui->c_hailIntensity->setChecked(ischecked);
	ui->c_heatTemperature->setChecked(ischecked);
	ui->c_heatVoltage->setChecked(ischecked);
	ui->c_rainAccumulation->setChecked(ischecked);
	ui->c_rainDuration->setChecked(ischecked);
	ui->c_rainIntensity->setChecked(ischecked);
	ui->c_refVoltage->setChecked(ischecked);
	ui->c_relativeHumidity->setChecked(ischecked);
	ui->c_supplyVoltage->setChecked(ischecked);
	ui->c_windDirectionAvrg->setChecked(ischecked);
	ui->c_windSpeedAverage->setChecked(ischecked);
	ui->c_analog1->setChecked(ischecked);
}
