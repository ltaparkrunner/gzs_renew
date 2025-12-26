#ifndef COMBOTABLE_H
#define COMBOTABLE_H

#include <QFile>
#include "auxil.h"
#include "crates.h"

struct tblrow{
   QString gname;
   QString gformula;
   float persentage;
};
class comboTable : public QObject
{
    Q_OBJECT
public:
    explicit comboTable(crates_t &cr, QString combon = "Combo.str", QObject *parent = nullptr);
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
    clr clrBn;
    int cur_row;
    clr clrCmb;
    crates_t &cr_r;
};

#endif // COMBOTABLE_H
