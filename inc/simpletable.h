#ifndef SIMPLETABLE_H
#define SIMPLETABLE_H

#include <QString>
#include <QTime>
#include <QFile>
#include <QList>

#include "auxil.h"

struct ttl_t{       // Titles
    int offset;
    clr clr_of;
    QString nm;
    clr clr_nm;
};
struct dt_t{        // main table
    int num_row;
    clr clr_nr;
    QTime duration;
    clr clr_dur;
    int cncntr1;
    clr clr_c1;
    int cncntr2;
    clr clr_c2;
    int sumStream;
    clr clr_sS;
    int relatHumidity;
    clr clr_rH;
};

struct dim_t{       // table dimentions
    int height;
    int width;
    clr clr_h;
    clr clr_w;
};

struct simpleTable : public QObject
{
    Q_OBJECT
public:
    ttl_t ttl[6];
    QVector<dt_t> dt;
    dim_t dim;

    /*explicit*/ simpleTable(QString tn = "Table.cfg", QObject *parent = nullptr);
    /*explicit*/ simpleTable(QObject *parent = nullptr);
    void publish();
    void publish2();
    QFile *stf;

    int rowsNum;
//    int checkTableRow(int n);
signals:
    void toQML_smplTbl(QList<QString> lc);
    void toQML_smplTbl2(QList<int> lc, QList<QString> ls);
public slots:
    void fromQML_smplTableCompleted();
//    void fromQML_smplTableEditFinished(QList<QString> ls);
    void fromQML_smplTableEditFinished(QList<QString> ls, int row, int clmn);
public:
    bool isTable();
    int color(int col, int row, QString color);
    bool isCell(int col, int row);
};

#endif // SIMPLETABLE_H
