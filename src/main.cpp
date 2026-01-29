
#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtCore/QDir>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>

#include "master.h"
#include "mycppobject.h"
#include <QDebug>

#include "wfiles.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    // QApplication must be used.
    QObject parentObject;
    QApplication app(argc, argv);
    app.setOrganizationName("OAO Avangard");
    app.setOrganizationDomain("aoAvangard.org");

    app.setWindowIcon(QIcon(":/resources/Gas.ico"));
    int st_num;                                         // TODO: check of station number Calibr.str vs facility(equpment, station ), write the right Calibr.str)
    int res = wfiles::checkFile("Calibr.str", st_num);
//    qDebug() << "Current working directory: " << QDir::currentPath();
    if(res == -1) {
        QMessageBox msgBox(QMessageBox::Critical, "Фатальная ошибка", "Отсутствует файл калибровки\nCalibr.str.", QMessageBox::Close);
        msgBox.exec();
        QGuiApplication::exit(-1);
        return -1;
    }
    else if(res == -2) {
        QMessageBox msgBox(QMessageBox::Critical, "Фатальная ошибка", "Файл калибровки Calibr.str изменен.\nДальнейшая работа невозможна.", QMessageBox::Close);
        msgBox.exec();
        QGuiApplication::exit(-2);
        return -2;
    }

    res = wfiles::checkFile("Combo.str");
//    qDebug() << "Current working directory: " << QDir::currentPath();
    if(res == -1) {
        QMessageBox msgBox(QMessageBox::Critical, "Фатальная ошибка", "Отсутствует файл калибровки\nCombo.str.", QMessageBox::Close);
        msgBox.exec();
        QGuiApplication::exit(-1);
        return -1;
    }
    else if(res == -2) {
        QMessageBox msgBox(QMessageBox::Critical, "Фатальная ошибка", "Файл калибровки Combo.str изменен.\nДальнейшая работа невозможна.", QMessageBox::Close);
        msgBox.exec();
        QGuiApplication::exit(-2);
        return -2;
    }

    // TODO: check Combo.str
    QQmlApplicationEngine engine;   //(/*QUrl("qrc:/main2.qml")*/);
    //    uMain* um=new uMain();

    master um("Combo.str", "Table.cfg", "Calibr.str", st_num, 1000, &parentObject);

    QQmlContext *context = engine.rootContext();

    context->setContextProperty("params", &(um.params));
    context->setContextProperty("master", &um);
    context->setContextProperty("crTbl", &(um.params.cr));
    context->setContextProperty("cmbTbl", &(um.params.cmbTbl));
    context->setContextProperty("smplTbl", &(um.params.smplTbl));
    context->setContextProperty("clbrTbl", &(um.params.clbrTbl));
//    context->setContextProperty("params", &(um.params));
//    context->setContextProperty("MyCppObject", &um.mo);

// The following are needed to make examples run without having to install the module
// in desktop environments.
#ifdef Q_OS_WIN
    QString extraImportPath(QStringLiteral("%1/../../../../%2"));
#else
    QString extraImportPath(QStringLiteral("%1/../../../%2"));
#endif

#if QT_VERSION >= 0x060000
    engine.load(QUrl("qrc:/main.qml"));
#else
    engine.load(QUrl("qrc:/main_5.qml"));
//    engine.load(QUrl("qrc:/TableHeader.qml"));
#endif


    return app.exec();
}
