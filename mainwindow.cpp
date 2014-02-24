#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <communication/serialport.h>
#include <QMessageBox>

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
	ui->dial_delai_acquisition->setMinimum(1);
	ui->dial_delai_acquisition->setMaximum(3600);
	connect(ui->b_play, SIGNAL(clicked()), this, SLOT(launchAcquisition()));
	connect(ui->m_saveData, SIGNAL(triggered()), this, SLOT(saveData()));
	connect(ui->m_loadData, SIGNAL(triggered()), this, SLOT(loadData()));
	connect(ui->m_about, SIGNAL(triggered()), this, SLOT(about()));
	connect(ui->m_aboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::createCommunication()
{
	com = new SerialPort(this);
	if (!com->isConfigured()){
		com->configurer();
	}
}

void MainWindow::launchAcquisition()
{
	if (com == NULL){
		QMessageBox::warning(0, "Error !", "Veuillez configurer la communication avant de commencer des mesures");
		return;
	}
	//while(true){
		//TODO : lancer mesures de manière périodique
	//}
}

void MainWindow::saveData()
{

}

void MainWindow::loadData()
{

}

void MainWindow::about()
{

}
