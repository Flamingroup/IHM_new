#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <convertisseur.hpp>

#include <communication/serialport.h>
#include <QMessageBox>
#include <iostream>

using std::cout;
using std::endl;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
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
    defaultButtonColor();
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

/**
 * @brief MainWindow::connections Constructeur de la fenêtre principale du logiciel
 */
void MainWindow::connections()
{

	//Color buttons
	connect(ui->bc_airPressure, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
	connect(ui->bc_airTemperture, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
	connect(ui->bc_analog1, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
	connect(ui->bc_hailAccumulation, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
	connect(ui->bc_hailDuration, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
	connect(ui->bc_hailIntensity, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
	connect(ui->bc_heatTemperature, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
	connect(ui->bc_heatVoltage, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
	connect(ui->bc_rainAccumulation, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
	connect(ui->bc_rainDuration, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
	connect(ui->bc_rainIntensity, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
	connect(ui->bc_refVoltage, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
	connect(ui->bc_relativeHumidity, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
	connect(ui->bc_supplyVoltage, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
	connect(ui->bc_windDirectionAvrg, SIGNAL(clicked()), this, SLOT(changeCurveColor()));
	connect(ui->bc_windSpeedAverage, SIGNAL(clicked()), this, SLOT(changeCurveColor()));

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

	// timer --> Non lié car le com est un pointeur et faut null par défaut.
	//           Solution possible, slot sendcommand dans this qui ne fait qu'appeler le sendcommand du com en vérifiant que le pointeur n'est pas null
	connect(&timer, SIGNAL(timeout()), com, SLOT(sendCommand()));

	// Communication
	connect(ui->m_portSerie, SIGNAL(triggered()), this, SLOT(createCommunication()));
}

void MainWindow::defaultButtonColor(){
    QColor c=meteo.getCapt(StationMeteo::TypeCapteur::airPressure)->getColor();
    ui->bc_airPressure->setStyleSheet(QString("background-color:rgb("+
                                              QString::number(c.red()) +
                                              ',' + QString::number(c.green()) +
                                              ',' + QString::number(c.blue()) +
                                              ");color:rgb(255,255,255)"));
    c=meteo.getCapt(StationMeteo::TypeCapteur::airTemperture)->getColor();
    ui->bc_airTemperture->setStyleSheet(QString("background-color:rgb("+
                                                QString::number(c.red()) +
                                                ',' + QString::number(c.green()) +
                                                ',' + QString::number(c.blue()) +
                                                ");color:rgb(255,255,255)"));
    c=meteo.getCapt(StationMeteo::TypeCapteur::hailAccumulation)->getColor();
    ui->bc_hailAccumulation->setStyleSheet(QString("background-color:rgb("+
                                                   QString::number(c.red()) +
                                                   ',' + QString::number(c.green()) +
                                                   ',' + QString::number(c.blue()) +
                                                   ");color:rgb(255,255,255)"));
    c=meteo.getCapt(StationMeteo::TypeCapteur::hailDuration)->getColor();
    ui->bc_hailDuration->setStyleSheet(QString("background-color:rgb("+
                                               QString::number(c.red()) +
                                               ',' + QString::number(c.green()) +
                                               ',' + QString::number(c.blue()) +
                                               ");color:rgb(255,255,255)"));
    c=meteo.getCapt(StationMeteo::TypeCapteur::hailIntensity)->getColor();
    ui->bc_hailIntensity->setStyleSheet(QString("background-color:rgb("+
                                                QString::number(c.red()) +
                                                ',' + QString::number(c.green()) +
                                                ',' + QString::number(c.blue()) +
                                                ");color:rgb(255,255,255)"));
    c=meteo.getCapt(StationMeteo::TypeCapteur::heatTemperature)->getColor();
    ui->bc_heatTemperature->setStyleSheet(QString("background-color:rgb("+
                                                  QString::number(c.red()) +
                                                  ',' + QString::number(c.green()) +
                                                  ',' + QString::number(c.blue()) +
                                                  ");color:rgb(255,255,255)"));
    c=meteo.getCapt(StationMeteo::TypeCapteur::heatVoltage)->getColor();
    ui->bc_heatVoltage->setStyleSheet(QString("background-color:rgb("+
                                              QString::number(c.red()) +
                                              ',' + QString::number(c.green()) +
                                              ',' + QString::number(c.blue()) +
                                              ");color:rgb(255,255,255)"));
    c=meteo.getCapt(StationMeteo::TypeCapteur::rainAccumulation)->getColor();
    ui->bc_rainAccumulation->setStyleSheet(QString("background-color:rgb("+
                                                   QString::number(c.red()) +
                                                   ',' + QString::number(c.green()) +
                                                   ',' + QString::number(c.blue()) +
                                                   ");color:rgb(255,255,255)"));
    c=meteo.getCapt(StationMeteo::TypeCapteur::rainDuration)->getColor();
    ui->bc_rainDuration->setStyleSheet(QString("background-color:rgb("+
                                               QString::number(c.red()) +
                                               ',' + QString::number(c.green()) +
                                               ',' + QString::number(c.blue()) +
                                               ");color:rgb(255,255,255)"));
    c=meteo.getCapt(StationMeteo::TypeCapteur::rainIntensity)->getColor();
    ui->bc_rainIntensity->setStyleSheet(QString("background-color:rgb("+
                                                QString::number(c.red()) +
                                                ',' + QString::number(c.green()) +
                                                ',' + QString::number(c.blue()) +
                                                ");color:rgb(255,255,255)"));
    c=meteo.getCapt(StationMeteo::TypeCapteur::refVoltage)->getColor();
    ui->bc_refVoltage->setStyleSheet(QString("background-color:rgb("+
                                             QString::number(c.red()) +
                                             ',' + QString::number(c.green()) +
                                             ',' + QString::number(c.blue()) +
                                             ");color:rgb(255,255,255)"));
    c=meteo.getCapt(StationMeteo::TypeCapteur::relativeHumidity)->getColor();
    ui->bc_relativeHumidity->setStyleSheet(QString("background-color:rgb("+
                                                   QString::number(c.red()) +
                                                   ',' + QString::number(c.green()) +
                                                   ',' + QString::number(c.blue()) +
                                                   ");color:rgb(255,255,255)"));
    c=meteo.getCapt(StationMeteo::TypeCapteur::supplyVoltage)->getColor();
    ui->bc_supplyVoltage->setStyleSheet(QString("background-color:rgb("+
                                                QString::number(c.red()) +
                                                ',' + QString::number(c.green()) +
                                                ',' + QString::number(c.blue()) +
                                                ");color:rgb(255,255,255)"));
    c=meteo.getCapt(StationMeteo::TypeCapteur::windDirectionAvrg)->getColor();
    ui->bc_windDirectionAvrg->setStyleSheet(QString("background-color:rgb("+
                                                    QString::number(c.red()) +
                                                    ',' + QString::number(c.green()) +
                                                    ',' + QString::number(c.blue()) +
                                                    ");color:rgb(255,255,255)"));
    c=meteo.getCapt(StationMeteo::TypeCapteur::windSpeedAverage)->getColor();
    ui->bc_windSpeedAverage->setStyleSheet(QString("background-color:rgb("+
                                                   QString::number(c.red()) +
                                                   ',' + QString::number(c.green()) +
                                                   ',' + QString::number(c.blue()) +
                                                   ");color:rgb(255,255,255)"));
    ui->bc_analog1->setStyleSheet("background-color:black");
}


void MainWindow::createCommunicationSerie()
{
	if (com == NULL) {
		com = new SerialPort(this);
		connect(com, SIGNAL(readyRead()), this, SLOT(lireRetour()));
	}
	else if (com->getType() != Communication::Type::Serie){
		delete com;
		com = new SerialPort(this);
		connect(com, SIGNAL(readyRead()), this, SLOT(lireRetour()));
	}
	if (!com->isConfigured()){
		com->configurer();
	}
}

void MainWindow::launchAcquisition()
{

	meteo.getCapt(StationMeteo::TypeCapteur::airPressure)->addValue(10, 10);
	meteo.getCapt(StationMeteo::TypeCapteur::airPressure)->addValue(20, 50);
	meteo.getCapt(StationMeteo::TypeCapteur::airPressure)->addValue(30, 2);
	meteo.getCapt(StationMeteo::TypeCapteur::airPressure)->addValue(40, 10);
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
	com->setCommand("00");
	timer.start();
	com->sendCommand();
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

void MainWindow::changeCurveColor()
{
	QColor newColor;
	QPushButton* focusedButton;
	if (ui->bc_airPressure->hasFocus()){
		newColor = QColorDialog::getColor(Qt::white,this);
		if(!newColor.isValid())
			return;
		meteo.getCapt(StationMeteo::TypeCapteur::airPressure)->setColor(newColor);
		focusedButton=ui->bc_airPressure;
	}
	else if (ui->bc_airTemperture->hasFocus()){
		newColor = QColorDialog::getColor(Qt::white,this);
		if(!newColor.isValid())
			return;
		meteo.getCapt(StationMeteo::TypeCapteur::airTemperture)->setColor(newColor);
		focusedButton=ui->bc_airTemperture;
	}
	else if (ui->bc_analog1->hasFocus()){
		newColor = QColorDialog::getColor(Qt::white,this);
		if(!newColor.isValid())
			return;
		analog1.setColor(newColor);
		focusedButton=ui->bc_analog1;
	}
	else if (ui->bc_hailAccumulation->hasFocus()){
		newColor = QColorDialog::getColor(Qt::white,this);
		if(!newColor.isValid())
			return;
		meteo.getCapt(StationMeteo::TypeCapteur::hailAccumulation)->setColor(newColor);
		focusedButton=ui->bc_hailAccumulation;
	}
	else if (ui->bc_hailDuration->hasFocus()){
		newColor = QColorDialog::getColor(Qt::white,this);
		if(!newColor.isValid())
			return;
		meteo.getCapt(StationMeteo::TypeCapteur::hailDuration)->setColor(newColor);
		focusedButton=ui->bc_hailDuration;
	}
	else if (ui->bc_hailIntensity->hasFocus()){
		newColor = QColorDialog::getColor(Qt::white,this);
		if(!newColor.isValid())
			return;
		meteo.getCapt(StationMeteo::TypeCapteur::hailIntensity)->setColor(newColor);
		focusedButton=ui->bc_hailIntensity;
	}
	else if (ui->bc_heatTemperature->hasFocus()){
		newColor = QColorDialog::getColor(Qt::white,this);
		if(!newColor.isValid())
			return;
		meteo.getCapt(StationMeteo::TypeCapteur::heatTemperature)->setColor(newColor);
		focusedButton=ui->bc_heatTemperature;
	}
	else if (ui->bc_heatVoltage->hasFocus()){
		newColor = QColorDialog::getColor(Qt::white,this);
		if(!newColor.isValid())
			return;
		meteo.getCapt(StationMeteo::TypeCapteur::heatVoltage)->setColor(newColor);
		focusedButton=ui->bc_heatVoltage;
	}
	else if (ui->bc_rainAccumulation->hasFocus()){
		newColor = QColorDialog::getColor(Qt::white,this);
		if(!newColor.isValid())
			return;
		meteo.getCapt(StationMeteo::TypeCapteur::rainAccumulation)->setColor(newColor);
		focusedButton=ui->bc_rainAccumulation;
	}
	else if (ui->bc_rainDuration->hasFocus()){
		newColor = QColorDialog::getColor(Qt::white,this);
		if(!newColor.isValid())
			return;
		meteo.getCapt(StationMeteo::TypeCapteur::rainDuration)->setColor(newColor);
		focusedButton=ui->bc_rainDuration;
	}
	else if (ui->bc_rainIntensity->hasFocus()){
		newColor = QColorDialog::getColor(Qt::white,this);
		if(!newColor.isValid())
			return;
		meteo.getCapt(StationMeteo::TypeCapteur::rainIntensity)->setColor(newColor);
		focusedButton=ui->bc_rainIntensity;
	}
	else if (ui->bc_refVoltage->hasFocus()){
		newColor = QColorDialog::getColor(Qt::white,this);
		if(!newColor.isValid())
			return;
		meteo.getCapt(StationMeteo::TypeCapteur::refVoltage)->setColor(newColor);
		focusedButton=ui->bc_refVoltage;
	}
	else if (ui->bc_relativeHumidity->hasFocus()){
		newColor = QColorDialog::getColor(Qt::white,this);
		if(!newColor.isValid())
			return;
		meteo.getCapt(StationMeteo::TypeCapteur::relativeHumidity)->setColor(newColor);
		focusedButton=ui->bc_relativeHumidity;
	}
	else if (ui->bc_supplyVoltage->hasFocus()){
		newColor = QColorDialog::getColor(Qt::white,this);
		if(!newColor.isValid())
			return;
		meteo.getCapt(StationMeteo::TypeCapteur::supplyVoltage)->setColor(newColor);
		focusedButton=ui->bc_supplyVoltage;
	}
	else if (ui->bc_windDirectionAvrg->hasFocus()){
		newColor = QColorDialog::getColor(Qt::white,this);
		if(!newColor.isValid())
			return;
		meteo.getCapt(StationMeteo::TypeCapteur::windDirectionAvrg)->setColor(newColor);
		focusedButton=ui->bc_windDirectionAvrg;
	}
	else if (ui->bc_windSpeedAverage->hasFocus()){
		newColor = QColorDialog::getColor(Qt::white,this);
		if(!newColor.isValid())
			return;
		meteo.getCapt(StationMeteo::TypeCapteur::windSpeedAverage)->setColor(newColor);
		focusedButton=ui->bc_windSpeedAverage;
	}
	else {
		return;
	}
	focusedButton->setAutoFillBackground(true);
	focusedButton->setStyleSheet(QString("background-color:rgb("+ QString::number(newColor.red()) + ',' + QString::number(newColor.green()) + ',' + QString::number(newColor.blue()) + ");color:rgb(255,255,255)"));
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

void MainWindow::lireRetour()
{
//	QString s (com->readAll());
	QString s = "0;20;2000;0R1,Dm=027D,Sm=0.1M\r\n0R2,Ta=74.6F,Ua=14.7P,Pa=1012.9H\r\n0R3,Rc=0.10M,Rd=2380s,Ri=0.0M,Hc=0.0M,Hd=0s,Hi=0.0M\r\n0R5,Th=76.1F,Vh=11.5N,Vs=11.5V,Vr=3.510V\r\n";
	double instant, analog1value;
	QStringList sl = s.split(';');
	cout << sl.size() << endl;
	if (sl.first() == "0") {
		sl.removeFirst();
		instant = sl.first().toDouble();
		cout << "instant " << instant << endl;
		sl.removeFirst();
		analog1value = sl.first().toDouble();
//		analog1.addValue(instant, analog1value);
		cout << "valeur analogique " << analog1value << endl;
		sl.removeFirst();
		for (QString i : sl.first().split("\r\n", QString::SkipEmptyParts)){
			QString str = i.remove(0, 4);
			QList<QList<QString*>*>* retour = ParseurRetour::parse(str);
			QList<QList<QString*>*>::Iterator itRetour = retour->begin();
			for (; itRetour!= retour->end(); ++itRetour){
				QList<QString*>::Iterator itListe = (*itRetour)->begin();
				while (itListe != (*itRetour)->end()){
					if (**itListe == "Dm"){
						++itListe;
						QString* valeur = *itListe;
						++itListe;
						cout << instant << "*" << valeur->toDouble() <<endl;
						//meteo.getCapt(StationMeteo::TypeCapteur::windDirectionAvrg)->addValue(instant, valeur->toDouble());
						//ui->v_windDirectionAvrg->setText(*valeur);
						++itListe;
					}
					else if (**itListe == "Sm"){
						++itListe;
						QString* valeur = *itListe;
						++itListe;
						cout << instant << "*" << valeur->toDouble() << endl;
						//meteo.getCapt(StationMeteo::TypeCapteur::windSpeedAverage)->addValue(instant, Convertisseur::convertSpeed(valeur->toDouble(), (*itListe)->toStdString()[0], 'M')) ;
						//ui->v_windSpeedAverage->setText(QString::number(Convertisseur::convertSpeed(valeur->toDouble(), (*itListe)->toStdString()[0], 'M')));
						++itListe;
					}
					else if (**itListe == "Ta"){
						++itListe;
						QString* valeur = *itListe;
						++itListe;
						cout << instant << "*" << valeur->toDouble() << endl;
//						meteo.getCapt(StationMeteo::TypeCapteur::airTemperture)->addValue(instant, Convertisseur::convertTemperature(valeur->toDouble(), (*itListe)->toStdString()[0], 'C'));
						++itListe;
					}
					else if (**itListe == "Ua"){
						++itListe;
						QString* valeur = *itListe;
						++itListe;
						cout << instant << "*" << valeur->toDouble() << endl;
//						meteo.getCapt(StationMeteo::TypeCapteur::relativeHumidity)->addValue(instant, valeur->toDouble());
						++itListe;
					}
					else if (**itListe == "Pa"){
						++itListe;
						QString* valeur = *itListe;
						++itListe;
						cout << instant << "*" << valeur->toDouble() << endl;
//						meteo.getCapt(StationMeteo::TypeCapteur::airPressure)->addValue(instant, Convertisseur::convertPression(valeur->toDouble(), (*itListe)->toStdString()[0], 'P'));
						++itListe;
					}
					else if (**itListe == "Rc"){
						++itListe;
						QString* valeur = *itListe;
						++itListe;
						cout << instant << "*" << valeur->toDouble() << endl;
//						meteo.getCapt(StationMeteo::TypeCapteur::rainAccumulation)->addValue(instant, valeur->toDouble());
						++itListe;
					}
					else if (**itListe == "Rd"){
						++itListe;
						QString* valeur = *itListe;
						++itListe;
						cout << instant << "*" << valeur->toDouble() << endl;
//						meteo.getCapt(StationMeteo::TypeCapteur::rainDuration)->addValue(instant, valeur->toDouble());
						++itListe;
					}
					else if (**itListe == "Ri"){
						++itListe;
						QString* valeur = *itListe;
						++itListe;
						cout << instant << "*" << valeur->toDouble() << endl;
//						meteo.getCapt(StationMeteo::TypeCapteur::rainIntensity)->addValue(instant, valeur->toDouble());
						++itListe;
					}
					else if (**itListe == "Hc"){
						++itListe;
						QString* valeur = *itListe;
						++itListe;
						cout << instant << "*" << valeur->toDouble() << endl;
//						meteo.getCapt(StationMeteo::TypeCapteur::hailAccumulation)->addValue(instant, Convertisseur::convertHail(valeur->toDouble(), (*itListe)->toStdString()[0], 'M'));
						++itListe;
					}
					else if (**itListe == "Hd"){
						++itListe;
						QString* valeur = *itListe;
						++itListe;
						cout << instant << "*" << valeur->toDouble() << endl;
//						meteo.getCapt(StationMeteo::TypeCapteur::hailDuration)->addValue(instant, valeur->toDouble());
						++itListe;
					}
					else if (**itListe == "Hi"){
						++itListe;
						QString* valeur = *itListe;
						++itListe;
						cout << instant << "*" << valeur->toDouble() << endl;
//						meteo.getCapt(StationMeteo::TypeCapteur::hailIntensity)->addValue(instant, valeur->toDouble());
						++itListe;
					}
					else if (**itListe == "Th"){
						++itListe;
						QString* valeur = *itListe;
						++itListe;
						cout << instant << "*" << valeur->toDouble() << endl;
//						meteo.getCapt(StationMeteo::TypeCapteur::heatTemperature)->addValue(instant, Convertisseur::convertTemperature(valeur->toDouble(), (*itListe)->toStdString()[0], 'C'));
						++itListe;
					}
					else if (**itListe == "Vh"){
						++itListe;
						QString* valeur = *itListe;
						++itListe;
						cout << instant << "*" << valeur->toDouble() << endl;
//						meteo.getCapt(StationMeteo::TypeCapteur::heatVoltage)->addValue(instant, valeur->toDouble());
						++itListe;
					}
					else if (**itListe == "Vs"){
						++itListe;
						QString* valeur = *itListe;
						++itListe;
						cout << instant << "*" << valeur->toDouble() << endl;
//						meteo.getCapt(StationMeteo::TypeCapteur::supplyVoltage)->addValue(instant, valeur->toDouble());
						++itListe;
					}
					else if (**itListe == "Vr"){
						++itListe;
						QString* valeur = *itListe;
						++itListe;
						cout << instant << "*" << valeur->toDouble() << endl;
//						meteo.getCapt(StationMeteo::TypeCapteur::refVoltage)->addValue(instant, valeur->toDouble());
						++itListe;
					}
					else {
						break;
					}
				}
			}
			itRetour = retour->begin();
			for (; itRetour!= retour->end(); ++itRetour){
				QList<QString*>::Iterator itListe = (*itRetour)->begin();
				for (; itListe != (*itRetour)->end(); ++itListe){
					delete (*itListe);
				}
				delete *itRetour;
			}
			delete retour;
		}
	}
	else if (sl.first() == "1"){
		sl.removeFirst();
		/** A lot of work to do **/
	}
	else if (sl.first() == "2"){
		sl.removeFirst();
//		ui->te_answer->setText(sl.first());
		cout << sl.first().toStdString() << endl;
	}
}
