#ifndef MONITORING_H
#define MONITORING_H

#include <QObject>
#include <QTimer>
#include <QSerialPort>

class monitoring: public QObject
{
    Q_OBJECT
public:
    monitoring(QObject *parent);
private:
    QTimer *mtr;
    int pollNSend();
    QSerialPort sprt;
};

#endif // MONITORING_H
