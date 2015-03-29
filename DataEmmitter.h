#pragma once

#include "Atoms.h"
#include <qobject.h>
#include <qelapsedtimer.h>
#include "Utils.h"

class DataEmmitter : public QObject {
    Q_OBJECT
private:
	QList<nmeaLogSentence> sentences;
	bool isInfinityLoop;
public:
	DataEmmitter(QList<nmeaLogSentence> _sentences, bool _isInfinityLoop = false);
	~DataEmmitter(void);

signals:
	void sendData(int moxaPortNumber, QString data);

public slots:
    void start();
};

