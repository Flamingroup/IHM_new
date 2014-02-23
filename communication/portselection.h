#ifndef PORTSELECTION_H
#define PORTSELECTION_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <map>
#include "qextserialport.h"

using std::map;


class PortSelection : public QDialog
{

    Q_OBJECT

public:
    PortSelection(QextSerialPort* port, QWidget *parent = 0);
private:

    map<QString, BaudRateType> map_baud;
    map<QString, DataBitsType> map_dataBits;
    map<QString, FlowType> map_flowControl;
    map<QString, ParityType> map_parity;
    map<QString, StopBitsType> map_stopBits;


    QPushButton* m_ok;
    QPushButton* m_cancel;

    QextSerialPort* m_port;

    QComboBox *box_baud;
    QComboBox *box_dataBits;
    QComboBox *box_flowControl;
    QComboBox *box_parity;
    QComboBox *box_stopBit;
    QLineEdit *m_name;

public slots:
    void initPort(void);

private:
    void initMap(void);

};

#endif // PORTSELECTION_H
