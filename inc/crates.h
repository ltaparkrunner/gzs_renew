#ifndef RATES_H
#define RATES_H

#include <QObject>
#include "auxil.h"

struct crates_t: public QObject
{
    Q_OBJECT
public:
    crates_t(QObject *parent = nullptr);
    float MaxFlow_1;
    float MaxFlow_2;
    float MaxFlow_3;
    clr clr_MF_1;
    clr clr_MF_2;
    clr clr_MF_3;

    float MaxBln;
    clr clr_mbln;

    int cbIndx;
    clr clr_cbi;

    void publish();
public slots:
    void fromQML_crCompleted();
signals:
    void toQML_crTbl(QList<float> lf, QList<int> lc);
//    void toQML_crTbl(QList<float> lf);
//    void toQML_crTbl(QList<int> lf);
//    void toQML_crTbl(QList<QString> lf);
};

#endif // RATES_H
