#ifndef PARAMS_H
#define PARAMS_H

#include "combotable.h"
#include "simpletable.h"
#include "calibrtable.h"

#include <QObject>

enum gvw {
    Max_1,
    Max_2,
    Max_3,
    Targ_gas,
    Ballon
};

/*
struct   TParameters
{
    float          Conc_Gas;               // Заданная концентрация целевого газа на выходе
    float          Conc_Gas_2;             // Заданная концентрация второго целевого газа на выходе
    float          Conc_Balloon;           // Заданная концентрация целевого газа в баллоне
    float          Conc_Balloon_2;         // Заданная концентрация целевого газа 2 в баллоне 2
    float          Factor_Dilute;          // Рассчитанный коэффициент разбавления
    float          Factor_Dilute_2;        // расчитанный коэффициент разбавления 2
    float          Flow_air;               // Рассчитанный расход по каналу "сухого воздуха"
    float          Flow_gas;               // Рассчитанный расход по каналу "целевого газа"
    float          Flow_gas_2;             // Рассчитанный расход по каналу второго "целевого газа"
    float          Flow_sum;               // Заданный суммарный расход газовой смеси
    float          Flow_vlag_gas;          // Рассчитанный расход по каналу "влажного воздуха"
    float          RH;                     // Заданная относительная влажность смеси
    float          Flow_max_gas;           // Заданный макс. расход по каналу "целевого газа"
    float          Flow_max_gas_2;         // Заданный максю расход по каналу второго "целевого газа"
    float          Flow_max_suh;           // Заданный макс. расход по каналу "сухого воздуха"
    float          Flow_max_vlag;          // Заданный макс. расход по каналу "влажного воздуха"
    float          C_gas;                  // Поправочный коэффициент для газа
    float          C_gas_2;                // Поправочный коэффициент для второго целевого газа
    float          C_mix;                  // Поправочный коэффициент для смеси
    float          C_mix_2;                // поправочный коэффициент для смеси
};
*/
class Parameters : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int Factor_Dilute READ rFactor_Dilute WRITE setFactor_Dilute NOTIFY Factor_DiluteChanged)
//    float          Conc_Gas;               // Заданная концентрация целевого газа на выходе
//    float          Conc_Balloon;           // Заданная концентрация целевого газа в баллоне
public:

    explicit Parameters(QString cmb_name, QString tname,  QString clbr_name, QObject *parent);
    int rFactor_Dilute() const {return Factor_Dilute;}
    void setFactor_Dilute(const int &num){
        if(Factor_Dilute != num){
            Factor_Dilute = num;
            emit Factor_DiluteChanged();
        }
    }
    int checkTblRow(int n);
signals:
    void Factor_DiluteChanged();
public:
//    calibrTable clbrTbl;
    comboTable cmbTbl;
    simpleTable smplTbl;
    calibrTable clbrTbl;
    int         Conc_Gas;               // Заданная концентрация целевого газа на выходе
    int          Conc_Balloon;           // Заданная концентрация целевого газа в баллоне

    int       /*&*/Factor_Dilute;          // Рассчитанный коэффициент разбавления
    float       Flow_air;               // Рассчитанный расход по каналу "сухого воздуха"
    float       Flow_gas;               // Рассчитанный расход по каналу "целевого газа"

//    float          Flow_sum;               // Заданный суммарный расход газовой смеси
    int          Flow_sum;               // Заданный суммарный расход газовой смеси

    float          Flow_vlag_gas;          // Рассчитанный расход по каналу "влажного воздуха"

//    float          RH;                     // Заданная относительная влажность смеси
    int          RH;                     // Заданная относительная влажность смеси

    float          Flow_max_gas;           // Заданный макс. расход по каналу "целевого газа"
    float          Flow_max_suh;           // Заданный макс. расход по каналу "сухого воздуха"
    float          Flow_max_vlag;          // Заданный макс. расход по каналу "влажного воздуха"
    float          C_gas;                  // Поправочный коэффициент для газа
    float          C_mix;                  // Поправочный коэффициент для смеси
    float          ballon_conc;
    bool           isBallon_conc;
    QString         targetType;
    int             numTGas;
signals:
    void toQML_statusBar(QString msg);
public:
    void button_calculateClick();
    void clearColor(QString);
    bool isBallon();
    void color(gvw plc, QString color);
private:
};

#endif // PARAMS_H
