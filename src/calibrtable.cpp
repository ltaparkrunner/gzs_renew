#include "calibrtable.h"

#include "wfiles.h"
#include <QTextStream>
#include <QDebug>

#include <QTimer>

calibrTable::calibrTable(QString clbrn, QObject *parent) :
    QObject (parent)
,   clbrf (new QFile(clbrn))
,   curtabn (0)
,   currbn (0)
,   calibTmr (new QTimer(this))
,   cfpt ({0.0})
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
    MaxFlow_1 = sl[0].toFloat();
    for(int i=0; i<10; i++){
        sl = in.readLine().split(':');
        arr1[i][1] = sl[0].toFloat();
        arr1[i][0] = arr1[i][1]*100/MaxFlow_1;
        arr1[i][3] = sl[1].toFloat();
        arr1[i][2] = arr1[i][3]*100/MaxFlow_1;
        arr1[i][5] = sl[2].toFloat();
        arr1[i][4] = arr1[i][5]*100/MaxFlow_1;
        cfpt.c_mix[0][i] = (arr1[i][3] - arr1[i][5]) / arr1[i][5] + 1.0;
        arr1[i][6] = cfpt.c_mix[0][i];
        cfpt.set_point[0][i] = arr1[i][1];
    }
    sl = in.readLine().split(':');
    MaxFlow_2 = sl[0].toFloat();
    for(int i=0; i<10; i++){
        sl = in.readLine().split(':');
        arr2[i][1] = sl[0].toFloat();
        arr2[i][0] = arr2[i][1]*100/MaxFlow_2;
        arr2[i][3] = sl[1].toFloat();
        arr2[i][2] = arr2[i][3]*100/MaxFlow_2;
        arr2[i][5] = sl[2].toFloat();
        arr2[i][4] = arr2[i][5]*100/MaxFlow_2;
        cfpt.c_mix[1][i] = (arr2[i][3] - arr2[i][5]) / arr2[i][5] + 1.0;
        arr2[i][6] = cfpt.c_mix[1][i];
        cfpt.set_point[1][i] = arr2[i][1];
    }
    sl = in.readLine().split(':');
    MaxFlow_3 = sl[0].toFloat();
    for(int i=0; i<10; i++){
        sl = in.readLine().split(':');
        arr3[i][1] = sl[0].toFloat();
        arr3[i][0] = arr3[i][1]*100/MaxFlow_3;
        arr3[i][3] = sl[1].toFloat();
        arr3[i][2] = arr3[i][3]*100/MaxFlow_3;
        arr3[i][5] = sl[2].toFloat();
        arr3[i][4] = arr3[i][5]*100/MaxFlow_3;
        cfpt.c_mix[2][i] = (arr3[i][3] - arr3[i][5]) / arr3[i][5] + 1.0;
        arr3[i][6] = cfpt.c_mix[2][i];
        cfpt.set_point[2][i] = arr3[i][1];
    }
    clbrf->close();
    // MaxFlow_1 = arr1_max;
    // MaxFlow_2 = arr2_max;
    // MaxFlow_3 = arr3_max;


//    QTimer::singleShot(8000, this, &calibrTable::publish);
}

void calibrTable::publish(){
    qDebug() << "From inside calibrTable::publish";
    QList<QString> lc;
    lc.append(QString::number(top.f));
    lc.append(top.s);
    lc.append(" ");
    lc.append(QString::number(MaxFlow_1));
    lc.append(" ");
    lc.append(" ");
    for(int i=0; i<10; i++){
        lc.append(QString::number(arr1[i][0]));
        lc.append(QString::number(arr1[i][1]));
        lc.append(QString::number(arr1[i][2]));
        lc.append(QString::number(arr1[i][3]));
        lc.append(QString::number(arr1[i][4]));
        lc.append(QString::number(arr1[i][5]));
        lc.append(QString::number(arr1[i][6]));
    }
    lc.append(QString::number(MaxFlow_2));
    lc.append(" ");
    lc.append(" ");
    for(int i=0; i<10; i++){
        lc.append(QString::number(arr2[i][0]));
        lc.append(QString::number(arr2[i][1]));
        lc.append(QString::number(arr2[i][2]));
        lc.append(QString::number(arr2[i][3]));
        lc.append(QString::number(arr2[i][4]));
        lc.append(QString::number(arr2[i][5]));
        lc.append(QString::number(arr2[i][6]));
    }
    lc.append(QString::number(MaxFlow_3));
    lc.append(" ");
    lc.append(" ");
    for(int i=0; i<10; i++){
        lc.append(QString::number(arr3[i][0]));
        lc.append(QString::number(arr3[i][1]));
        lc.append(QString::number(arr3[i][2]));
        lc.append(QString::number(arr3[i][3]));
        lc.append(QString::number(arr3[i][4]));
        lc.append(QString::number(arr3[i][5]));
        lc.append(QString::number(arr3[i][6]));
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
            lc.append(QString::number(arr1[i][0]));
            lc.append(QString::number(arr1[i][1]));
            lc.append(QString::number(arr1[i][2]));
            lc.append(QString::number(arr1[i][3]));
            lc.append(QString::number(arr1[i][4]));
            lc.append(QString::number(arr1[i][5]));
            lc.append(QString::number(arr1[i][6]));
        }
    }
    else     if(id == 2){
        for(int i=0; i<10; i++){
            lc.append(QString::number(arr2[i][0]));
            lc.append(QString::number(arr2[i][1]));
            lc.append(QString::number(arr2[i][2]));
            lc.append(QString::number(arr2[i][3]));
            lc.append(QString::number(arr2[i][4]));
            lc.append(QString::number(arr2[i][5]));
            lc.append(QString::number(arr2[i][6]));
        }
    }
    else if(id == 3){
        for(int i=0; i<10; i++){
            lc.append(QString::number(arr3[i][0]));
            lc.append(QString::number(arr3[i][1]));
            lc.append(QString::number(arr3[i][2]));
            lc.append(QString::number(arr3[i][3]));
            lc.append(QString::number(arr3[i][4]));
            lc.append(QString::number(arr3[i][5]));
            lc.append(QString::number(arr3[i][6]));
        }
    }
    emit toQML_clbrTbl2(lc, id);
}

void calibrTable::fromQML_RadioB(QString tabn, QString rbn){
    qDebug() << "fromQML_RadioB tabn: " << tabn << " rbn: " << rbn;
    int ntabn = tabn.toInt();
    int nrbn = rbn.toInt();
    if((curtabn != 0 && currbn != 0) && ( ntabn != 0 && nrbn != 0) && (curtabn != ntabn || currbn != nrbn) ){

    }
    else if((curtabn != 0 && currbn != 0) && (  ntabn != 0 && nrbn != 0 ) && (curtabn == ntabn && currbn == nrbn)){

    }
    else if((curtabn != 0 && currbn != 0) && ( ntabn == 0 || nrbn == 0 )){

    }
    else if((curtabn == 0 || currbn == 0) && ( ntabn != 0 && nrbn != 0)){
        curtabn = ntabn;
        currbn = nrbn;

        connect(calibTmr, &QTimer::timeout, this, &calibrTable::calibStage);
//        calibTmr->setInterval(300);
        calibTmr->start(300);
    }
    else if ((curtabn == 0 || currbn == 0) && ( ntabn == 0 && nrbn == 0 )){

    }
}

void calibrTable::calibStage() {
    qDebug() << "calibStage stage";
    calibTmr->stop();
}

void calibrTable::fromQML_calibTableManualEditingFinished(int tabn, int row, int column) {
    qDebug() << "fromQML_calibTableManualEditingFinished tabn: " << tabn << " row: " << row << " column: " << column;
}

calibrTable::~calibrTable(){

}
