#include "simpletable.h"
#include "wfiles.h"
#include <QTextStream>
#include <QStringList>
#include <QDebug>

#include <QTimer>
//#include <QList>

simpleTable::simpleTable(QString tn, QObject *parent):
    QObject(parent)
,   stf (new QFile(tn))
,   rowsNum (4)
{
    int i, j;
//    stf = new QFile(tn);
    int res = wfiles::checkFile(stf);
    if (!stf->open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "simpleTable Could not open file for reading:" << stf->errorString();
        return;
    }
    QTextStream in(stf);
    QStringList sl = in.readLine().split(',');
    dim.width = sl[0].toInt();
    dim.height = sl[1].toInt();

    for(i = 0; i < 6; i++){
        sl = in.readLine().split(',');
//        st.ttl->operator [](i).offset = sl[1].toInt();
        ttl[i].offset = sl[1].toInt();
    }

    for(i = 0; i < 6; i++){
        sl = in.readLine().split(',');
        ttl[i].nm = sl[2]; //.toInt();
    }
    for(i = 0; i < 4; i++){
        sl = in.readLine().split(',');
        dt[i].num_row = sl[2].toInt();
        sl = in.readLine().split(',');
        dt[i].duration = QTime::fromString(sl[2],"h:mm:ss");
        sl = in.readLine().split(',');
        dt[i].cncntr1 = sl[2].toInt();
        sl = in.readLine().split(',');
        dt[i].cncntr2 = sl[2].toInt();
        sl = in.readLine().split(',');
        dt[i].sumStream = sl[2].toInt();
        sl = in.readLine().split(',');
        dt[i].relatHumidity = sl[2].toInt();
    }
    QTimer::singleShot(7500, this, &simpleTable::publish);
}

void simpleTable::publish(){
//    qDebug() << "simpleTable::publish() the beginning";
    QList<QString> lc;
    int i;
    for(i = 0; i < 6; i++){
        lc.append(QString::number(ttl[i].offset));
    }
    for(i = 0; i < 6; i++){
        lc.append(ttl[i].nm);
    }
    for(i = 0; i < 4; i++){
        lc.append(QString::number(dt[i].num_row));
        lc.append(dt[i].duration.toString("hh:mm:ss"));
        lc.append(QString::number(dt[i].cncntr1));
        lc.append(QString::number(dt[i].cncntr2));
        lc.append(QString::number(dt[i].sumStream));
        lc.append(QString::number(dt[i].relatHumidity));
    }
    qDebug() << "before toQML_smplTbl(lc)";
    toQML_smplTbl(lc);
}
