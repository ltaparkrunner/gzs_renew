#ifndef SIMPLETABLE_H
#define SIMPLETABLE_H

#include <QString>
#include <QTime>
#include <QFile>
#include <QList>

struct ttl_t{
    int offset;
    QString nm;
};
struct dt_t{
    int num_row;
    QTime duration;
    int cncntr1;
    int cncntr2;
    int sumStream;
    int relatHumidity;
};

struct dim_t{
    int height;
    int width;
};

struct simpleTable : public QObject
{
    Q_OBJECT
public:
    ttl_t ttl[6];
    dt_t dt[4];
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
};

#endif // SIMPLETABLE_H
