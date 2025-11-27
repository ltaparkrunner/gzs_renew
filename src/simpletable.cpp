#include "simpletable.h"
#include "wfiles.h"
#include <QTextStream>
#include <QStringList>
#include <QDebug>

#include <QMessageBox>
#include <QTimer>
//#include <QList>

QTime t0 = QTime::fromString("00:00:05", "hh:mm:ss");
QTime t1 = QTime::fromString("05:00:00", "hh:mm:ss");

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
    if(sl.length() < 2) goto parse_err;
//    bool ok;
    dim.width = sl[0].toInt(&dim.sucs_w);
    dim.height = sl[1].toInt(&dim.sucs_h);

    for(i = 0; i < 6; i++){
        sl = in.readLine().split(',');
//        st.ttl->operator [](i).offset = sl[1].toInt();
        ttl[i].offset = sl[1].toInt(&ttl[i].sucs_of);
    }

    for(i = 0; i < 6; i++){
        sl = in.readLine().split(',');
        if(sl.length()<3) goto parse_err;
        ttl[i].nm = sl[2]; //.toInt();
        if(ttl[i].nm=="") ttl[i].sucs_nm = false;
        else ttl[i].sucs_nm = true;
    }

    for(i = 0; i < 4; i++){
        dt.append({0, false, t0, 0, false, 0, false, 0, false, 0, false});
        sl = in.readLine().split(',');
        if(sl.length()<3) goto parse_err;
        dt[i].num_row = sl[2].toInt(&dt[i].sucs_nr);
        sl = in.readLine().split(',');
        if(sl.length()<3) goto parse_err;
        dt[i].duration = QTime::fromString(sl[2],"hh:mm:ss");
        if(dt[i].duration > t0 && t1 > dt[i].duration) dt[i].sucs_dur = true;
        else dt[i].sucs_dur = false;
        // else ttl[i].sucs_nm = true;
        sl = in.readLine().split(',');
        if(sl.length()<3) goto parse_err;
        dt[i].cncntr1 = sl[2].toInt(&dt[i].sucs_c1);
        sl = in.readLine().split(',');
        if(sl.length()<3) goto parse_err;
        dt[i].cncntr2 = sl[2].toInt(&dt[i].sucs_c2);
        sl = in.readLine().split(',');
        if(sl.length()<3) goto parse_err;
        dt[i].sumStream = sl[2].toInt(&dt[i].sucs_ss);
        sl = in.readLine().split(',');
        if(sl.length()<3) goto parse_err;
        dt[i].relatHumidity = sl[2].toInt(&dt[i].sucs_rH);
    }

    parse_err:
        QMessageBox msgBox(QMessageBox::Warning, "Сообщение о проблеме", "Не могу прочитать файл " + tn + "./n Заканчиваю работу.", QMessageBox::Close);
        msgBox.exec();
        return;
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

    for(i=0; i<6; i++) {
        ttl[i].sucs_of = true;
        ttl[i].sucs_nm = true;
    }

    for(i = 0; i < 2; i++){
        dt.append({0, false, t0, 0, false, 0, false, 0, false, 0, false});
        dt[i].num_row = i+1;
        dt[i].duration = QTime::fromString("0:00:30","h:mm:ss");
        dt[i].cncntr1 = 0;
        dt[i].cncntr2 = 0;
        dt[i].sumStream = 200;
        dt[i].relatHumidity = 100;

        dt[i].sucs_nr = true;
        dt[i].sucs_dur = true;
        dt[i].sucs_c1 = true;
        dt[i].sucs_c2 = true;
        dt[i].sucs_rH = true;
        dt[i].sucs_ss = true;
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

int simpleTable::color(int col, int row, QString color){
    return 0;
}

bool simpleTable::isCell(int col, int row) {
    return true;
}

void simpleTable::fromQML_smplTableEditFinished(QList<QString> ls) {
    qDebug() << "fromQML_smplTableEditFinished: " << ls[0] << " " << ls[1] << "  " << ls[2] << "  " << ls[3] << "  " << ls[4];



}
