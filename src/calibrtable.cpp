#include "calibrtable.h"

#include "wfiles.h"
#include <QTextStream>
#include <QDebug>

#include <QTimer>

calibrTable::calibrTable(QString clbrn, QObject *parent) :
    QObject (parent)
,   clbrf (new QFile(clbrn))
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
    arr1_max = sl[0].toFloat();
    for(int i=0; i<10; i++){
        sl = in.readLine().split(':');
        arr1[i][0] = sl[0].toFloat();
        arr1[i][1] = sl[1].toFloat();
        arr1[i][2] = sl[2].toFloat();
    }
    sl = in.readLine().split(':');
    arr2_max = sl[0].toFloat();
    for(int i=0; i<10; i++){
        sl = in.readLine().split(':');
        arr2[i][0] = sl[0].toFloat();
        arr2[i][1] = sl[1].toFloat();
        arr2[i][2] = sl[2].toFloat();
    }
    sl = in.readLine().split(':');
    arr3_max = sl[0].toFloat();
    for(int i=0; i<10; i++){
        sl = in.readLine().split(':');
        arr3[i][0] = sl[0].toFloat();
        arr3[i][1] = sl[1].toFloat();
        arr3[i][2] = sl[2].toFloat();
    }
    clbrf->close();
    MaxFlow_1 = arr1_max;
    MaxFlow_2 = arr2_max;
    MaxFlow_3 = arr3_max;
//    QTimer::singleShot(8000, this, &calibrTable::publish);
}

void calibrTable::publish(){
    qDebug() << "From inside calibrTable::publish";
    QList<QString> lc;
    lc.append(QString::number(top.f));
    lc.append(top.s);
    lc.append(" ");
    lc.append(QString::number(arr1_max));
    lc.append(" ");
    lc.append(" ");
    for(int i=0; i<10; i++){
        lc.append(QString::number(arr1[i][0]));
        lc.append(QString::number(arr1[i][1]));
        lc.append(QString::number(arr1[i][2]));
    }
    lc.append(QString::number(arr2_max));
    lc.append(" ");
    lc.append(" ");
    for(int i=0; i<10; i++){
        lc.append(QString::number(arr2[i][0]));
        lc.append(QString::number(arr2[i][1]));
        lc.append(QString::number(arr2[i][2]));
    }
    lc.append(QString::number(arr3_max));
    lc.append(" ");
    lc.append(" ");
    for(int i=0; i<10; i++){
        lc.append(QString::number(arr3[i][0]));
        lc.append(QString::number(arr3[i][1]));
        lc.append(QString::number(arr3[i][2]));
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
        }
    }
    else     if(id == 2){
        for(int i=0; i<10; i++){
            lc.append(QString::number(arr2[i][0]));
            lc.append(QString::number(arr2[i][1]));
            lc.append(QString::number(arr2[i][2]));
        }
    }
    else if(id == 3){
        for(int i=0; i<10; i++){
            lc.append(QString::number(arr3[i][0]));
            lc.append(QString::number(arr3[i][1]));
            lc.append(QString::number(arr3[i][2]));
        }
    }
     emit toQML_clbrTbl2(lc, id);
}
