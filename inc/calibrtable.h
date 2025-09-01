#ifndef CALIBRTABLE_H
#define CALIBRTABLE_H

#include <QFile>
struct calibrTable : public QObject
{
    Q_OBJECT
public:
    struct top_t{
        int f;
        QString s;
    } top;
    float arr1_max;
    float arr1[10][3];
    float arr2_max;
    float arr2[10][3];
    float arr3_max;
    float arr3[10][3];

    int MaxFlow_1;
    int MaxFlow_2;
    int MaxFlow_3;
    calibrTable(QString clb_name = "Combo.str", QObject *parent = nullptr);
    void publish();
    QFile *clbrf;
signals:
    void toQML_clbrTbl(QList<QString> lc);
public slots:
    void fromQML_calibTableCompleted(QString id);
};

#endif // CALIBRTABLE_H
