#ifndef RATES_H
#define RATES_H

#include <QObject>
#include "auxil.h"

// Класс для максимальных значений.
// MaxFlow_1 -- максимальный расход газа
// MaxFlow_2 -- максимальный расход сушняка
// MaxFlow_3 -- максимальный расход влаги
// MaxBln    -- максимальная концентрация в баллоне  do not use
// cbIndx    -- индекс целевого газа? TODO: первая цифра в в файле Calibr.str(15) aren't publish // Form1->AdvComboBox1->ItemIndex Kalib.cpp 194 line

struct Restrict{
    const int INDX_MAX;
    const int BLLN_MAX;
    const int TARG_MAX;
    const int DRY_AIR_MAX;
    const int WET_AIR_MAX;
};

struct crates_t: public QObject
{
    Q_OBJECT
public:
    Restrict restr ={.INDX_MAX=100, .BLLN_MAX=100, .TARG_MAX=100, .DRY_AIR_MAX=1000, .WET_AIR_MAX=1000};
    crates_t(QObject *parent = nullptr);
    float MaxFlow_1;
    float MaxFlow_2;
    float MaxFlow_3;
    clr clr_MF_1;
    clr clr_MF_2;
    clr clr_MF_3;

    float MaxBln;   // Simple ballon
    clr clr_mbln;

    float ballon_cncntr;
    clr clr_bc;
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
