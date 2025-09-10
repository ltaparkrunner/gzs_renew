#include "monitoring.h"

monitoring::monitoring(QObject *parent):
    QObject(parent)
,   mtr (new QTimer(this))
,   sprt (new QSerialPort(this))
{
    connect(mtr, &QTimer::timeout, this, &monitoring::pollNSend);
    mtr->setInterval(1000);
    mtr->start();
    sprt->setBaudRate(115200);
}

int monitoring::pollNSend() {
//    connect(test_tmr, &QTimer::timeout, this, &master::sendPbData);
    pcsc = FIRST_SNSR_POLL_RESP;
    connect(sprt, &QSerialPort::errorOccurred, this, &monitoring::procError);
    connect(sprt, &QSerialPort::readyRead, this, &monitoring::pollCycle);
//    QByteArray wBuff = {0x2, 0x5, 0x7};
//    sprt->write(wBuff);
    return 0;
}

int monitoring::pollCycle(){
    QByteArray data = sprt->readAll();
    switch(pcsc){
        case FIRST_SNSR_POLL_RESP:
            snsMeanArray[1] = data[5]*256 +data[6];
            pcsc = SECOND_SNSR_POLL_RESP;
//            QByteArray wBuff = {0x2, 0x5, 0x7};
//            sprt->write(wBuff);
        break;
        case SECOND_SNSR_POLL_RESP:
            snsMeanArray[1] = data[5]*256 +data[6];
            pcsc = SECOND_SNSR_POLL_RESP;
//            QByteArray wBuff = {0x2, 0x5, 0x7};
//            sprt->write(wBuff);
        break;
    default: break;
    }

    return 0;
}

void monitoring::poll2(QSerialPort::DataBits db){

}

int monitoring::procError(){
    return 0;
}
