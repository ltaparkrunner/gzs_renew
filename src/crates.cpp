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
//    lf.append(MaxBln);
    lf.append(ballon_cncntr);
    lclr.append(clr_MF_1);
    lclr.append(clr_MF_2);
    lclr.append(clr_MF_3);
//    lclr.append(clr_mbln);
    lclr.append(clr_bc);
    emit toQML_crTbl(lf, lclr);
//    emit toQML_crTbl(lf);
}

void crates_t::fromQML_crCompleted(){
    qDebug() << "crates_t::fromQML_smplTableCompleted()";
    publish();
}

//Restrict restr ={.INDX_MAX=100, .BLLN_MAX=100, .TARG_MAX=100, .DRY_AIR_MAX=100, .WET_AIR_MAX=100};
