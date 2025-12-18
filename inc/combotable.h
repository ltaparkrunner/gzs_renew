#ifndef COMBOTABLE_H
#define COMBOTABLE_H

#include <QFile>
#include "auxil.h"

struct tblrow{
   QString gname;
   QString gformula;
   float persentage;
};
class comboTable : public QObject
{
    Q_OBJECT
public:
    explicit comboTable(QString combon = "Combo.str", QObject *parent = nullptr);
    void publish();
    int checkTblrow(int r);
signals:
    void toQML_cmbTbl(QList<QString> lc);
private:
    QFile *cmbf;

    const int cmbTblLenMax = 30;
    int cmbTblLen;
public:
    tblrow tblrows[30];
//    clr clrCombo;
    float ballon;
    clr clrBn;
    int cur_row;
    clr clrCmb;
};

#endif // COMBOTABLE_H
