#include "station.h"
#include <locale>
#include <QDebug>
#include <QMessageBox>

static char rbuf[RBUF_SIZE] = {0};
static char name_tx[TBUF_SIZE] = {0};
__tod_t texp;
DWORD _87017_TX[TBUF_SIZE] = {0};
float _87017_RX[RBUF_SIZE] = {0};
DWORD _87024_TX[TBUF_SIZE] = {0};
float _87024_RX[RBUF_SIZE] = {0};
DWORD _87024_2_TX[TBUF_SIZE] = {0};
float _87024_2_RX[RBUF_SIZE] = {0};
DWORD _87063_TX[TBUF_SIZE] = {0};
float _87063_RX[RBUF_SIZE] = {0};
char szSend[RBUF_SIZE], szReceive[RBUF_SIZE];

unsigned char PUMP_STATE = 0;

station::station(QString portn, int s_num, int &rerr, QObject *parent):
    QObject(parent)
,   pn(portn)
,   init_err(-1)
//,   snum(s_num)
{
//    char *pn_str;
    int retVal;
    char* oldlocale = setlocale(LC_NUMERIC, NULL);
    sp = sio_open(pn.toStdString().c_str(), B115200, DATA_BITS_8, NO_PARITY, ONE_STOP_BIT);
    qDebug() << "sp = " << sp;
    if(sp <= 0) { init_err = -1; goto s_port_unavalable;}

    sio_set_noncan(sp);
    sio_set_timer(sp, 0, 1);

    sprintf(name_tx, "$00M\r");
    retVal = i7k_send_readt_cs(sp, name_tx, rbuf, RBUF_SIZE, &texp);
    if((((rbuf[8]-'0')<<4) + (rbuf[9]-'0')) != s_num ) { init_err = -2; goto wrong_station_num;}

    WORD err;
    _87017_TX[0] = sp;
    _87017_TX[1] = 0;
    _87017_TX[2] = 0x87017;
    _87017_TX[3] = 1;
    _87017_TX[4] = 100;
    _87017_TX[5] = 0;
    _87017_TX[6] = 1;
    _87017_TX[7] = 0;

    err = AnalogInAll_87K(_87017_TX, _87017_RX, szSend, szReceive);
    if(err != 0){ init_err = -3; goto wrong_87017;}

    _87024_TX[0] = sp;          // port num
    _87024_TX[1] = 1;           // Module address
    _87024_TX[2] = 0x87024;     // Module ID
    _87024_TX[3] = 1;           // Checksum enable
    _87024_TX[4] = 100;         // Timeout = 0.1 sec
    _87024_TX[6] = 1;           // string debug
    _87024_TX[7] = 0;           // Slot number

    _87024_TX[5] = 0;           // Channel No.
    _87024_RX[0] = 0.000;        // Digital out

    setlocale(LC_NUMERIC, "POSIX");
    err = AnalogOut_87K(_87024_TX, _87024_RX, szSend, szReceive);
    if(err != 0){ init_err = -4; goto wrong_87024;}

    _87024_TX[5] = 1;           // Channel No.
    _87024_RX[0] = 0.000;        // Digital out
    err = AnalogOut_87K(_87024_TX, _87024_RX, szSend, szReceive);
    if(err != 0){ init_err = -4; goto wrong_87024;}

    _87024_TX[5] = 2;           // Channel No.
    _87024_RX[0] = 0.000;        // Digital out
    err = AnalogOut_87K(_87024_TX, _87024_RX, szSend, szReceive);
    if(err != 0){ init_err = -4; goto wrong_87024;}

    _87024_TX[5] = 3;           // Channel No.
    _87024_RX[0] = 0.000;        // Digital out
    err = AnalogOut_87K(_87024_TX, _87024_RX, szSend, szReceive);
    if(err != 0){ init_err = -4; goto wrong_87024;}

    _87024_2_TX[0] = sp;          // port num
    _87024_2_TX[1] = 1;           // Module address
    _87024_2_TX[2] = 0x87024;     // Module ID
    _87024_2_TX[3] = 1;           // Checksum enable
    _87024_2_TX[4] = 100;         // Timeout = 0.1 sec
    _87024_2_TX[6] = 1;           // string debug
    _87024_2_TX[7] = 0;           // Slot number

    _87024_2_TX[5] = 0;           // Channel No.
    _87024_2_RX[0] = 0.000;        // Digital out
    err = AnalogOut_87K(_87024_2_TX, _87024_2_RX, szSend, szReceive);
    if(err != 0){ init_err = -5; goto wrong_87024_2;}

    _87024_2_TX[5] = 1;           // Channel No.
    _87024_2_RX[0] = 0.000;        // Digital out
    err = AnalogOut_87K(_87024_2_TX, _87024_2_RX, szSend, szReceive);
    if(err != 0){ init_err = -5; goto wrong_87024_2;}

    _87024_2_TX[5] = 2;           // Channel No.
    _87024_2_RX[0] = 0.000;        // Digital out
    err = AnalogOut_87K(_87024_2_TX, _87024_2_RX, szSend, szReceive);
    if(err != 0){ init_err = -5; goto wrong_87024_2;}

    _87024_2_TX[5] = 3;           // Channel No.
    _87024_2_RX[0] = 0.000;        // Digital out
    err = AnalogOut_87K(_87024_2_TX, _87024_2_RX, szSend, szReceive);
    setlocale(LC_NUMERIC, oldlocale);
    if(err != 0){ init_err = -5; goto wrong_87024_2;}

    _87063_TX[0] = sp;          // port num
    _87063_TX[1] = 3;           // Module address
    _87063_TX[2] = 0x87063;     // Module ID
    _87063_TX[3] = 1;           // Checksum enable
    _87063_TX[4] = 100;         // Timeout = 0.1 sec
    _87063_TX[5] = PUMP_STATE;           // Channel No.
    _87063_TX[6] = 1;           // string debug
    _87063_TX[7] = 0;           // Slot number

    _87063_TX[5] = 0;           // Channel No.
//    _87063_RX[0] = 0.000;        // Digital out
    err = DigitalOut_87K(_87063_TX, _87063_RX, szSend, szReceive);
    if(err != 0){ init_err = -5; goto wrong_87063;}

    init_err = 0; rerr = init_err;
    return;

    s_port_unavalable:
    wrong_station_num:

    wrong_87017:
    wrong_87024:
    wrong_87024_2:
    wrong_87063:

    sio_close(sp);

    rerr = init_err;
    qDebug() << "station ERR: " << init_err;
    return;

}

//bool station::if_init(){}
