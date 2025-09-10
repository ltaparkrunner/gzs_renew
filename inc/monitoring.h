#ifndef MONITORING_H
#define MONITORING_H

#include <QObject>
#include <QTimer>
#include <QSerialPort>

enum pcs_consts{
    START_POLL,
    EQUIP_START_RESP,
    FIRST_SNSR_Q,
    FIRST_SNSR_RESP,
    SECOND_SNSR_Q,
    SECOND_SNSR_RESP,
    THIRD_SNSR_Q,
    THIRD_SNSR_RESP,
    FIRST_VLV_CMD,
    FIRST_VLV_RESP,
    SECOND_VLV_CMD,
    SECOND_VLV_RESP,
    THIRD_VLV_CMD,
    THIRD_VLV_RESP,
    FOURTH_VLV_CMD,
    FOURTH_VLV_RESP,
    FIRST_SNSR_POLL_Q,
    FIRST_SNSR_POLL_RESP,
    SECOND_SNSR_POLL_Q,
    SECOND_SNSR_POLL_RESP,
    THIRD_SNSR_POLL_Q,
    THIRD_SNSR_POLL_RESP,
    FIRST_VLV_POLL_CMD,
    FIRST_VLV_POLL_RESP,
    SECOND_VLV_POLL_CMD,
    SECOND_VLV_POLL_RESP,
    THIRD_VLV_POLL_CMD,
    THIRD_VLV_POLL_RESP,
    FOURTH_VLV_POLL_CMD,
    FOURTH_VLV_POLL_RESP
};

class monitoring: public QObject
{
    Q_OBJECT
public:
    monitoring(QObject *parent);
private:
    QTimer *mtr;
    int pollNSend();
    QSerialPort *sprt;
    void poll2(QSerialPort::DataBits db);
    int pollCycle();
    int procError();
    int pollCycleJumps(pcs_consts pcsc);
    enum pcs_consts pcsc;
    int snsMeanArray[3];
};

#endif // MONITORING_H
