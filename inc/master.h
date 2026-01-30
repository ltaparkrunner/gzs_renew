#ifndef VMMAIN_H
#define VMMAIN_H

#include <QObject>
#include <QTimer>
#include <QSerialPortInfo>
#include <QProcess>

#include "simpletable.h"
#include "calibrtable.h"
#include "params.h"
#include "serial.h"
#include "station.h"

#include "mycppobject.h"

class master : public QObject
{
    Q_OBJECT
public:
    explicit master(/*QString fname = "Test.csv",*/ QString cmbn = "Combo.str", QString tn = "Table.cfg", QString cn = "Calibr.str", int stn = 6, int time = 1000, QObject *parent = nullptr);
    ~master();
    void sendPbData();
    void ch_val();
signals:
    void toQML_message(QString msg);
    void toQML_data(QList<QString> pb);
    void toQML_comList(QList<QString> lc);
    void toQML_initListString(QList<QString> lc, int c);
    void toQML_startMainW();

public slots:
    void openefile_fromQML(QString urlList);
    void startTest_fromQML();
    void stopTest_fromQML();
    void eqpRqst_fromQML(QString pn);
    void calibClosed_fromQML();
    void calibOpened_fromQML();
    void fromQML_btnStart(/*QList<QString> lc*/);
    void fromQML_btnStop();
    void fromQML_btn_blowing();
    void fromQML_ApplicationWindowCompleted();
private:
//    int tm;
//    QTimer* test_tmr;
    int startTest();
    int stopTest();
    int startInit();
    void appendSerials();
//    char station_calc(unsigned int num);

//    void pwExit(/*int ec, QProcess::ExitStatus es*/);
//    unsigned char     crc_pr;
    QList<QString> cports;
    QList<QSerialPortInfo> serialPortInfos;
    serial *sp;
    station *gst;
    bool isBlowing;
//    QProcess *proc;
public:
    Parameters params;
    int st_num;
    int crc;
//    MyCppObject mo;
};

#endif // VMMAIN_H
