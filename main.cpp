
#include <QtCore/QCoreApplication>

#include <qstringlist.h>
#include <qdebug.h>
#include <qcommandlineparser.h>
#include <qfile.h>
#include <QElapsedTimer>
#include <QTime>
#include <qthread.h>

#include "NTConfig.h"
#include <stdio.h>
#include <iostream>

#include "Atoms.h"
#include "DataEmmitter.h"
#include "ConsoleSerialPort.h"
#include "RealSerialPorts.h"

appStartArguments initApp(QCoreApplication * app){
	appStartArguments ags;
	// set manufacturer
	QCoreApplication::setApplicationName("YACHT NTW TEST");
    QCoreApplication::setApplicationVersion("0.2");
	// configure parser and parse
	QCommandLineParser parser;
    
	parser.setApplicationDescription("APP helper");
    parser.addHelpOption();
    parser.addVersionOption();
	parser.addPositionalArgument("nmealog", "NMEA log file for send");

	parser.process(*app);


	const QStringList args = parser.positionalArguments();

	ags.logfile = (args.size() > 0) ? args.at(0) : "log.nmealog";
	ags.configFile = "config.ini";

	return ags;
}

bool fillSentence(QString line, nmeaLogSentence & sentence){
	line = line.trimmed();
	
	QStringList entries = line.split(' ');
	
	if (entries.size() != 3)
		return false;

	long long time = entries[0].toLongLong();
	int moxaPort = entries[1].mid(3).toInt();

	if (time <= 0 || moxaPort <= 0)
		return false;

	sentence.time = time;
	sentence.moxaID = moxaPort;
	sentence.message = entries[2];

	return true;
}

void sentenceNormalizeTimes(QList<nmeaLogSentence> & list){
	if (list.size() < 1)
		return;

	long long startTime = list.begin()->time;

	for (QList<nmeaLogSentence>::iterator p = list.begin(); p!= list.end(); p++)
		p->time -= startTime;
}

QList<nmeaLogSentence> parseSentences(QString fileName){
	QList<nmeaLogSentence> out;

	QFile inputFile(fileName);
	if (inputFile.open(QIODevice::ReadOnly)){

		QTextStream in(&inputFile);

		while (!in.atEnd()){
			nmeaLogSentence sentence;
			if (fillSentence(in.readLine(), sentence))
				out.append(sentence);
		}

		inputFile.close();
	}

	sentenceNormalizeTimes(out);

	return out;
}




int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	
	appStartArguments ags = initApp(&a);

	NTConfig cfg(ags.configFile, 6);

	if (!cfg.isValid()){
		std::cout << cfg.getError().toStdString();
		return 1;
	}

	if (!QFile::exists(ags.logfile)){
		std::cout << "log file " << ags.logfile.toStdString() << " not exists";
		return 1;
	}

	QList<nmeaLogSentence> sentences = parseSentences(ags.logfile);

	// add loop thread
	QThread * loopThread = new QThread(&a);

	DataEmmitter * de			= new DataEmmitter(sentences, cfg.isInfinityLoop());
	ConsoleSerialPort * csp		= new ConsoleSerialPort();
	RealSerialPorts * rsp		= new RealSerialPorts(cfg.getMoxaAssociations(), cfg.baudRate());

	if (rsp->isError()){
		std::cout << rsp->getError().toStdString() << std::endl;		
	}

	QObject::connect(de, SIGNAL(sendData(int, QString)), csp, SLOT(recieveData(int, QString)));
	QObject::connect(de, SIGNAL(sendData(int, QString)), rsp, SLOT(recieveData(int, QString)));

	de->moveToThread(loopThread);
	de->start();


	loopThread->wait();

	
	/*

	QStringList ports;

	QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

	for (QList<QSerialPortInfo>::iterator p = availablePorts.begin(); p!= availablePorts.end(); p++)
	{
		QSerialPortInfo port = *p;
		//Their is some sorting to do for just list the port I want, with vendor Id & product Id
		qDebug() << port.portName() << port.vendorIdentifier() << port.productIdentifier()
				 << port.hasProductIdentifier() << port.hasVendorIdentifier() << port.isBusy();
	}
	*/

	return 0;
	//return a.exec();
}


