#include "RealSerialPorts.h"


RealSerialPorts::RealSerialPorts(QMap<int, QString> _moxaAssociations, int _baudRate){
	m_moxaAssociations = _moxaAssociations;
	m_baudRate = _baudRate;
	m_isError = false;
	linkSerialPorts();
}


RealSerialPorts::~RealSerialPorts(void){
	QMap<int, QSerialPort*>::iterator it;

	for (it = m_serialPortAssociations.begin(); it != m_serialPortAssociations.end(); it++){
		QSerialPort * sp = it.value();
		sp->close();
		delete sp;
	}

	m_serialPortAssociations.clear();
}


void RealSerialPorts::recieveData(int moxaPortNumber, QString data){
	if (!m_serialPortAssociations.contains(moxaPortNumber))
		return;

	m_serialPortAssociations[moxaPortNumber]->write((data + "\r\n").toStdString().c_str());
	m_serialPortAssociations[moxaPortNumber]->flush();
}

bool RealSerialPorts::isError() {
	return m_isError;
}

QString RealSerialPorts::getError(){
	return m_errorMessage;
}

void RealSerialPorts::linkSerialPorts(){
	QMap<int, QString>::iterator it;

	for (it = m_moxaAssociations.begin(); it != m_moxaAssociations.end(); it++){
		try {
			QSerialPort * serial = new QSerialPort();
			serial->setPortName(it.value());
			
			if (serial->open(QIODevice::WriteOnly)){
				serial->setBaudRate(m_baudRate, QSerialPort::Output);
				serial->setDataBits(QSerialPort::Data8);
				serial->setParity(QSerialPort::NoParity);
				serial->setStopBits(QSerialPort::OneStop);
				serial->setFlowControl(QSerialPort::NoFlowControl);
				m_serialPortAssociations[it.key()] = serial;
				continue;
			}
			else {
				m_isError = true;
				m_errorMessage += "Cannot connect to port " + it.value() + " [" + serial->errorString() + "]\n";
			}
			delete serial;
		}
		catch (...){
			m_isError = true;
			m_errorMessage += "Failt while connecting to port " + it.value() + "\n";
		}
	}
}