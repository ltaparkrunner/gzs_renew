#include "calibrtable.h"

#include "wfiles.h"
#include <QTextStream>
#include <QDebug>

#include <QTimer>
#include <QMessageBox>
#include "clibinc.h"

calibrTable::calibrTable(QString clbrn, QObject *parent) :
    QObject (parent)
,   clbrf (new QFile(clbrn))
,   curtabn (0)
,   currbn (0)
,   curvalue (0.0)
,   calibTmr (new QTimer(this))
,   cfpt ({0.0})
,   isaxis(true)
{
//    qDebug() << "calibrTable constractor. Name: " << clbrn;
//    clbrf = new QFile(clbrn);
    int res = wfiles::checkFile(clbrf);
    if (!clbrf->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "calibrTable could not open file for reading:" << clbrf->errorString();
        return;
    }

    QTextStream in(clbrf);
//    clbrt = new calibrtable;
    QStringList sl = in.readLine().split(':');

    top.f = sl[0].toInt();
    top.s = sl[1];
    sl = in.readLine().split(':');
    bool ok;
    cr.MaxFlow_1 = sl[0].toFloat(&ok);
    cr.clrMF_1 = ok ? wht : rd;
    if((cr.clrMF_1 == wht) && (cr.MaxFlow_1 < 100.0) && (cr.MaxFlow_1 > 0)) cr.clrMF_1 = wht;
    else cr.clrMF_1 = rd;
    for(int i=0; i<10; i++){
        sl = in.readLine().split(':');
        // arr1[i][1] = sl[0].toFloat();
        // arr1[i][0] = arr1[i][1]*100/mf.MaxFlow_1;
        // arr1[i][3] = sl[1].toFloat();
        // arr1[i][2] = arr1[i][3]*100/mf.MaxFlow_1;
        // arr1[i][5] = sl[2].toFloat();
        // arr1[i][4] = arr1[i][5]*100/mf.MaxFlow_1;
        // cfpt.c_mix[0][i] = (arr1[i][3] - arr1[i][5]) / arr1[i][5] + 1.0;
        // arr1[i][6] = cfpt.c_mix[0][i];
        // cfpt.set_point[0][i] = arr1[i][1];

        tbl1[i].ml1 = sl[0].toFloat(&ok);
        if(!ok)tbl1[i].ml1 = 0.0;
        tbl1[i].pc1 = ok ? tbl1[i].ml1*100.0/cr.MaxFlow_1 : 0.0;
        tbl1[i].ml2 = sl[1].toFloat(&ok);
        if(!ok)tbl1[i].ml2 = 0.0;
        tbl1[i].pc2 = ok ? tbl1[i].ml2*100.0/cr.MaxFlow_1 : 0.0;
        tbl1[i].ml3 = sl[2].toFloat(&ok);
        if(!ok)tbl1[i].ml3 = 0.0;
        tbl1[i].pc3 = ok ? tbl1[i].ml3*100.0/cr.MaxFlow_1 : 0.0;
        cfpt.c_mix[0][i] = (tbl1[i].ml2 - tbl1[i].ml3)/tbl1[i].ml3 + 1.0;
        tbl1[i].coeff = cfpt.c_mix[0][i];
        cfpt.set_point[0][i] = tbl1[i].ml1;
    }
    sl = in.readLine().split(':');
    cr.MaxFlow_2 = sl[0].toFloat(&ok);
    cr.clrMF_1 = ok ? wht : rd;
    for(int i=0; i<10; i++){
        sl = in.readLine().split(':');
        tbl2[i].ml1 = sl[0].toFloat(&ok);
        if(!ok)tbl2[i].ml1 = 0.0;
        tbl2[i].pc1 = ok ? tbl2[i].ml1*100.0/cr.MaxFlow_2 : 0.0;
        tbl2[i].ml2 = sl[1].toFloat(&ok);
        if(!ok)tbl2[i].ml2 = 0.0;
        tbl2[i].pc2 = ok ? tbl2[i].ml2*100.0/cr.MaxFlow_2 : 0.0;
        tbl2[i].ml3 = sl[2].toFloat(&ok);
        if(!ok)tbl2[i].ml3 = 0.0;
        tbl2[i].pc3 = ok ? tbl2[i].ml3*100.0/cr.MaxFlow_2 : 0.0;
        cfpt.c_mix[1][i] = (tbl2[i].ml2 - tbl2[i].ml3)/tbl2[i].ml3 + 1.0;
        tbl2[i].coeff = cfpt.c_mix[1][i];
        cfpt.set_point[1][i] = tbl2[i].ml1;
    }
    sl = in.readLine().split(':');
    cr.MaxFlow_3 = sl[0].toFloat(&ok);
    cr.clrMF_3 = ok ? wht : rd;
    for(int i=0; i<10; i++){
        sl = in.readLine().split(':');
        tbl3[i].ml1 = sl[0].toFloat(&ok);
        if(!ok)tbl3[i].ml1 = 0.0;
        tbl3[i].pc1 = ok ? tbl3[i].ml1*100.0/cr.MaxFlow_3 : 0.0;
        tbl3[i].ml2 = sl[1].toFloat(&ok);
        if(!ok)tbl3[i].ml2 = 0.0;
        tbl3[i].pc2 = ok ? tbl3[i].ml2*100.0/cr.MaxFlow_3 : 0.0;
        tbl3[i].ml3 = sl[2].toFloat(&ok);
        if(!ok)tbl3[i].ml3 = 0.0;
        tbl3[i].pc3 = ok ? tbl3[i].ml3*100.0/cr.MaxFlow_3 : 0.0;
        cfpt.c_mix[2][i] = (tbl3[i].ml2 - tbl3[i].ml3)/tbl3[i].ml3 + 1.0;
        tbl3[i].coeff = cfpt.c_mix[2][i];
        cfpt.set_point[2][i] = tbl3[i].ml1;
    }
    clbrf->close();
    // mf.MaxFlow_1 = arr1_max;
    // mf.MaxFlow_2 = arr2_max;
    // mf.MaxFlow_3 = arr3_max;


//    QTimer::singleShot(8000, this, &calibrTable::publish);
}

void calibrTable::publish(){
    qDebug() << "From inside calibrTable::publish";
    QList<QString> lc;
    // lc.append(QString::number(top.f));
    // lc.append(top.s);
    // lc.append(" ");
    // lc.append(QString::number(mf.MaxFlow_1));
    // lc.append(" ");
    // lc.append(" ");
    for(int i=0; i<10; i++){
        lc.append(QString::number(tbl1[i].pc1));
        lc.append(QString::number(tbl1[i].ml1));
        lc.append(QString::number(tbl1[i].pc2));
        lc.append(QString::number(tbl1[i].ml2));
        lc.append(QString::number(tbl1[i].pc3));
        lc.append(QString::number(tbl1[i].ml3));
        lc.append(QString::number(tbl1[i].coeff));
    }
    // lc.append(QString::number(mf.MaxFlow_2));
    // lc.append(" ");
    // lc.append(" ");
    for(int i=0; i<10; i++){
        lc.append(QString::number(tbl2[i].pc1));
        lc.append(QString::number(tbl2[i].ml1));
        lc.append(QString::number(tbl2[i].pc2));
        lc.append(QString::number(tbl2[i].ml2));
        lc.append(QString::number(tbl2[i].pc3));
        lc.append(QString::number(tbl2[i].ml3));
        lc.append(QString::number(tbl2[i].coeff));
    }
    // lc.append(QString::number(mf.MaxFlow_3));
    // lc.append(" ");
    // lc.append(" ");
    for(int i=0; i<10; i++){
        lc.append(QString::number(tbl3[i].pc1));
        lc.append(QString::number(tbl3[i].ml1));
        lc.append(QString::number(tbl3[i].pc2));
        lc.append(QString::number(tbl3[i].ml2));
        lc.append(QString::number(tbl3[i].pc3));
        lc.append(QString::number(tbl3[i].ml3));
        lc.append(QString::number(tbl3[i].coeff));
    }
    emit toQML_clbrTbl(lc);
}

void calibrTable::fromQML_calibTableCompleted(QString id) {
    publish();
}

void calibrTable::fromQML_calibTableCompleted(int id) {
    QList<QString> lc;
    if(id == 1){
        for(int i=0; i<10; i++){
            lc.append(QString::number(tbl1[i].pc1));
            lc.append(QString::number(tbl1[i].ml1));
            lc.append(QString::number(tbl1[i].pc2));
            lc.append(QString::number(tbl1[i].ml2));
            lc.append(QString::number(tbl1[i].pc3));
            lc.append(QString::number(tbl1[i].ml3));
            lc.append(QString::number(tbl1[i].coeff));
        }
    }
    else     if(id == 2){
        for(int i=0; i<10; i++){
            lc.append(QString::number(tbl2[i].pc1));
            lc.append(QString::number(tbl2[i].ml1));
            lc.append(QString::number(tbl2[i].pc2));
            lc.append(QString::number(tbl2[i].ml2));
            lc.append(QString::number(tbl2[i].pc3));
            lc.append(QString::number(tbl2[i].ml3));
            lc.append(QString::number(tbl2[i].coeff));
        }
    }
    else if(id == 3){
        for(int i=0; i<10; i++){
            lc.append(QString::number(tbl3[i].pc1));
            lc.append(QString::number(tbl3[i].ml1));
            lc.append(QString::number(tbl3[i].pc2));
            lc.append(QString::number(tbl3[i].ml2));
            lc.append(QString::number(tbl3[i].pc3));
            lc.append(QString::number(tbl3[i].ml3));
            lc.append(QString::number(tbl3[i].coeff));
        }
    }
    emit toQML_clbrTbl2(lc, id);
}

//void calibrTable::fromQML_RadioB(QString tabn, QString rbn){
void calibrTable::fromQML_RadioB(QString tabn, QString rbn, QString value) {
    qDebug() << "fromQML_RadioB tabn: " << tabn << " rbn: " << rbn;
    int ntabn = tabn.toInt();
    int nrbn = rbn.toInt();
    curvalue = value.toFloat();
    if((curtabn != 0 && currbn != 0) && ( ntabn != 0 && nrbn != 0) && (curtabn != ntabn || currbn != nrbn) ){
        // QList<QString> lc;
        // lc.append(QDateTime::currentDateTime().toString());
        // lc.append(QDateTime::currentDateTime().toString());
        // emit toQml_clbrAxis(lc);
        calibTmr->stop();
        curtabn = ntabn;
        currbn = nrbn;
        connect(calibTmr, &QTimer::timeout, this, &calibrTable::calibStage);
        isaxis = true;
        calibStage();
        calibTmr->start(1000); //какой период таймера?
    }
    else if((curtabn != 0 && currbn != 0) && (  ntabn != 0 && nrbn != 0 ) && (curtabn == ntabn && currbn == nrbn)){
    }
    else if((curtabn != 0 && currbn != 0) && ( ntabn == 0 || nrbn == 0 )){
        calibTmr->stop();
    }
    else if((curtabn == 0 || currbn == 0) && ( ntabn != 0 && nrbn != 0)){
        // QList<QString> lc;
        // // lc.append(QDateTime::currentDateTime().addSecs(-1).toString());
        // lc.append(QDateTime::currentDateTime().toString());
        // lc.append(QDateTime::currentDateTime().toString());
        // emit toQml_clbrAxis(lc);
        // qDebug("fromQML_RadioB      toQml_clbrAxis");
        curtabn = ntabn;
        currbn = nrbn;

        connect(calibTmr, &QTimer::timeout, this, &calibrTable::calibStage);
//        calibTmr->setInterval(300);
        isaxis = true;
        calibStage();
        calibTmr->start(1000); //какой период таймера?
    }
    else if ((curtabn == 0 || currbn == 0) && ( ntabn == 0 && nrbn == 0 )){

    }
}

void calibrTable::calibStage() {
    int err;
    static int count = 4;
    switch(curtabn){
    case 1: qDebug() << "calibStage stage, curvalue: " << tbl1[currbn-1].ml1; break;
    case 2: qDebug() << "calibStage stage, curvalue: " << tbl2[currbn-1].ml1; break;
    case 3: qDebug() << "calibStage stage, curvalue: " << tbl3[currbn-1].ml1; break;
    }
    float anOut0=0, anOut1=0, anOut2=0;
    float anIn0, anIn1, anIn2;
    QList<QString> lc;
    switch (curtabn){
    case 1:
        anOut0 = curvalue * 5.000 / cr.MaxFlow_1;
        ar._87063_TX[5] = 0x2;
        break;
    case 2:
        anOut1 = curvalue * 5.000 / cr.MaxFlow_2;
        ar._87063_TX[5] = 0x4;
        break;
    case 3:
        anOut2 = curvalue * 5.000 / cr.MaxFlow_3;
        ar._87063_TX[5] = 0x4;
        break;
    }

    {
        ar._87024_TX[5] = 0;
        ar._87024_RX[0] = anOut0;
        err = AnalogOut_87K(ar._87024_TX, ar._87024_RX, ar.szSend, ar.szReceive);
        if (err != 0){
           QMessageBox msgBox(QMessageBox::Critical, "Сообщение о проблеме", "Ошибка модуля i-87024", QMessageBox::Close);
           msgBox.exec();
           return;
        }
        ar._87024_TX[5] = 1;
        ar._87024_RX[0] = anOut1;
        err = AnalogOut_87K(ar._87024_TX, ar._87024_RX, ar.szSend, ar.szReceive);
        if (err != 0){
           QMessageBox msgBox(QMessageBox::Critical, "Сообщение о проблеме", "Ошибка модуля i-87024", QMessageBox::Close);
           msgBox.exec();
           return;
        }
        ar._87024_TX[5] = 2;
        ar._87024_RX[0] = anOut2;
        err = AnalogOut_87K(ar._87024_TX, ar._87024_RX, ar.szSend, ar.szReceive);
        if (err != 0){
           QMessageBox msgBox(QMessageBox::Critical, "Сообщение о проблеме", "Ошибка модуля i-87024", QMessageBox::Close);
           msgBox.exec();
           return;
        }
        err = DigitalOut_87K(ar._87063_TX, ar._87063_RX, ar.szSend, ar.szReceive);
        if (err != 0){
           QMessageBox msgBox(QMessageBox::Critical, "Сообщение о проблеме", "Ошибка модуля i-87063", QMessageBox::Close);
           msgBox.exec();
           return;
        }
        err = AnalogInAll_87K(ar._87017_TX, ar._87017_RX, ar.szSend, ar.szReceive);
        if (err != 0){
           QMessageBox msgBox(QMessageBox::Critical, "Сообщение о проблеме", "Ошибка модуля i-87017", QMessageBox::Close);
           msgBox.exec();
           return;
        }
        lc.append(QDateTime::currentDateTime().toString());
//        lc.append(QString::number(count++));
        switch (curtabn){
        case 1:
            anIn0 = ar._87017_RX[0];
            tbl1[currbn-1].ml2 = anIn0 * cr.MaxFlow_1/5.0;
//            toQML_clbrTbl3(anIn0 * mf.MaxFlow_1/5.0, currbn);
            for(int i=0; i<10; i++){
                tbl1[i].pc1 = tbl1[i].ml1*100.0/cr.MaxFlow_1;
                tbl1[i].pc2 = tbl1[i].ml2*100.0/cr.MaxFlow_1;
                tbl1[i].pc3 = tbl1[i].ml3*100.0/cr.MaxFlow_1;
                cfpt.c_mix_temp[0][i] = (tbl1[i].ml2 - tbl1[i].ml3)/tbl1[i].ml3 + 1.0;
                tbl1[i].coeff = cfpt.c_mix_temp[0][i];
                cfpt.set_point_temp[0][i] = tbl1[i].ml1;
            }
            lc.append(QString::number(anOut0));
            lc.append(QString::number(anIn0));
            break;
        case 2:
            anIn1 = ar._87017_RX[0];
            tbl2[currbn-1].ml2 = anIn1 * cr.MaxFlow_2/5.0;
//            toQML_clbrTbl3(anIn1 * cr.MaxFlow_2/5.0, currbn);
            for(int i=0; i<10; i++){
                tbl2[i].pc1 = tbl2[i].ml1*100.0/cr.MaxFlow_2;
                tbl2[i].pc2 = tbl2[i].ml2*100.0/cr.MaxFlow_2;
                tbl2[i].pc3 = tbl2[i].ml3*100.0/cr.MaxFlow_2;
                cfpt.c_mix_temp[1][i] = (tbl2[i].ml2 - tbl2[i].ml3)/tbl2[i].ml3 + 1.0;
                tbl2[i].coeff = cfpt.c_mix_temp[1][i];
                cfpt.set_point_temp[1][i] = tbl2[i].ml1;
            }
            fromQML_calibTableCompleted(curtabn);           //????
            lc.append(QString::number(anOut0));
            lc.append(QString::number(anIn0));
            break;
        case 3:
            anIn2 = ar._87017_RX[0];
            tbl3[currbn-1].ml2 = anIn2 * cr.MaxFlow_3/5.0;
//            toQML_clbrTbl3(anIn2 * cr.MaxFlow_3/5.0, currbn);
            for(int i=0; i<10; i++){
                tbl3[i].pc1 = tbl3[i].ml1*100.0/cr.MaxFlow_3;
                tbl3[i].pc2 = tbl3[i].ml2*100.0/cr.MaxFlow_3;
                tbl3[i].pc3 = tbl3[i].ml3*100.0/cr.MaxFlow_3;
                cfpt.c_mix_temp[2][i] = (tbl3[i].ml2 - tbl3[i].ml3)/tbl3[i].ml3 + 1.0;
                tbl3[i].coeff = cfpt.c_mix_temp[2][i];
                cfpt.set_point_temp[2][i] = tbl3[i].ml1;
            }
            lc.append(QString::number(anOut0));
            lc.append(QString::number(anIn0));
            break;
        }
    }
    fromQML_calibTableCompleted(curtabn);
    if(isaxis) {
        QList<QString> lc;
        lc.append(QDateTime::currentDateTime().toString());
        lc.append(QDateTime::currentDateTime().toString());
        emit toQml_clbrAxis(lc);
        isaxis = false;
    }
    toQml_clbrPlot(lc);
}

void calibrTable::fromQML_calibTableManualEditingFinished(int tabn, int row, int column, QString mean) {
    qDebug() << "fromQML_calibTableManualEditingFinished tabn: " << tabn << " row: " << row << " column: " << column << mean;
//    curtabn = tabn;
    bool ok;
    float fmean = mean.toFloat(&ok);
    if(ok) {
        switch (tabn){
            case 1:
                tbl1[row-1].ml3 = fmean;
                tbl1[row-1].pc3 = tbl1[row-1].ml3*100.0/cr.MaxFlow_1;
            break;
            case 2:
                tbl2[row-1].ml3 = fmean;
                tbl2[row-1].pc3 = tbl2[row-1].ml3*100.0/cr.MaxFlow_2;
            break;
            case 3:
                tbl3[row-1].ml3 = fmean;
                tbl3[row-1].pc3 = tbl3[row-1].ml3*100.0/cr.MaxFlow_3;
            break;
        }
        fromQML_calibTableCompleted(tabn);
    }
    else {
        QMessageBox msgBox(QMessageBox::Critical, "Сообщение о проблеме", "Ошибка конвертации в число с плавающей точкой", QMessageBox::Close);
        msgBox.exec();
    }
}

calibrTable::~calibrTable(){
    calibTmr->stop();
    delete calibTmr;
}

void calibrTable::fromQML_calibClosed(){
    calibTmr->stop();
}
