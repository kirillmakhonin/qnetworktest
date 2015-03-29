#pragma once

#include <QSettings>
#include <qstring.h>
#include <qfile.h>
#include <qmap.h>
#include <qdebug.h>




class NTConfig {
private:
	bool valid;
	QString error;
	QSettings settings;


private:
	int m_baudRate;
	QMap<int, QString> m_moxaAssociations;
	bool m_isInfinityLoop;

public:
	NTConfig(const QString fileLocation, const int moxaPortsCount);
	~NTConfig(void);

	bool isValid();
	bool isInfinityLoop();
	QString getError();

	int baudRate();
	QString getMoxaPort(int moxaId);
	QString getInvalidPortName();
	QMap<int, QString> getMoxaAssociations();


};

