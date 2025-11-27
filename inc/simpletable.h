#ifndef SIMPLETABLE_H
#define SIMPLETABLE_H

#include <QString>
#include <QTime>
#include <QFile>
#include <QList>

struct ttl_t{
    int offset;
    bool sucs_of;
    QString nm;
    bool sucs_nm;
};
struct dt_t{
    int num_row;
    bool sucs_nr;
    QTime duration;
    bool sucs_dur;
    int cncntr1;
    bool sucs_c1;
    int cncntr2;
    bool sucs_c2;
    int sumStream;
    bool sucs_ss;
    int relatHumidity;
    bool sucs_rH;
};

struct dim_t{
    int height;
    int width;
    bool sucs_h;
    bool sucs_w;
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
    QFile *stf;

    int rowsNum;
//    int checkTableRow(int n);
signals:
    void toQML_smplTbl(QList<QString> lc);
public slots:
    void fromQML_smplTableCompleted();
    void fromQML_smplTableEditFinished(QList<QString> ls);
public:
    bool isTable();
    int color(int col, int row, QString color);
    bool isCell(int col, int row);
};

#endif // SIMPLETABLE_H
