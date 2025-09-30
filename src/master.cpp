#include "master.h"
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QSerialPort>

#include "wfiles.h"

master::master(QString cmb_name, QString tname,  QString clbr_name, int tim, QObject *parent) :
    QObject(parent)
//  , fn (fname)
//  , tm (tim)
//  , test_tmr (new QTimer(this))
  , params(cmb_name, tname, clbr_name, this)
//  , mo()
//  , fp (nullptr)
//  ,fp(new file_parser(fname, lag, parent))
//  , mbsvr(new mbTcpServer(parent))
{

//    connect(test_tmr, &QTimer::timeout, this, &master::ch_val);
//    test_tmr->start(1000);

    QTimer::singleShot(1000, this, &master::publish);
    for(int row=1; row < params.smplTbl.rowsNum; row++)
        params.checkTblRow(row);
    params.button_calculateClick();
    params.toQML_statusBar("Настройте связь с газовой станцией");

    qDebug() << "Check checksum STATION-3K.exe";
}

void master::publish(){
/*    const QList<QSerialPortInfo> */ serialPortInfos = QSerialPortInfo::availablePorts();
//    QList<QString> lc;
    qDebug()<< "Доступных последовательных портов: " << serialPortInfos.length();
    for (QSerialPortInfo port: serialPortInfos) {
       cports.append(port.portName());
       qDebug() << "Доступный последовательный порт: "<< port.portName();
    }
//    qDebug() << "Attempt to receive COMs, total: " << lc.length();
    if(cports.length() > 0) toQML_comList(cports);
    else {
        toQML_comList(cports);
        QMessageBox msgBox(QMessageBox::Warning, "Сообщение о проблеме", "Последовательные порты отсутствуют. Не получится связаться с газосмесительной установкой", QMessageBox::Close);
        msgBox.exec();
    }
}

int master::startInit(){
    int res = wfiles::checkFile(QString("Combo.str"));
    switch (res) {
        case -2: {
                QMessageBox msgBox(QMessageBox::Warning, "Сообщение о проблеме", "Не существует файла Combo.str, закрываю программу", QMessageBox::Close);
                msgBox.exec();
            }
            return res;
            break;
        case -1: {
                QMessageBox msgBox(QMessageBox::Warning, "Сообщение о проблеме", "Файл Combo.str изменен.\nДальнейшая работа невозможна, закрываю программу", QMessageBox::Close);
                msgBox.exec();
            }
            return res;
            break;
        case 0: {
                QList<QString>* cb = wfiles::linesOfFile(QString("Combo.str"));
                toQML_initListString(*cb, 1);
            }
    //        return res;
            break;
        default: {
                QMessageBox msgBox(QMessageBox::Warning, "Сообщение о проблеме", "Что-то пошло не так. Неправильная ветка программы", QMessageBox::Close);
                msgBox.exec();
            }
            return -3;
            break;
    }
    QFile cfile("Table.cfg");
    if(!cfile.open(QIODevice::ReadOnly | QIODevice::Unbuffered)){
         qDebug() << "startInit Could not open file for reading:" << cfile.errorString();
         QMessageBox msgBox(QMessageBox::Warning, "Сообщение о проблеме", "Файл Table.cfg изменен.\nДальнейшая работа невозможна, закрываю программу", QMessageBox::Close);
         msgBox.exec();
           return -2;
    }
    else{
        QList<QString>* cb = wfiles::linesOfFile(QString("Table.cfg"));
        toQML_initListString(*cb, 2);
    }
    QString timeString = "14:30:15";
    QString format = "hh:mm:ss";
    QTime time = QTime::fromString(timeString, format);
    QTime totalTime = wfiles::sumTime(QString("Table.cfg"));

    toQML_message("Настройте связь с газовой станцией");

    int crc_pr = wfiles::checkExe("STATION-3K.exe");
    return 0;
}

bool fileExist(QString fn){

    QFileInfo fileInfo(fn);

    if (fileInfo.exists()) {
        if (fileInfo.isFile()) {
            return true;
        } else return false;
    }
    else return false;

}



void master::openefile_fromQML(QString urlList){

    qDebug() << "inside func master::openedf_fromQML";
    qDebug() << "canConvert<QUrl>() successfully" << urlList;
    QString fn = urlList;

    if(fn.isEmpty() && fileExist("Calibr.str")){
        QFile cfile("Calibr.str");
        if(!cfile.open(QIODevice::ReadOnly | QIODevice::Unbuffered)){
             qDebug() << "openefile_fromQML Could not open file for reading:" << cfile.errorString();
               return;
        }
        QByteArray tmp = cfile.readAll();
        cfile.close();
        int len = tmp.length();
        tmp[len-2] = 4;
        char summ = wfiles::CalcCrc8(tmp, len-1);


        /*if(summ != tmp[len-1])*/{
            tmp[len-1] = summ;
            QMessageBox msgBox(QMessageBox::Warning, "Сообщение об действии", "Создаю Calibr_04.str. Номер 22, другая контрольная сумма", QMessageBox::Close);
            msgBox.exec();
            QFile cfile("Calibr_04.str");
            cfile.open(QIODevice::WriteOnly | QIODevice::Unbuffered);
            cfile.write(tmp);
        }
        tmp[len-2] = 40;
        summ = wfiles::CalcCrc8(tmp, len-1);
        {
                    tmp[len-1] = summ;
                    QMessageBox msgBox(QMessageBox::Warning, "Сообщение об действии", "Создаю Calibr_40.str. Номер 22, другая контрольная сумма", QMessageBox::Close);
                    msgBox.exec();
                    QFile cfile("Calibr_40.str");
                    cfile.open(QIODevice::WriteOnly | QIODevice::Unbuffered);
                    cfile.write(tmp);
                }
//        else {
//            QMessageBox msgBox(QMessageBox::Warning, "Сообщение об успехе", "Контрольная сумма правильная", QMessageBox::Close);
//            msgBox.exec();
//        }
    }
}

void master::startTest_fromQML(){
//    fn.remove("file:///");
    startTest();
}

void master::stopTest_fromQML(){
    stopTest();
}

void master::eqpRqst_fromQML(){

    QSerialPort *sp = new QSerialPort(serialPortInfos[0]);
    sp->open()
}

void master::sendPbData(){
    qDebug() << "message from inside func sendPbData";
//    fp->readPb();
//    QList<QString> li = {"1,1", "2,2", "3,3", "4,4", "5,5", "6,6", "7,7", "8,8", "9,9"};
//    toQML_data(li);
}

int master::startTest(){
    qDebug() << "message from inside func startTest";
//    if(test_tmr == nullptr) test_tmr = new QTimer(this);
//    connect(test_tmr, &QTimer::timeout, this, &master::sendPbData);
//    test_tmr->start(1000);
    return 0;
}

int master::stopTest(){
    qDebug() << "message from inside func stopTest";
//    if(test_tmr != nullptr) test_tmr->stop();
    return 0;
}

void master::ch_val(){
//    params.Factor_Dilute++;
//    qDebug() << "params.Factor_Dilute: " << params.Factor_Dilute;
}
