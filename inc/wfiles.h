#ifndef WFILES_H
#define WFILES_H

#include <QString>
#include <QList>
#include <QTime>
#include <QFile>

class wfiles
{
public:
//    wfiles();
  static int checkFile(QString fname);
  static int checkFile(QFile* cfile);
  static int checkFile(QString fname, QFile *fl);
  static int loadCombo(QString &fname);
  static int checkExe(QString fname);
  static char CalcCrc8(QByteArray cBlock, int len);
  static QList<QString>* linesOfFile(QString fname);
  static QTime sumTime(QString fname);
};

#endif // WFILES_H
