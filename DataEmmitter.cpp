#include "DataEmmitter.h"


DataEmmitter::DataEmmitter(QList<nmeaLogSentence> _sentences, bool _isInfinityLoop){
	this->sentences = _sentences;
	this->isInfinityLoop = _isInfinityLoop;
}


DataEmmitter::~DataEmmitter(void){

}


void DataEmmitter::start(){
	do {		
		QList<nmeaLogSentence>::iterator nextSentence = sentences.begin();

		QElapsedTimer timer;
		timer.start();

		while (nextSentence != sentences.end()){
			if (nextSentence->time * 1000 > timer.elapsed())
				delay(nextSentence->time * 1000 - timer.elapsed());

			emit sendData(nextSentence->moxaID, nextSentence->message);

			nextSentence++;
		}


	} while (isInfinityLoop);

}