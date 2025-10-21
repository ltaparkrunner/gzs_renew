#include "params.h"
#include <QDebug>

//params::params(simpleTable* s_t, calibrTable* c_t):
//    ps.Factor_Dilute(s_t ->st.dt[2].relatHumidity)
//{
//    ps.Conc_Gas = &(s_t->st.dt[1].cncntr1);
//    ps.Conc_Balloon = c_t->clbrt->top.s.toFloat();
//    ps.Flow_sum = s_t->st.dt[1].sumStream;
//    ps.RH = s_t->st.dt[1].relatHumidity;
////    ps.Factor_Dilute = s_t ->st.dt[2].relatHumidity;
//}

//bool params::isInit(){
//    return true;
//}

Parameters::Parameters(QString cmb_name, QString tname,  QString clbr_name, QObject *parent):
    QObject(parent)
,   cmbTbl(cmb_name, this)
//,   smplTbl(tname, this)
,   smplTbl(this)
,   clbrTbl(clbr_name, this)
{
}

int Parameters::checkTblRow(int n){
    if(!(smplTbl.dt[n].duration.isValid())) {
        toQML_statusBar("Ошибка ввода данных | Длительность");
        return 1;
    }

    if(!(smplTbl.dt[n].cncntr1 > 0 && smplTbl.dt[n].cncntr1 < 100)) {
        toQML_statusBar("Ошибка ввода данных | Концентрация");
        return 1;
    }
    else Conc_Gas = smplTbl.dt[n].cncntr1;

    if(!(smplTbl.dt[n].cncntr2 > 0 && smplTbl.dt[n].cncntr2 < 100)) {
        toQML_statusBar("Ошибка ввода данных | Концентрация в баллоне");
        return 1;
    }
    else Conc_Balloon = smplTbl.dt[n].cncntr2;

    if(!(smplTbl.dt[n].relatHumidity > 0 && smplTbl.dt[n].relatHumidity < 100)){
        toQML_statusBar("Ошибка ввода данных | Относительная влажность");
        return 1;
    }
    else RH = smplTbl.dt[n].relatHumidity;

    if(!(clbrTbl.MaxFlow_1 > 0 && clbrTbl.MaxFlow_1 < 100)) {
        toQML_statusBar("Ошибка ввода данных | \"ЦЕЛЕВОЙ ГАЗ\"");
        return 2;
    }
    else  Flow_max_gas = clbrTbl.MaxFlow_1;

    if(!(clbrTbl.MaxFlow_2 > 0 && clbrTbl.MaxFlow_2 < 100)) {
        toQML_statusBar("Ошибка ввода данных | \"СУХОЙ ВОЗДУХ\"");
        return 2;
    }
    else  Flow_max_suh = clbrTbl.MaxFlow_2;

    if(!(clbrTbl.MaxFlow_3 > 0 && clbrTbl.MaxFlow_3 < 100)) {
        toQML_statusBar("Ошибка ввода данных | \"ВЛАЖНЫЙ ВОЗДУХ\"");
        return 2;
    }
    else  Flow_max_vlag = clbrTbl.MaxFlow_3;

    if(cmbTbl.tblrows[n].gname.isEmpty()){
        toQML_statusBar("Ошибка ввода данных | Тип целевого газа");
        return 2;
    }
    else if(!(cmbTbl.tblrows[n].persentage > 0 && cmbTbl.tblrows[n].persentage < 100)){
        C_gas = 1.00;
        toQML_statusBar("ВНИМАНИЕ | Поправочный коэффициент = 1.00");
    }
    else C_gas = cmbTbl.tblrows[n].persentage;

    // РАСЧЕТ ПАРАМЕТРОВ //

    if (Conc_Gas > Conc_Balloon)
    {
    //        for (int col=1; col<Form1->AdvStringGrid1->ColCount; col++)    // Красная строка
    //            AdvStringGrid1->Colors[col][number] = clRed;
        toQML_statusBar("Заданная концентрация газа больше концентрации в баллоне");
        return 3;
    }
    if (Conc_Gas == 0)  Factor_Dilute = 99999;
    else Factor_Dilute = (Conc_Balloon - Conc_Gas) / Conc_Gas;

    if (Factor_Dilute == 99999)  Flow_gas = 0;
    else    Flow_gas = Flow_sum / (Factor_Dilute + 1);

    Flow_air = Flow_sum - Flow_gas;

    if (RH == 0) Flow_vlag_gas = 0;
    else {
       Flow_vlag_gas = (Flow_sum * RH) / 100;
       Flow_air -= Flow_vlag_gas;
    }

    C_mix = C_gas * (1 - Conc_Balloon / 100) + Conc_Balloon / 100;
    C_mix = C_gas / C_mix;

    Flow_gas = Flow_gas / C_mix;

    if (Flow_gas<0 | Flow_air<0 | Flow_vlag_gas<0)
    {
//         for (int col=1; col<Form1->AdvStringGrid1->ColCount; col++)    // Красная строка
//          AdvStringGrid1->Colors[col][number] = clRed;
        toQML_statusBar("Отрицательные параметры расхода");
        return 3;
    }
    else if (Flow_air > Flow_max_suh)
    {
//         for (int col=1; col<Form1->AdvStringGrid1->ColCount; col++)    // Красная строка
//             AdvStringGrid1->Colors[col][number] = clRed;
        toQML_statusBar("Расход \"сухого разбавителя\" больше максимально заданного");
        return 3;
     }
     else if (Flow_gas > Flow_max_gas)
     {
//         for (int col=1; col<Form1->AdvStringGrid1->ColCount; col++)    // Красная строка
//          AdvStringGrid1->Colors[col][number] = clRed;
        toQML_statusBar("Расход \"целевого газа\" больше максимально заданного");
        return 3;
    }
    else if (Flow_vlag_gas > Flow_max_vlag)
    {
//         for (int col=1; col<Form1->AdvStringGrid1->ColCount; col++)    // Красная строка
//             AdvStringGrid1->Colors[col][number] = clRed;
        toQML_statusBar("Расход \"влажного разбавителя\" больше максимально заданного");
        return 3;
    }

    toQML_statusBar("Режим без ошибок");
    return 0;
}

void Parameters::button_calculateClick(){
    qDebug() << "button_calculateClick() what for??";
    toQML_statusBar("button_calculateClick()");
}
