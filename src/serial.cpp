#include "serial.h"
/*
 *
 * src/serial.h src/serial.cpp
 */
serial::serial(QSerialPortInfo &spi, QObject *parent):
    QObject(parent)
,   sp (new QSerialPort(spi))
//,   txbuf(QByteArray({0x24, 0x30, 0x30, 0x4d, 0x44, 0x31, 0x0d }))
//,   rxbuf({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})
{
    sp->setPortName(spi.portName());
}

bool serial::open(){
    sp->setBaudRate(115200);
    return sp->open(QIODevice::ReadWrite);
}

QString serial::portName(){
    return sp->portName();
}

void requestNum(){
    char tb[] = {0x24, 0x30, 0x30, 0x4d, 0x44, 0x31, 0x0d };
    QByteArray txbuf = QByteArray(tb);
//    connect()
}

int respondNum(){
    return -1;
}
