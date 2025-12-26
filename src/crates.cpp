#include "crates.h"
#include <QDebug>

//crates_t cRates;
crates_t::crates_t(QObject *parent) :
    QObject (parent)
{
}

void crates_t::publish(){
    QList<float> lf;
//    QList<QString> lf;
    QList<int> lclr;
    lf.append(MaxFlow_1);
    lf.append(MaxFlow_2);
    lf.append(MaxFlow_3);
    lf.append(MaxBln);
    lclr.append(clr_MF_1);
    lclr.append(clr_MF_2);
    lclr.append(clr_MF_3);
    lclr.append(clr_mbln);
    emit toQML_crTbl(lf, lclr);
//    emit toQML_crTbl(lf);
}

void crates_t::fromQML_crCompleted(){
    qDebug() << "crates_t::fromQML_smplTableCompleted()";
    publish();
}
