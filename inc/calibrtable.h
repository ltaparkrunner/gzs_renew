#ifndef CALIBRTABLE_H
#define CALIBRTABLE_H

#include <QFile>
#include <QTimer>

struct cfs_points{
    float c_mix[3][10];             // Поправочные коэффициенты для расходомеров
    float c_mix_temp[3][10];
    float set_point[3][10];         // Калибровочные точки из таблицы
    float set_point_temp[3][10];
};
struct calibRow{
    int num;
    float pc1;
    float ml1;
    float pc2;
    float ml2;
    float pc3;
    float ml3;
    float coeff;
};

struct calibrTable : public QObject
{
    Q_OBJECT
public:
    struct top_t{
        int f;
        QString s;
    } top;
//    float arr1_max;
//    float arr1[10][7];
//    float arr2_max;
//    float arr2[10][7];
//    float arr3_max;
//    float arr3[10][7];

    calibRow tbl1[10];
    calibRow tbl2[10];
    calibRow tbl3[10];
    int MaxFlow_1;
    int MaxFlow_2;
    int MaxFlow_3;
    calibrTable(QString clb_name = "Combo.str", QObject *parent = nullptr);
    ~calibrTable();
    void publish();
    QFile *clbrf;
signals:
    void toQML_clbrTbl(QList<QString> lc);
    void toQML_clbrTbl2(QList<QString> lc, int tln);
    void toQml_clbrPlot(QList<QString> lc);
    void toQML_clbrTbl3(float, int);
public slots:
    void fromQML_calibTableCompleted(QString id);
    void fromQML_calibTableCompleted(int id);
//    void fromQML_RadioB(QString tabn, QString rbn);
    void fromQML_RadioB(QString tabn, QString rbn, QString value);
    void fromQML_calibTableManualEditingFinished(int tabn, int row, int column);
private:
    int curtabn;
    int currbn;
    float curvalue;
    QTimer *calibTmr;
    void calibStage();
    cfs_points cfpt;
//    unsigned int Max
//    void fromQML_
};

#endif // CALIBRTABLE_H
