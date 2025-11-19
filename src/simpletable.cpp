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

//    QTimer::singleShot(7500, this, &simpleTable::publish);
}

simpleTable::simpleTable(QObject *parent):
    QObject(parent)
,   stf (new QFile(""))
,   rowsNum (2)
{
    int i, j;

    dim.width = 6;
    dim.height = 3;

    ttl[0].offset = 53;
    ttl[1].offset = 137;
    ttl[2].offset = 120;
    ttl[3].offset = 120;
    ttl[4].offset = 199;
    ttl[5].offset = 201;

    ttl[0].nm = "Номер режима";
    ttl[1].nm = "Длительность подачи газовой смеси";
    ttl[2].nm = "Концентрация газовой смеси (%, ppm)";
    ttl[3].nm = "Концентрация газовой смеси (%, ppm)";
    ttl[4].nm = "Суммарный поток газовой смеси (ml/min)";
    ttl[5].nm = "Относительная влажность газовой смеси (%)";

    for(i = 0; i < 2; i++){
        dt[i].num_row = i+1;
        dt[i].duration = QTime::fromString("0:00:30","h:mm:ss");
        dt[i].cncntr1 = 0;
        dt[i].cncntr2 = 0;
        dt[i].sumStream = 200;
        dt[i].relatHumidity = 100;
    }

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
//    for(i = 0; i < 4; i++){
    for(i = 0; i < 2; i++){
        lc.append(QString::number(dt[i].num_row));
        lc.append(dt[i].duration.toString("hh:mm:ss"));
        lc.append(QString::number(dt[i].cncntr1));
        lc.append(QString::number(dt[i].cncntr2));
        lc.append(QString::number(dt[i].sumStream));
        lc.append(QString::number(dt[i].relatHumidity));
    }
//    qDebug() << "before toQML_smplTbl(lc)";
    emit toQML_smplTbl(lc);
}

void simpleTable::fromQML_smplTableCompleted(){
    publish();
}

bool simpleTable::isTable(){
    return true;
}

int color(int col, int row, QString color){
    return 0;
}
