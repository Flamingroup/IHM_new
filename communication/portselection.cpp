#include "portselection.h"
#include <QFormLayout>
#include <QComboBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <communication/serialport.h>
#include <QString>

PortSelection::PortSelection(QextSerialPort *port, QWidget *parent) :
    QDialog(parent)
{


    initMap();

    setModal(true);

    m_port = port;

    box_baud = new QComboBox;
    box_baud->addItem("BAUD9600");
    box_baud->addItem("BAUD19200");
    box_baud->addItem("BAUD115200");

    box_dataBits = new QComboBox;
    box_dataBits->addItem("DATA_8");
    box_dataBits->addItem("DATA_7");
    box_dataBits->addItem("DATA_6");
    box_dataBits->addItem("DATA_5");

    box_flowControl = new QComboBox;
    box_flowControl->addItem("FLOW_OFF");           // No flow control
    box_flowControl->addItem("FLOW_HARDWARE");      // Hardware (RTS/CTS) flow control
    box_flowControl->addItem("FLOW_XONXOFF");       // Software (XON/XOFF) flow control

    box_parity = new QComboBox;
    box_parity->addItem("PAR_NONE");
    box_parity->addItem("PAR_SPACE");
    box_parity->addItem("PAR_EVEN");
    box_parity->addItem("PAR_ODD");

    box_stopBit = new QComboBox;
    box_stopBit->addItem("STOP_1");
    box_stopBit->addItem("STOP_2");

	m_name = new QLineEdit;

    QFormLayout* formlayout = new QFormLayout;
    formlayout->addRow("Port name : ", m_name);
    formlayout->addRow("Baud rate", box_baud);
    formlayout->addRow("Number of data bits", box_dataBits);
    formlayout->addRow("Flow control", box_flowControl);
    formlayout->addRow("Parity", box_parity);
    formlayout->addRow("Number of stop bits", box_stopBit);


    m_ok = new QPushButton("Ok", this);
    m_cancel = new QPushButton("Cancel", this);

	QObject::connect(m_ok, SIGNAL(clicked()), this, SLOT(initPort()));
	QObject::connect(m_ok, SIGNAL(clicked()), parent, SLOT(validateConfig()));
    QObject::connect(m_cancel, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(m_ok);
    buttonsLayout->addWidget(m_cancel);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formlayout);
    mainLayout->addLayout(buttonsLayout);

    this->setLayout(mainLayout);



}


void PortSelection::initMap(void)
{
    map_baud["BAUD9600"] = BAUD9600;
    map_baud["BAUD19200"] = BAUD19200;
    map_baud["BAUD115200"] = BAUD115200;

    map_dataBits["DATA_5"] = DATA_5;
    map_dataBits["DATA_6"] = DATA_6;
    map_dataBits["DATA_7"] = DATA_7;
    map_dataBits["DATA_8"] = DATA_8;

    map_flowControl["FLOW_OFF"] = FLOW_OFF;
    map_flowControl["FLOW_HARDWARE"] = FLOW_HARDWARE;
    map_flowControl["FLOW_XONXOFF"] = FLOW_XONXOFF;

    map_parity["PAR_SPACE"] = PAR_SPACE;
    map_parity["PAR_NONE"] = PAR_NONE;
    map_parity["PAR_EVEN"] = PAR_EVEN;
    map_parity["PAR_ODD"] = PAR_ODD;

    map_stopBits["STOP_1"] = STOP_1;
    map_stopBits["STOP_2"] = STOP_2;
}

void PortSelection::initPort(void)
{


    m_port->setPortName(m_name->text());
    m_port->setBaudRate(map_baud.find(box_baud->currentText())->second);
    m_port->setDataBits(map_dataBits.find(box_dataBits->currentText())->second);
    m_port->setFlowControl(map_flowControl.find(box_flowControl->currentText())->second);
    m_port->setParity(map_parity.find(box_parity->currentText())->second);
	m_port->setStopBits(map_stopBits.find(box_stopBit->currentText())->second);
	// Fonctionne comme ça sans le find normalement :
	//m_port->setStopBits(map_stopBits[box_stopBit->currentText()]);

    this->close();
}
