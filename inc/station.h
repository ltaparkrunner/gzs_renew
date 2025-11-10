#ifndef STATION_H
#define STATION_H

#include <QObject>
#include <QString>

#include "clibinc.h"

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
