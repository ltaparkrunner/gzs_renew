#ifndef STATION_H
#define STATION_H

#include <QObject>
#include <QString>

extern "C" {
    #include "sio.h"
    #include "i7k.h"
    #include "i87000_lnx.h"
}

const int RBUF_SIZE = 80;
const int TBUF_SIZE = 20;

class station : public QObject
{
        Q_OBJECT
public:
    station(QString portn, int s_num, int &err, QObject *parent = nullptr);
    int if_init(){return init_err;}
private:
    QString pn;
    int init_err;
    int sp;
//    int snum;
};

#endif // STATION_H
