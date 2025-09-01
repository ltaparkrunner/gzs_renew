import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
import QtQuick.Controls 1.5
import QtQuick.Window 2.0
//import QtQuick.Window 1.5//2.15

//Rectangle{
Window{
    id: r1
//    implicitHeight : parent.height
//    implicitWidth : parent.width
    width: 1000
    height: 800
    color: "light blue"
    TabView {
        id: tbv1
        anchors.fill: parent

        Tab {
            id: tb1
            title: "Расходомер №1 (50 мл/мин)"
            Calibr1{
                property int tabn: 1
            }
        }
        Tab {
            id: tb2
            title: "Расходомер №2 (200 мл/мин)"
            Calibr1{
                property int tabn: 2
            }
        }
        Tab {
            id: tb3
            title: "Расходомер №2 (200 мл/мин)"
            Calibr1{
                property int tabn: 3
            }
        }
    }
}
