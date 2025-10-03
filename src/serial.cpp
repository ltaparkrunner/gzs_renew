#include <QDebug>
#include "serial.h"

/*
 *
 * src/serial.h src/serial.cpp
 */
serial::serial(QSerialPortInfo &spi, QObject *parent):
    QObject(parent)
,   sp (new QSerialPort(spi))
,   eqpNum (-1)
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

void serial::requestEqpNum(){
    char tb[] = {0x24, 0x30, 0x30, 0x4d, 0x44, 0x31, 0x0d };
    QByteArray txbuf = QByteArray(tb);
    connect(sp, &QSerialPort::readyRead, this, &serial::parseNum);
    connect(sp, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            [&](QSerialPort::SerialPortError e){ eMsg = "An error " + sp->errorString() + " occured while reading data from the port " + sp->portName();
            eqpNum = -1;
            emit this->errMsg();
    });
//    qint64 bw = sp->writeData(tb, 7);
    sp->write(txbuf);
    qDebug() << "Just after sp->write(txbuf)";
}

QSerialPort * serial::getptr(){
    return sp;
}

int serial::getEqpNum(){
    return eqpNum;
}

void serial::parseNum() {
    QByteArray rxbuf(13, '\0');
    rxbuf = sp->readAll();
    int num1, num2;
    if(rxbuf[8] >= '0' && rxbuf[8] <= '9') num1 = rxbuf[8] - '0';
    else if(rxbuf[8] >= 'A' && rxbuf[8] <= 'F') num1 = rxbuf[8] - 'A' + 10;
    else num1 = -1;

    if(rxbuf[9] >= '0' && rxbuf[9] <= '9') num2 = rxbuf[9] - '0';
    else if(rxbuf[9] >= 'A' && rxbuf[9] <= 'F') num2 = rxbuf[9] - 'A' + 10;
    else num2 = -1;

    qDebug() << "Received rxbuf[8]: " << rxbuf[8] << " rxbuf[9]: " << rxbuf[9];
    eqpNum = num1 * 10 + num2;
    qDebug() << "Received rxbuf[8]: " << num1 << " rxbuf[9]: " << num2;
    emit readyRead();
}

QString serial::getEMsg(){
    return eMsg;
}
