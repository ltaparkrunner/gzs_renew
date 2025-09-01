#include "combotable.h"
#include "wfiles.h"
#include <QTextStream>
#include <QStringList>
#include <QDebug>

#include <QTimer>
#include <QList>
comboTable::comboTable(QString cmbn, QObject *parent):
    QObject(parent)
,   cmbTblLen (0)
{
//    qDebug() << "comboTable constractor. Name: " << cmbn;
    cmbf = new QFile(cmbn);
    int res = wfiles::checkFile(cmbf);
    if (!cmbf->open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(cmbf);
    int i;
    for(i=0; (i<cmbTblLenMax) && (!in.atEnd()); i++) {
        bool ok;
        QString line = in.readLine();
        QStringList ls = line.split(' ');
        if(ls.length() > 3){
        if(ls[2] == ":" && ls[1].at(0) == '(') {
            tblrows[i].gname = ls[0];
            tblrows[i].gformula =  ls[1];
            tblrows[i].persentage = ls[3].toFloat(&ok);
        } else if(ls[3] == ":" && ls[2].at(0) == '('){
            tblrows[i].gname = ls[0] + " " + ls[1];
            tblrows[i].gformula =  ls[2];
            tblrows[i].persentage = ls[4].toFloat(&ok);
        }else if(ls[2] == ":" && ls[2].at(0) != '('){
            tblrows[i].gname = ls[0] + " " + ls[1];
            tblrows[i].gformula =  "";
            tblrows[i].persentage = ls[3].toFloat(&ok);
        }
        else qDebug() << "Не подходит.";
        if(!ok) qDebug() << "Проблема преобразования в десятичные числа.";
        }
    }
    cmbTblLen = i-1;

    QTimer::singleShot(8000, this, &comboTable::publish);
}

void comboTable::publish(){
    qDebug() << "From inside comboTable::publish";
    QList<QString> lc;
    for(int i1=0; i1<cmbTblLen; i1++){
       lc.append(tblrows[i1].gname);
       lc.append(tblrows[i1].gformula);
       lc.append(QString::number(tblrows[i1].persentage));
    }
    toQML_cmbTbl(lc);
//    qDebug() << "After toQML_cmbTbl(ls)";
}

int comboTable::checkTblrow(int r){
//    if()
    return 0;
}
