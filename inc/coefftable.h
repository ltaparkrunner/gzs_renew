#ifndef COEFFTABLE_H
#define COEFFTABLE_H

#include <QString>
#include <QFile>

struct ttable{
    QString f1;
    float   f2;
};

class coeffTable
{
public:
    coeffTable(QString tn = "Table.str");
private:
    QFile *cmbf;
    QList<ttable> tbl;
};

#endif // COEFFTABLE_H
