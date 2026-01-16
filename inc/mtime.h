#ifndef MTIME_H
#define MTIME_H

#include <QString>

struct mtime{
    int h;
    int m;
    int s;

    bool rel;

    mtime(QString hh, QString mm, QString ss);
    mtime(int hh, int mm, int ss);
    bool isValid();
    bool operator >(const mtime other);
    mtime operator +(const mtime other);
    QString to_string();
};

#endif // MTIME_H
