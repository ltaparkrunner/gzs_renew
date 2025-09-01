
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
int main(int argc, char *argv[])
{
    // QApplication must be used.
    QObject parentObject;
    QApplication app(argc, argv);
//    app.setWindowIcon(QIcon(":/clover_3.png"));
    app.setWindowIcon(QIcon(":/resources/Gas.ico"));
    QQmlApplicationEngine engine;//(/*QUrl("qrc:/main2.qml")*/);
//    uMain* um=new uMain();

    master um("Combo.str", "Table.cfg", "Calibr.str", 1000, &parentObject);

    QQmlContext *context = engine.rootContext();

    context->setContextProperty("master", &um);
    context->setContextProperty("cmbTbl", &(um.params.cmbTbl));
    context->setContextProperty("smplTbl", &(um.params.smplTbl));
    context->setContextProperty("clbrTbl", &(um.params.clbrTbl));
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
#endif


    return app.exec();
}
