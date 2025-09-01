#include "wfiles.h"

#include <QFile>
#include <QDebug>

//wfiles::wfiles()
//{
//}
//int wfiles::checkFile(QString fname){
//    QFile cfile(fname);
int wfiles::checkFile(QFile* cfile){
    if(!cfile->open(QIODevice::ReadOnly | QIODevice::Unbuffered)){
         qDebug() << "wfiles::checkFile Could not open file for reading:" << cfile->errorString();
           return -2;
    }
    else{
        QByteArray tmp = cfile->readAll();
        cfile->close();
        int len = tmp.length();
        char summ = CalcCrc8(tmp, len-2); // tmp[len-1] == EOF ??

        if(summ != tmp[len-2]) return -1;
    }
    cfile->close();
    return 0;
}

int wfiles::checkFile(QString fname){
    QFile* cfile = new QFile(fname);
    if(!cfile->open(QIODevice::ReadOnly | QIODevice::Unbuffered)){
         qDebug() << "Could not open file for reading:" << cfile->errorString();
           return -2;
    }
    else{
        QByteArray tmp = cfile->readAll();
        cfile->close();
        int len = tmp.length();
        char summ = CalcCrc8(tmp, len-2); // tmp[len-1] == EOF ??

        if(summ != tmp[len-2]) return -1;
    }
    cfile->close();
    return 0;
}

int wfiles::checkFile(QString fname, QFile *fl){
    QFile cfile(fname);
    fl = nullptr;
    if(!cfile.open(QIODevice::ReadOnly | QIODevice::Unbuffered)){
         qDebug() << "Could not open file for reading:" << cfile.errorString();
           return -2;
    }
    else{
        QByteArray tmp = cfile.readAll();
        cfile.close();
        int len = tmp.length();
        char summ = CalcCrc8(tmp, len-2); // tmp[len-1] == EOF ??

        if(summ != tmp[len-2]) return -1;
    }
    cfile.close();
    fl = &cfile;
    return 0;
}

int wfiles::loadCombo(QString &fname){}
int wfiles::checkExe(QString fname){
    QFile cfile(fname);
    unsigned char crc = 0xff;
    if(!cfile.open(QIODevice::ReadOnly | QIODevice::Unbuffered)){
         qDebug() << "Could not open file for reading:" << cfile.errorString();
           return 0x01;
    }
    else{
        unsigned char tem;


        QByteArray tmp = cfile.readAll();
        cfile.close();
        int len = tmp.length();
        for(int i=0; i>len-1; i++){

        }


    }
    return crc;
}

char wfiles::CalcCrc8(QByteArray cBlock, int len)
{
    char crc = 0xFF;
    unsigned int i;

    QByteArray::iterator pcBlock = cBlock.begin();
    while(len--)
    {
        crc ^= *pcBlock++;
        for(i=0; i<8; i++)
            crc = crc & 0x80 ? (crc<<1) ^ 0x31 : crc << 1;
    }
    return crc;
}

QList<QString>* wfiles::linesOfFile(QString fname){
    return new QList<QString>({"1.1", "2.2", "3.3", "4.4", "5.5", "6.6", "7.7", "8.8"});
}

QTime wfiles::sumTime(QString fname) {
    return QTime(3, 2, 10);
}
