#include "ConsoleSerialPort.h"


ConsoleSerialPort::ConsoleSerialPort(void){

}


ConsoleSerialPort::~ConsoleSerialPort(void){

}


void ConsoleSerialPort::recieveData(int moxaPortNumber, QString data){
	std::cout << "moxa port " << moxaPortNumber << " data: " << data.toStdString() << std::endl;
}