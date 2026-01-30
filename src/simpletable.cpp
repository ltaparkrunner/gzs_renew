#include "simpletable.h"
#include "wfiles.h"
#include <QTextStream>
#include <QStringList>
#include <QDebug>

#include <QMessageBox>
#include <QTimer>
//#include <QList>

// QTime t0 = QTime::fromString("00:00:05", "hh:mm:ss");
// QTime t1 = QTime::fromString("05:00:00", "hh:mm:ss");

mtime t0 = mtime(0, 0, 5);
mtime t1 = mtime(5, 0, 0);

simpleTable::simpleTable(QString tn, QObject *parent):
    QObject(parent)
,   stf (new QFile(tn))
,   rowsNum (4)
{
    int i, j;
//    stf = new QFile(tn);
    int res = wfiles::checkFile(stf);
    if (!stf->open(QIODevice::ReadOnly | QIODevice::Text)){
//        qDebug() << "simpleTable Could not open file for reading:" << stf->errorString();
        noFileInit();
        return;
    }
//    qDebug() << "simpleTable_constructor start";
    QTextStream in(stf);
    QStringList sl = in.readLine().split(',');
    QStringList sl2;
    if(sl.length() < 2) goto parse_err;
    bool ok;
    dim.width = sl[0].toInt(&ok);
    dim.clr_w = ok ? wht : rd;
    dim.height = sl[1].toInt(&ok);
    dim.clr_h = ok ? wht : rd;

//    qDebug() << "simpleTable_constructor 1";
    for(i = 0; i < 6; i++){
        sl = in.readLine().split(',');
//        st.ttl->operator [](i).offset = sl[1].toInt();
        ttl[i].offset = sl[1].toInt(&ok);
        ttl[i].clr_of = ok ? wht : rd;
    }
//    qDebug() << "simpleTable_constructor 2";
    for(i = 0; i < 6; i++){
        sl = in.readLine().split(',');
        if(sl.length()<3) goto parse_err;
        ttl[i].nm = sl[2]; //.toInt();
        if(ttl[i].nm=="") ttl[i].clr_nm = rd;
        else ttl[i].clr_nm = wht;
    }
//    qDebug() << "simpleTable_constructor 3";
    for(i = 0; i < 4; i++){     // TODO: Make for random length in file
        dt.append({0, rd, t0, rd, 0, rd, 0, rd, 0, rd, 0, rd});
        sl = in.readLine().split(',');
        if(sl.length()<3) goto parse_err;
        dt[i].num_row = sl[2].toInt(&ok);
        dt[i].clr_nr = ok ? wht : rd;
        sl = in.readLine().split(',');
        if(sl.length()<3) goto parse_err;
//        dt[i].duration = QTime::fromString(sl[2],"hh:mm:ss");
        sl2 = sl[2].split(':');
        if(sl2.length()<3) goto parse_err;
        dt[i].duration = mtime(sl2[0], sl2[1], sl2[2]);
        if(dt[i].duration > t0 && t1 > dt[i].duration) dt[i].clr_dur = wht;
        else dt[i].clr_dur = rd;
        // else ttl[i].clr_nm = true;
        sl = in.readLine().split(',');
        if(sl.length()<3) goto parse_err;
        dt[i].cncntr1 = sl[2].toInt(&ok);
        dt[i].clr_c1 = ok ? wht : rd;
        sl = in.readLine().split(',');
        if(sl.length()<3) goto parse_err;
        dt[i].cncntr2 = sl[2].toInt(&ok);
        dt[i].clr_c2 = ok ? wht : rd;
        sl = in.readLine().split(',');
        if(sl.length()<3) goto parse_err;
        dt[i].sumStream = sl[2].toInt(&ok);
        dt[i].clr_sS = ok ? wht : rd;
        sl = in.readLine().split(',');
        if(sl.length()<3) goto parse_err;
        dt[i].relatHumidity = sl[2].toInt(&ok);
        dt[i].clr_rH = ok ? wht : rd;
    }
    dt_len = dt.length();
    return;
    parse_err:
        QMessageBox msgBox(QMessageBox::Warning, "Сообщение о проблеме", "Не могу прочитать файл " + tn + "./n Заканчиваю работу.", QMessageBox::Close);
        msgBox.exec();
        return;
}

int simpleTable::noFileInit(){
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
            ttl[i].clr_of = wht;
            ttl[i].clr_nm = wht;
        }

        for(i = 0; i < 2; i++){
    //        dt.append({0, false, t0, 0, false, 0, false, 0, false, 0, false});
            dt.append({0, rd, t0, rd, 0, rd, 0, rd, 0, rd, 0, rd});
            dt[i].num_row = i+1;
    //        dt[i].duration = QTime::fromString("0:00:30","h:mm:ss");
            dt[i].duration = mtime(0, 0, 30);
            dt[i].cncntr1 = 0;
            dt[i].cncntr2 = 0;
            dt[i].sumStream = 200;
            dt[i].relatHumidity = 100;

            dt[i].clr_nr = wht;//wht;
            dt[i].clr_dur = wht;//wht;
            dt[i].clr_c1 = wht; //wht
            dt[i].clr_c2 = wht;
            dt[i].clr_sS = wht;
            dt[i].clr_rH = wht;
        }
    }
    return 0;
}
/*
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
        ttl[i].clr_of = wht;
        ttl[i].clr_nm = wht;
    }

    for(i = 0; i < 2; i++){
//        dt.append({0, false, t0, 0, false, 0, false, 0, false, 0, false});
        dt.append({0, rd, t0, rd, 0, rd, 0, rd, 0, rd, 0, rd});
        dt[i].num_row = i+1;
//        dt[i].duration = QTime::fromString("0:00:30","h:mm:ss");
        dt[i].duration = mtime(0, 0, 30);
        dt[i].cncntr1 = 0;
        dt[i].cncntr2 = 0;
        dt[i].sumStream = 200;
        dt[i].relatHumidity = 100;

        dt[i].clr_nr = wht;//wht;
        dt[i].clr_dur = wht;//wht;
        dt[i].clr_c1 = wht; //wht
        dt[i].clr_c2 = wht;
        dt[i].clr_sS = wht;
        dt[i].clr_rH = wht;
    }
}
*/
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
    int rowsNum = dt.length();
    for(i = 0; i < rowsNum; i++){
        lc.append(QString::number(dt[i].num_row));
//        lc.append(dt[i].duration.toString("hh:mm:ss"));
        lc.append(dt[i].duration.to_string());
        lc.append(QString::number(dt[i].cncntr1));
        lc.append(QString::number(dt[i].cncntr2));
        lc.append(QString::number(dt[i].sumStream));
        lc.append(QString::number(dt[i].relatHumidity));
    }
    qDebug() << "simpleTable::publish rows_num = " << rowsNum;
//    qDebug() << "before toQML_smplTbl(lc)";
    emit toQML_smplTbl(lc);
}

void simpleTable::publish2(){
//    qDebug() << "simpleTable::publish() the beginning";
    QList<int> ln;
    QList<QString> ls;
    int i;
    for(i = 0; i < 6; i++){
        ln.append(ttl[i].offset);
    }
    for(i = 0; i < 6; i++){
        ls.append(ttl[i].nm);
    }
    int rowsNum = dt.length();
    for(i = 0; i < rowsNum; i++){
        ln.append(dt[i].num_row);
        ln.append(dt[i].clr_nr);
//        lc.append(dt[i].duration.toString("hh:mm:ss"));
        ln.append(dt[i].clr_dur);
        ln.append(dt[i].cncntr1);
        ln.append(dt[i].clr_c1);
        ln.append(dt[i].cncntr2);
        ln.append(dt[i].clr_c2);
        ln.append(dt[i].sumStream);
        ln.append(dt[i].clr_sS);
        ln.append(dt[i].relatHumidity);
        ln.append(dt[i].clr_rH);

//        ls.append(dt[i].duration.toString("hh:mm:ss"));
        ls.append(dt[i].duration.to_string());
    }
    emit toQML_smplTbl2(ln, ls);
}

void simpleTable::fromQML_smplTableCompleted(){
    publish2();
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

void simpleTable::fromQML_smplTableEditFinished(QList<QString> ls, int row, int clmn) {
    qDebug() << "fromQML_smplTableEditFinished: " << ls[0] << " " << ls[1] << "  " << ls[2] << "  " << ls[3] << "  " << ls[4] << " " << row << " " << clmn << "\n";
    bool ok;
    float tmp;
    if(clmn == 2) {
        tmp = ls[1].toFloat(&ok);
        if(ok){
            dt[row].cncntr1 = tmp;
            dt[row].cncntr2 = dt[row].cncntr1 * 10000;
        }
    }
    else if(clmn == 3) {
        tmp = ls[2].toFloat(&ok);
        if(ok) {
            dt[row].cncntr2 = tmp;
            dt[row].cncntr1 = dt[row].cncntr2 / 10000;
        }
    }
    else if(clmn == 1) {
        QStringList sl = ls[0].split(':');
        if(sl.length()>=3){
            mtime tm = mtime(sl[0], sl[1], sl[2]);
            if(tm.isValid()) {
                dt[row].duration = tm;
            }
        }
    }
    //TODO: Output of recounted concentrations
//    if(row)
}

void simpleTable::publish3(int row, int clmn){
    if(clmn == 2) {
        toQML_smplTbl3(dt[row].cncntr2, row, 3);
        toQML_smplTbl3(dt[row].cncntr1, row, 2);
    }
    else if(clmn == 3) {
        toQML_smplTbl3(dt[row].cncntr1, row, 2);
        toQML_smplTbl3(dt[row].cncntr2, row, 3);
    }
    else if(clmn == 1) {
        toQML_smplTbl4(dt[row].duration.to_string(), row, 1);
    }
}

void simpleTable::fromQML_smplTableRowAdded(QList<QString> ls, int row, int clmn){
    qDebug() << "fromQML_smplTableEditFinished: " << ls[0] << " " << ls[1] << "  " << ls[2] << "  " << ls[3] << "  " << ls[4] << " " << row << " " << clmn << "\n";
    mtime tt = mtime(0,0,0);
    dt_t temp = {row, rd, tt, rd, 0, rd, 0, rd, 0, rd, 0, rd};
    temp.num_row = row;
    temp.duration = tt;
    temp.cncntr1 = ls[1].toInt();
    temp.cncntr2 = ls[2].toInt();
    temp.sumStream = ls[3].toInt();
    temp.relatHumidity = ls[4].toInt();
    temp.clr_c1 = rd;
    temp.clr_c2 = rd;
    temp.clr_dur = rd;
    temp.clr_nr = rd;
    temp.clr_rH = rd;
    temp.clr_sS = rd;
    dt.append({row, rd, tt, rd, 0, rd, 0, rd, 0, rd, 0, rd});
}
