#include "Utils.h"

void delay( int millisecondsToWait ){
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
}