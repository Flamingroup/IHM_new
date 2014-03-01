#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <communication/serialport.h>
#include <QMessageBox>
#include <iostream>
//#include <Q_INT32>
#include <QColorDialog>
#include <QPalette>
#include <sstream>

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

    connections();

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

void MainWindow::connections()
{
    //Color buttons
    connect(ui->colorButtonX1, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
    connect(ui->colorButtonX2, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
    connect(ui->colorButtonX3, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
    connect(ui->colorButtonX4, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
    connect(ui->colorButtonX5, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
    connect(ui->colorButtonX6, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
    connect(ui->colorButtonX7, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
    connect(ui->colorButtonX8, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
    connect(ui->colorButtonX9, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
    connect(ui->colorButtonX10, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
    connect(ui->colorButtonX11, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
    connect(ui->colorButtonX12, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
    connect(ui->colorButtonX13, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
    connect(ui->colorButtonX14, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
    connect(ui->colorButtonX15, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
    connect(ui->colorButtonX16, SIGNAL(clicked()), this, SLOT(changeCurveColor()));

    //buttons and actions
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

    //checkboxes
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

QPushButton *MainWindow::colorButtonWithFocus()
{
    if(ui->colorButtonX1->hasFocus())
        return ui->colorButtonX1;
    if(ui->colorButtonX2->hasFocus())
        return ui->colorButtonX2;
    if(ui->colorButtonX3->hasFocus())
        return ui->colorButtonX3;
    if(ui->colorButtonX4->hasFocus())
        return ui->colorButtonX4;
    if(ui->colorButtonX5->hasFocus())
        return ui->colorButtonX5;
    if(ui->colorButtonX6->hasFocus())
        return ui->colorButtonX6;
    if(ui->colorButtonX7->hasFocus())
        return ui->colorButtonX7;
    if(ui->colorButtonX8->hasFocus())
        return ui->colorButtonX8;
    if(ui->colorButtonX9->hasFocus())
        return ui->colorButtonX9;
    if(ui->colorButtonX10->hasFocus())
        return ui->colorButtonX10;
    if(ui->colorButtonX11->hasFocus())
        return ui->colorButtonX11;
    if(ui->colorButtonX12->hasFocus())
        return ui->colorButtonX12;
    if(ui->colorButtonX13->hasFocus())
        return ui->colorButtonX13;
    if(ui->colorButtonX14->hasFocus())
        return ui->colorButtonX14;
    if(ui->colorButtonX15->hasFocus())
        return ui->colorButtonX15;
    if(ui->colorButtonX16->hasFocus())
        return ui->colorButtonX16;
    return NULL;
}

void MainWindow::changeCurveColor()
{
    int r, g, b, buttonNum;
    QColor newColor = QColorDialog::getColor(Qt::white,this);
    QPushButton *focusedButton = colorButtonWithFocus();
    string buttonName(focusedButton->objectName().toStdString()), junk, numString;
    stringstream ns(buttonName);
    getline(ns,junk,'X');
    getline(ns,numString);
    ns.flush();
    ns>>buttonNum;
    meteo.changeCurveColor(buttonNum, newColor);
    r=newColor.red();
    g=newColor.green();
    b=newColor.blue();
    ostringstream os;
    os<<"background-color:rgb("<<r<<","<<g<<","<<b<<");color:rgb(255,255,255)";
    focusedButton->setAutoFillBackground(true);
    focusedButton->setStyleSheet(QString(os.str().c_str()));
}

void MainWindow::airPressureToggled(bool ischecked)
{
	if (ischecked)
		++nbChecked;
	else --nbChecked;
	if (nbChecked < 16){
		c_AllCheckedManually = true;
		ui->c_all->setChecked(false);
		c_AllCheckedManually = false;
	}
	else if(nbChecked == 16)
		ui->c_all->setChecked(true);
	std::cout << nbChecked << std::endl;
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::airPressure);
	capt->setVisible(ischecked);
}

void MainWindow::airTemperatureToggled(bool ischecked)
{
	if (ischecked)
		++nbChecked;
	else --nbChecked;
	if (nbChecked < 16){
		c_AllCheckedManually = true;
		ui->c_all->setChecked(false);
		c_AllCheckedManually = false;
	}
	else if(nbChecked == 16)
		ui->c_all->setChecked(true);
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::airTemperture);
	capt->setVisible(ischecked);
}

void MainWindow::hailAccumulationToggled(bool ischecked)
{
	if (ischecked)
		++nbChecked;
	else --nbChecked;
	if (nbChecked < 16){
		c_AllCheckedManually = true;
		ui->c_all->setChecked(false);
		c_AllCheckedManually = false;
	}
	else if(nbChecked == 16)
		ui->c_all->setChecked(true);
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::hailAccumulation);
	capt->setVisible(ischecked);
}

void MainWindow::hailDurationToggled(bool ischecked)
{
	if (ischecked)
		++nbChecked;
	else --nbChecked;
	if (nbChecked < 16){
		c_AllCheckedManually = true;
		ui->c_all->setChecked(false);
		c_AllCheckedManually = false;
	}
	else if(nbChecked == 16)
		ui->c_all->setChecked(true);
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::hailDuration);
	capt->setVisible(ischecked);
}

void MainWindow::hailIntensity(bool ischecked)
{
	if (ischecked)
		++nbChecked;
	else --nbChecked;
	if (nbChecked < 16){
		c_AllCheckedManually = true;
		ui->c_all->setChecked(false);
		c_AllCheckedManually = false;
	}
	else if(nbChecked == 16)
		ui->c_all->setChecked(true);
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::hailIntensity);
	capt->setVisible(ischecked);
}

void MainWindow::heatTemperatureToggled(bool ischecked)
{
	if (ischecked)
		++nbChecked;
	else --nbChecked;
	if (nbChecked < 16){
		c_AllCheckedManually = true;
		ui->c_all->setChecked(false);
		c_AllCheckedManually = false;
	}
	else if(nbChecked == 16)
		ui->c_all->setChecked(true);
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::heatTemperature);
	capt->setVisible(ischecked);
}

void MainWindow::heatVoltageToggled(bool ischecked)
{
	if (ischecked)
		++nbChecked;
	else --nbChecked;
	if (nbChecked < 16){
		c_AllCheckedManually = true;
		ui->c_all->setChecked(false);
		c_AllCheckedManually = false;
	}
	else if(nbChecked == 16)
		ui->c_all->setChecked(true);
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::heatVoltage);
	capt->setVisible(ischecked);
}

void MainWindow::rainAccumulationToggled(bool ischecked)
{
	if (ischecked)
		++nbChecked;
	else --nbChecked;
	if (nbChecked < 16){
		c_AllCheckedManually = true;
		ui->c_all->setChecked(false);
		c_AllCheckedManually = false;
	}
	else if(nbChecked == 16)
		ui->c_all->setChecked(true);
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::rainAccumulation);
	capt->setVisible(ischecked);
}

void MainWindow::rainDurationToggled(bool ischecked)
{
	if (ischecked)
		++nbChecked;
	else --nbChecked;
	if (nbChecked < 16){
		c_AllCheckedManually = true;
		ui->c_all->setChecked(false);
		c_AllCheckedManually = false;
	}
	else if(nbChecked == 16)
		ui->c_all->setChecked(true);
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::rainDuration);
	capt->setVisible(ischecked);
}

void MainWindow::rainIntensityToggled(bool ischecked)
{
	if (ischecked)
		++nbChecked;
	else --nbChecked;
	if (nbChecked < 16){
		c_AllCheckedManually = true;
		ui->c_all->setChecked(false);
		c_AllCheckedManually = false;
	}
	else if(nbChecked == 16)
		ui->c_all->setChecked(true);
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::rainIntensity);
	capt->setVisible(ischecked);
}

void MainWindow::refVoltageToggled(bool ischecked)
{
	if (ischecked)
		++nbChecked;
	else --nbChecked;
	if (nbChecked < 16){
		c_AllCheckedManually = true;
		ui->c_all->setChecked(false);
		c_AllCheckedManually = false;
	}
	else if(nbChecked == 16)
		ui->c_all->setChecked(true);
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::refVoltage);
	capt->setVisible(ischecked);
}

void MainWindow::relativeHumidityToggled(bool ischecked)
{
	if (ischecked)
		++nbChecked;
	else --nbChecked;
	if (nbChecked < 16){
		c_AllCheckedManually = true;
		ui->c_all->setChecked(false);
		c_AllCheckedManually = false;
	}
	else if(nbChecked == 16)
		ui->c_all->setChecked(true);
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::relativeHumidity);
	capt->setVisible(ischecked);
}

void MainWindow::supplyVoltageToggled(bool ischecked)
{
	if (ischecked)
		++nbChecked;
	else --nbChecked;
	if (nbChecked < 16){
		c_AllCheckedManually = true;
		ui->c_all->setChecked(false);
		c_AllCheckedManually = false;
	}
	else if(nbChecked == 16)
		ui->c_all->setChecked(true);
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::supplyVoltage);
	capt->setVisible(ischecked);
}

void MainWindow::windDirectionAvrgToggled(bool ischecked)
{
	if (ischecked)
		++nbChecked;
	else --nbChecked;
	if (nbChecked < 16){
		c_AllCheckedManually = true;
		ui->c_all->setChecked(false);
		c_AllCheckedManually = false;
	}
	else if(nbChecked == 16)
		ui->c_all->setChecked(true);
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::windDirectionAvrg);
	capt->setVisible(ischecked);
}

void MainWindow::windSpeedAverageToggled(bool ischecked)
{
	if (ischecked)
		++nbChecked;
	else --nbChecked;
	if (nbChecked < 16){
		c_AllCheckedManually = true;
		ui->c_all->setChecked(false);
		c_AllCheckedManually = false;
	}
	else if(nbChecked == 16)
		ui->c_all->setChecked(true);
	Capteur* capt = meteo.getCapt(StationMeteo::TypeCapteur::windSpeedAverage);
	capt->setVisible(ischecked);
}

void MainWindow::analog1Toggled(bool ischecked)
{
	if (ischecked)
		++nbChecked;
	else --nbChecked;
	if (nbChecked < 16){
		c_AllCheckedManually = true;
		ui->c_all->setChecked(false);
		c_AllCheckedManually = false;
	}
	else if(nbChecked == 16)
		ui->c_all->setChecked(true);
	analog1.setVisible(ischecked);
}

void MainWindow::toggleAll(bool ischecked)
{
	if (c_AllCheckedManually)
		return;
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
