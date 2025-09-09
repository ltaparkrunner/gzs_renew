#include "monitoring.h"

monitoring::monitoring(QObject *parent):
    QObject(parent)
,   mtr (new QTimer(this))
,   sprt (new QSerialPort(this))
{
    connect(mtr, &QTimer::timeout, this, &monitoring::pollNSend);
    mtr->setInterval(1000);
    mtr->start();
}

int monitoring::pollNSend() {

    return 0;
}
