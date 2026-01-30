#include "master.h"
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QProcess>

#include "wfiles.h"
extern "C" {
    #include "sio.h"
    #include "i7k.h"
    #include "i87000_lnx.h"
}
master::master(QString cmb_name, QString tname,  QString clbr_name, int stn, int tim, QObject *parent) :
    QObject(parent)
,   params(cmb_name, tname, clbr_name, this)
,   st_num(stn)
,   crc(wfiles::checkExe("gaz_mixer"))
{
//    params.button_calculateClick();
    qDebug() << "Check checksum STATION-3K.exe" << crc;    // TODO: Calculate STATION-3K.exe CRC16
}

void master::appendSerials(){
/*    const QList<QSerialPortInfo> */ serialPortInfos = QSerialPortInfo::availablePorts();
//    qDebug()<< "Доступных последовательных портов: " << serialPortInfos.length();
    for (QSerialPortInfo port: serialPortInfos) {
       cports.append(port.portName());
       qDebug() << "Доступный последовательный порт: "<< port.portName();
    }
//    qDebug() << "Attempt to receive COMs, total: " << lc.length();
    if(cports.length() > 0) emit toQML_comList(cports);
    else {
        emit toQML_comList(cports);
        QMessageBox msgBox(QMessageBox::Warning, "Сообщение о проблеме", "Последовательные порты отсутствуют. Не получится связаться с газосмесительной установкой", QMessageBox::Close);
        msgBox.exec();
    }
}

int master::startInit(){
    int num;
    int res = wfiles::checkFile(QString("Combo.str"), num);
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
                emit toQML_initListString(*cb, 1);
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
        emit toQML_initListString(*cb, 2);
    }
    QString timeString = "14:30:15";
    QString format = "hh:mm:ss";
    QTime time = QTime::fromString(timeString, format);
    QTime totalTime = wfiles::sumTime(QString("Table.cfg"));

    emit toQML_message("Настройте связь с газовой станцией");

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
        tmp[len-2] = 5;
        char summ = wfiles::CalcCrc8(tmp, len-1);


        /*if(summ != tmp[len-1])*/{
            tmp[len-1] = summ;
            QMessageBox msgBox(QMessageBox::Warning, "Сообщение об действии", "Создаю Calibr_05.str. Номер 05, другая контрольная сумма", QMessageBox::Close);
            msgBox.exec();
            QFile cfile("Calibr_05.str");
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

// bool terminal_finished = false;
// void master::pwExit(/*int ec, QProcess::ExitStatus es*/){
//     terminal_finished = true;
// }

void master::eqpRqst_fromQML(QString pname){
    QProcess *proc = new QProcess(this);
    QString prog ="xfce4-terminal";
//    QString prog = "mousepad";
    QStringList args;

    for(QSerialPortInfo pinfo: serialPortInfos){
        if (pinfo.portName() == pname) {
            qDebug() << "bash -c 'sudo chmod 777 " + pinfo.systemLocation() + "; exit; exec bash'";
            args << "-e" << "bash -c 'sudo chmod 777 " + pinfo.systemLocation() + "; exit; exec bash'";
//            args << "-e" << "bash -c 'sudo chmod 777 /dev/ttyS0; exit; exec bash'";
            proc->start(prog, args);
            proc -> waitForFinished(-1);
            sp = new serial(pinfo);
            if(!sp->open()) {
                QMessageBox msgBox(QMessageBox::Warning, "Сообщение о проблеме", "Не могу открыть последовательный порт " + sp->portName() , QMessageBox::Close);
                msgBox.exec();
            }
            else{
                QMessageBox msgBox(QMessageBox::Warning, "Сообщение об успехе 2", "Последовательный порт " + sp->portName() + " успешно открыт." , QMessageBox::Close);
                msgBox.exec();
            }
            break;
        }
    }
    if(sp->isOpen()) sp->close();
//    qDebug() << "Serial port name: " << sp->portName() << ",   Object Name: " << sp->objectName();
    int err;
//    qDebug() << "Master st_num = " << st_num;
//    gst = new station("/dev/ttyUSB0",  st_num /* 6 */, err, this);  // TODO: take choosen serial port
//    pname = QString("/dev/") + pname;
    gst = new station(QString("/dev/") + pname,  st_num /* 6 */, err, this);  // TODO: take choosen serial port
    switch(err){
        case 0:{
            QMessageBox msgBox(QMessageBox::Warning, "Инициализация прошла успешно", "Загрузите/создайте настройки газовой станции." , QMessageBox::Close);
            msgBox.exec();
            emit toQML_startMainW();}
            break;
        default:
            {QMessageBox msgBox(QMessageBox::Warning, "Сообщение о проблеме", "Не могу подключиться к станции." , QMessageBox::Close);
            msgBox.exec();}
            break;
    }
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

void master::calibOpened_fromQML(){
    qDebug() << "calibOpened_fromQML";
}

void master::calibClosed_fromQML(){
    qDebug() << "calibClosed_fromQML";
}

void master::fromQML_btnStart(/*lc*/){
    int pos;
    WORD err;

    if(isBlowing == true) fromQML_btn_blowing();
    // Manipulation with AdvTrackBar

    /*** ПРОВЕРКА НА КРАСНОТУ ***/

    if((wht != params.cr.clr_MF_1) || (wht != params.cr.clr_MF_2) ||
    (wht != params.cr.clr_MF_3) || (wht != params.cr.clr_mbln))
//    ||(cb1.isproper()))
    {
        QMessageBox msgBox(QMessageBox::Warning, "Сообщение о проблеме", "В таблице калибровки неправильные данные (Это точно про калибровку, может быть это главная таблица?)" , QMessageBox::Close);
        msgBox.exec();
        return;
    }
    if(!params.smplTbl.isTable()){
        QMessageBox msgBox(QMessageBox::Warning, "Сообщение о проблеме", "В основной таблице неправильные данные." , QMessageBox::Close);
        msgBox.exec();
        return;
    }

}

void master::fromQML_btnStop(){

}

void master::fromQML_btn_blowing(){

}

master::~master(){
    params.clbrTbl.~calibrTable();
    params.cmbTbl.~QObject();
    params.smplTbl.~QObject();
    params.cr.~QObject();
    params.~QObject();
}

void master::fromQML_ApplicationWindowCompleted(){
    qDebug() << "master::fromQML_ApplicationWindowCompleted";
    QString str = "Настройте связь с газовой станцией";
    emit params.toQML_statusBar(str);
//    emit params.toQML_statusBar();
    appendSerials();
}
