#include "NTConfig.h"


NTConfig::NTConfig(const QString fileLocation, const int moxaPortsCount){
	valid = false;

	if (!QFile::exists(fileLocation)){
		error = "Config file " + fileLocation + " not exists";
		return;
	}

	QSettings settings(fileLocation, QSettings::IniFormat);
	
	settings.beginGroup("network");
	m_baudRate = settings.value("baud-rate", "9600").toInt();
	for (int i = 0; i < moxaPortsCount; i++){
		QString cfgKey = QString("moxa") + QString::number(i + 1);
		QString cfgValue = settings.value(cfgKey, "AXAXA").value<QString>();
		m_moxaAssociations[i + 1] = cfgValue;
	}

	settings.endGroup();

	settings.beginGroup("logic");
	m_isInfinityLoop = settings.value("infinity-loop", "false").toBool();

	valid = true;
}



NTConfig::~NTConfig(void){

}


bool NTConfig::isValid(){
	return this->valid;
}

bool NTConfig::isInfinityLoop(){
	return this->m_isInfinityLoop;
}

QString NTConfig::getError(){
	return this->error;
}

int NTConfig::baudRate(){
	return this->m_baudRate;
}

/**
 * Get moxa port association (moxa1 - moxaN)
 */

QString NTConfig::getMoxaPort(int moxaId){
	
	if (!m_moxaAssociations.contains(moxaId))
		return this->getInvalidPortName();

	return m_moxaAssociations.value(moxaId);
}

QString NTConfig::getInvalidPortName(){
	return "INVALIDCONFIGPORT";
}

QMap<int, QString> NTConfig::getMoxaAssociations(){
	return m_moxaAssociations;
}