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
	m_plot = new Plot();
	ui->plotLayout->addWidget(m_plot, 1, 0);
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
}

MainWindow::~MainWindow()
{
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
	// A décommenter si on supprime de faire
	//timer.setInterval(ui->dial_delai_acquisitionSpin->value()*1000);
}

void MainWindow::pauseAcquisition()
{
	timer.stop();
}

void MainWindow::stopAcquisition()
{
	timer.stop();
	com->unConfigure();
}
