#ifndef CALCMIXTURE_H
#define CALCMIXTURE_H

#include <QString>
#include <QTime>

struct mixStringTable{
    QString tm;
    QString cnctr;
    QString cnctrBarr;
    QString sumStream;
    QString revHumid;
    QString maxGazConsumpt;
    QString maxDryConsumpt;
    QString maxLiquidConsumpt;
    QString targGazType;
};

struct mixCoeffTable {
    QTime tm;
    float concentr;
    float concentrBarr;
    int   sumStream;
    int   relatHumid;
    int   maxGazConsumpt;
    int   maxDryConsumpt;
    int   maxHumidConsumpt;
    QString targetGazType;
};

struct   TParameters
{
    float          Conc_Gas;               // Заданная концентрация целевого газа на выходе
    float          Conc_Balloon;           // Заданная концентрация целевого газа в баллоне
    float          Factor_Dilute;          // Рассчитанный коэффициент разбавления
    float          Flow_air;               // Рассчитанный расход по каналу "сухого воздуха"
    float          Flow_gas;               // Рассчитанный расход по каналу "целевого газа"
    float          Flow_sum;               // Заданный суммарный расход газовой смеси
    float          Flow_vlag_gas;          // Рассчитанный расход по каналу "влажного воздуха"
    float          RH;                     // Заданная относительная влажность смеси
    float          Flow_max_gas;           // Заданный макс. расход по каналу "целевого газа"
    float          Flow_max_suh;           // Заданный макс. расход по каналу "сухого воздуха"
    float          Flow_max_vlag;          // Заданный макс. расход по каналу "влажного воздуха"
    float          C_gas;                  // Поправочный коэффициент для газа
    float          C_mix;                  // Поправочный коэффициент для смеси
};

class calcMixture
{
public:
//    calcMixture();
    static int stationCalc();
};

#endif // CALCMIXTURE_H
