#ifndef CALIBRTABLE_H
#define CALIBRTABLE_H

#include <QFile>
#include <QTimer>

struct cfs_points{
    float c_mix[3][10];             // Поправочные коэффициенты для расходомеров
    float set_point[3][10];         // Калибровочные точки из таблицы
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
    float arr1[10][7];
//    float arr2_max;
    float arr2[10][7];
//    float arr3_max;
    float arr3[10][7];

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
