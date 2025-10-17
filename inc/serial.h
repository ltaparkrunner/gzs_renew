#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>

class serial : public QObject
{
    Q_OBJECT
public:
    serial(QSerialPortInfo &spi, QObject *parent = nullptr);
    bool open();
    QString portName();
    void requestEqpNum();
    int getEqpNum();
    QSerialPort * getptr();
    QString getEMsg();
    bool isOpen();
    void close();
signals:
    void readyRead();
    void errMsg();

private:
    void parseNum();
    QSerialPort *sp;
    QString eMsg;
    int eqpNum;
//    QByteArray txbuf; //= {0x24, 0x30, 0x30, 0x4d, 0x44, 0x31, 0x0d };
//    QByteArray rxbuf; // = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
};

#endif // SERIAL_H
