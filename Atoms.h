#pragma once

#include <qstring.h>

struct appStartArguments {
	QString logfile;
	QString configFile;
};

struct nmeaLogSentence {
	long long time;
	int moxaID;
	QString message;
};