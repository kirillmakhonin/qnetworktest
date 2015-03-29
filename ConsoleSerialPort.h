#pragma once

#include <qobject.h>
#include <iostream>

class ConsoleSerialPort : public QObject {
    Q_OBJECT
public:
	ConsoleSerialPort(void);
	~ConsoleSerialPort(void);
	
public slots:
	void recieveData(int moxaPortNumber, QString data);
};

