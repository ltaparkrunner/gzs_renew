#include "mtime.h"
#include <QDebug>

mtime::mtime(QString hh, QString mm, QString ss){
    bool ok;
    s = ss.toInt(&ok);
    m = 0;
    if(!ok || s < 0) {
        rel = false; return;
    }
    else if(s > 59){
        m = s / 60;
        s = s % 60;
    }
    m = m + mm.toInt(&ok);
    h = 0;
    if(!ok || m < 0) {
        rel = false; return;
    }
    else if(m > 59) {
        h = m / 60;
        m = m % 60;
    }
    h = h + hh.toInt(&ok);
//    qDebug() << "ok= " << ok << "    h= " << h << "   hh =" << hh;
    if(!ok || h < 0) {
        rel = false; return;
    }
    rel = true;
}


mtime::mtime(int hh, int mm, int ss){
    s = ss;
    m = 0;
    if(s < 0) {
        rel = false; return;
    }
    else if(s > 59){
        m = s / 60;
        s = s % 60;
    }
    m = m + mm;
    h = 0;
    if(m < 0) {
        rel = false; return;
    }
    else if(m > 59) {
        h = m / 60;
        m = m % 60;
    }
    h = h + hh;
    if(h < 0) {
        rel = false; return;
    }
    rel = true;
}

bool mtime::operator >(const mtime other){
    if(this->h > other.h) return true;
    else if(this->h < other.h) return false;
    else {
        if(this->m > other.m) return true;
        else if(this->m < other.m) return false;
        else {
            if(this->s > other.m) return true;
            else return false;
        }
    }
}

mtime mtime::operator +(const mtime other){
    int ss = this->s + other.s;
    int mm = 0;
    if(ss < 0) {
        return mtime(0, 0, ss);
    }
    else if(ss > 59){
        mm = ss / 60;
        ss = ss % 60;
    }

    mm = mm + this->m + other.m;
    int hh = 0;
    if(mm < 0) {
        return mtime(0, mm, ss);
    }
    else if(mm > 59){
        hh = mm / 60;
        mm = mm % 60;
    }

    hh = hh + this->h + other.h;
    return mtime(hh, mm, ss);
}

bool mtime::isValid() {
    return rel;
}

QString mtime::to_string(){
    return (QString::number(h) + ":" + QString::number(m) + ":" + QString::number(s));
}
