#ifndef SLIDER_H
#define SLIDER_H

#include <QObject>
#include <QDebug>

struct slider : public QObject
{
    Q_OBJECT
public:
    explicit slider(int p, int m, QObject *parent = nullptr):QObject(parent), pos(p), max(m){}
    void publish(){
        toQML_setMax(max);
        toQML_setPos(pos);
    }
    int pos;
    int max;
public slots:
    void fromQML_posChanged(int p){
        if(pos != p){
            if(p > max) pos = max;
            else if(p<1) pos = 1;
            else pos = p;
            qDebug() << "Slider position is changed: " << p;
        }
    }
    void fromQML_sldrCompleted(){
        publish();
    }
signals:
    void toQML_setMax(int m);
    void toQML_setPos(int p);
private:
    void changeMax(int m){
        if(m != max){
            if(m < pos) {
                pos = m;
                emit toQML_setPos(pos);
            }
            max = m;
            toQML_setMax(max);
        }
    }
};

#endif // SLIDER_H
