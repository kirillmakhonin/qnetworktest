#pragma once

#include <qobject.h>
#include <qmap.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/qserialport.h>
#include <QtSerialPort/qserialportinfo.h>

class RealSerialPorts : public QObject {
	Q_OBJECT

private:
	QMap<int, QString> m_moxaAssociations;
	QMap<int, QSerialPort *> m_serialPortAssociations;

	int m_baudRate;

	bool m_isError;
	QString m_errorMessage;

public:
	RealSerialPorts(QMap<int, QString> _moxaAssociations, int _baudRate);
	~RealSerialPorts(void);

public:
	bool isError();
	QString getError();

public slots:
	void recieveData(int moxaPortNumber, QString data);


protected:
	void linkSerialPorts();
};

