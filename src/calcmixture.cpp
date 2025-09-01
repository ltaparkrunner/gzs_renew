#include "calcmixture.h"

#include <QString>
#include <QTime>

//calcMixture::calcMixture()
//{

//}

int calcMixture::stationCalc(){
    int I;
    float F;
    QString S;
    QTime T;

    char DecimalSeparator = '.';
/*
         Label_MaxFlow_1->Color = clWhite;
         Label_MaxFlow_2->Color = clWhite;
         Label_MaxFlow_3->Color = clWhite;
         Label_ballon->Color = clWhite;
         AdvComboBox1->Color = clWhite;

    if (AdvStringGrid1->Colors[1][number] != clGrayText)
    {
                 for (int col=1; col<Form1->AdvStringGrid1->ColCount; col++)    					// Очистка цвета
       AdvStringGrid1->Colors[col][number] = clWhite;
    }
*/
/*
    if (!TryStrToTime(Form1->AdvStringGrid1->Cells[1][number],T))                    // Время
    {
       AdvStringGrid1->FocusCell(1,number);
       AdvStringGrid1->Colors[1][number] = clBlue;
                 StatusBar1->Panels->Items[1]->Text = "Ошибка ввода данных | Длительность";
       return 1;
         }

         if (!TryStrToFloat(Form1->AdvStringGrid1->Cells[2][number], F) | F<0 | F>100)    // Концентрация
    {
       AdvStringGrid1->FocusCell(2,number);
       AdvStringGrid1->Colors[2][number] = clBlue;
                 StatusBar1->Panels->Items[1]->Text = "Ошибка ввода данных | Концентрация";
       return 1;
    }
    else  Parameters.Conc_Gas = F;

         if (!TryStrToFloat(Form1->Label_ballon->Text , F) | F<0 | F>100)                 // Концентрация в баллоне
    {
                 Label_ballon->Color = clRed;
                 StatusBar1->Panels->Items[1]->Text = "Ошибка ввода данных | Концентрация в баллоне";
       return 1;
    }
    else  Parameters.Conc_Balloon = F;

         if (!TryStrToInt(Form1->AdvStringGrid1->Cells[4][number], I))                    // Сум. поток
    {
       AdvStringGrid1->FocusCell(4,number);
       AdvStringGrid1->Colors[4][number] = clBlue;
                 StatusBar1->Panels->Items[1]->Text = "Ошибка ввода данных | Сум. поток";
       return 1;
    }
    else  Parameters.Flow_sum = I;

         if (!TryStrToInt(Form1->AdvStringGrid1->Cells[5][number], I) | I<0 | I>100)      // Относительная влажность
         {
                 AdvStringGrid1->FocusCell(5,number);
       AdvStringGrid1->Colors[5][number] = clBlue;
                 StatusBar1->Panels->Items[1]->Text = "Ошибка ввода данных | Относительная влажность";
       return 1;
    }
    else  Parameters.RH = I;

         if (!TryStrToInt(Label_MaxFlow_1->Text, I))                              // MAX расход газа
    {
                 Label_MaxFlow_1->Color = clRed;
                 StatusBar1->Panels->Items[1]->Text = "Ошибка ввода данных | \"ЦЕЛЕВОЙ ГАЗ\"";
                 return 2;
    }
    else  Parameters.Flow_max_gas = I;

         if (!TryStrToInt(Label_MaxFlow_2->Text, I))                             // MAX расход сушняка
    {
                 Label_MaxFlow_2->Color = clRed;
                 StatusBar1->Panels->Items[1]->Text = "Ошибка ввода данных | \"СУХОЙ ВОЗДУХ\"";
       return 2;
    }
    else  Parameters.Flow_max_suh = I;

         if (!TryStrToInt(Label_MaxFlow_3->Text, I))                             // MAX расход влаги
    {
       Label_MaxFlow_3->Color = clRed;
                 StatusBar1->Panels->Items[1]->Text = "Ошибка ввода данных | \"ВЛАЖНЫЙ ВОЗДУХ\"";
       return 2;
    }
    else  Parameters.Flow_max_vlag = I;

    AnsiString Gas_mix = Form1->AdvComboBox1->Text;
         if (Gas_mix == "")                                                   // Тип целевого газа
         {
                 AdvComboBox1->Color = clRed;
                 StatusBar1->Panels->Items[1]->Text = "Ошибка ввода данных | Тип целевого газа";
       return 2;
    }
         try
    {
       unsigned int i;
       AnsiString Delimiters = ":";
                 for (i=1; i<=StrLen(Gas_mix.c_str()); i++)     // Определение поправочного коэффициента
       {
          if (IsDelimiter(Delimiters, Gas_mix, i))
          {
             String COOL = "";
             COOL = Gas_mix[i+2];
             COOL += Gas_mix[i+3];
             COOL += Gas_mix[i+4];
             COOL += Gas_mix[i+5];
             DecimalSeparator = '.';
             Parameters.C_gas = StrToFloat(COOL);
          }
       }
    }
    catch(...)
    {
       Parameters.C_gas = 1.00;
                 StatusBar1->Panels->Items[1]->Text = "ВНИМАНИЕ | Поправочный коэффициент = 1.00";
    }

         // РАСЧЕТ ПАРАМЕТРОВ //

    if (Parameters.Conc_Gas > Parameters.Conc_Balloon)
    {
 //      Parameters.Conc_Gas = Parameters.Conc_Balloon;
 //      AdvStringGrid1->Cells[2][number] = LabeledEdit5->Text;
 //      AdvStringGrid1->Cells[3][number] =
 //                     FloatToStr(StrToFloat(AdvStringGrid1->Cells[2][number])*10000); // % -> PPM
                 for (int col=1; col<Form1->AdvStringGrid1->ColCount; col++)    // Красная строка
                         AdvStringGrid1->Colors[col][number] = clRed;
                 StatusBar1->Panels->Items[1]->Text = "Заданная концентрация газа больше концентрации в баллоне";
       return 3;
    }
    if (Parameters.Conc_Gas == 0)
           Parameters.Factor_Dilute = 99999;
    else
       Parameters.Factor_Dilute = (Parameters.Conc_Balloon - Parameters.Conc_Gas) / Parameters.Conc_Gas;

    if (Parameters.Factor_Dilute == 99999)
       Parameters.Flow_gas = 0;
    else
       Parameters.Flow_gas = Parameters.Flow_sum / (Parameters.Factor_Dilute + 1);
    Parameters.Flow_air = Parameters.Flow_sum - Parameters.Flow_gas;

    if (Parameters.RH == 0)
       Parameters.Flow_vlag_gas = 0;
    else
    {
       Parameters.Flow_vlag_gas = (Parameters.Flow_sum * Parameters.RH) / 100;
       Parameters.Flow_air -= Parameters.Flow_vlag_gas;
    }

    Parameters.C_mix = Parameters.C_gas * (1 - Parameters.Conc_Balloon / 100) + Parameters.Conc_Balloon / 100;
    Parameters.C_mix = Parameters.C_gas / Parameters.C_mix;

    Parameters.Flow_gas = Parameters.Flow_gas / Parameters.C_mix;

    if (Parameters.Flow_gas<0 | Parameters.Flow_air<0 | Parameters.Flow_vlag_gas<0)
    {
                 for (int col=1; col<Form1->AdvStringGrid1->ColCount; col++)    // Красная строка
          AdvStringGrid1->Colors[col][number] = clRed;
                 StatusBar1->Panels->Items[1]->Text = "Отрицательные параметры расхода";
                 return 3;
    }
    else if (Parameters.Flow_air > Parameters.Flow_max_suh)
    {
                 for (int col=1; col<Form1->AdvStringGrid1->ColCount; col++)    // Красная строка
                         AdvStringGrid1->Colors[col][number] = clRed;
                 StatusBar1->Panels->Items[1]->Text = "Расход \"сухого разбавителя\" больше максимально заданного";
                 return 3;
         }
         else if (Parameters.Flow_gas > Parameters.Flow_max_gas)
         {
                 for (int col=1; col<Form1->AdvStringGrid1->ColCount; col++)    // Красная строка
          AdvStringGrid1->Colors[col][number] = clRed;
                 StatusBar1->Panels->Items[1]->Text = "Расход \"целевого газа\" больше максимально заданного";
                 return 3;
    }
    else if (Parameters.Flow_vlag_gas > Parameters.Flow_max_vlag)
    {
                 for (int col=1; col<Form1->AdvStringGrid1->ColCount; col++)    // Красная строка
                         AdvStringGrid1->Colors[col][number] = clRed;
                 StatusBar1->Panels->Items[1]->Text = "Расход \"влажного разбавителя\" больше максимально заданного";
       return 3;
    }

         StatusBar1->Panels->Items[1]->Text = "Режим без ошибок";
         // УсЁ у порядке !!!
*/
    return 0;

}
