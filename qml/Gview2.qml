import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
import QtQuick.Controls 1.5


Rectangle {
    id: ch_com
//    width: 270
    color: "light green"
    Connections {
        target: master // Указываем целевое соединение
        onToQML_comList:
        {
            console.log("inside QML onToQML_comList")
//            for(c in lc){
//                cbItems.append({text: c})
//            }
        }
    }
    ColumnLayout{
        spacing: 3
    //    anchors.top: parent
    //    anchors.left: parent
        anchors.fill: parent
        Rectangle{
            id: r1
            implicitHeight : parent.height
            implicitWidth : parent.width
            color: "light blue"
            TabView {
                id: tbv1
                anchors.fill: parent

                Tab {
                    id: tb1
                    title: "Параметры работы"
                    WorkParams{
                    }
                }
                Tab {
                    id: tb2
                    title: "Визуализация работы"
                    Plot1{
                    }
                }
                Tab {
                    id: tb3
                    title: "Тесты"
                    Plot2{
                    }
                }
            }
        }
        Rectangle{
            anchors.bottom: parent.bottom
            implicitWidth : parent.width
            height: 20
            color: "yellow"
            Text{
                text: "forever"
            }
        }
    }
}
