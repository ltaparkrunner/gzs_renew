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
//        onToQML_comList:
        function onToQML_comList(lc)
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
            Layout.alignment: Qt.AlignTop
//            implicitHeight : 60//parent.height
//            implicitHeight : parent.height - cndln.height
            Layout.fillHeight: true
//            implicitWidth : parent.width
            Layout.fillWidth: true
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
                    anchors.fill: parent
                    title: "Тесты"
                    Plot2{
                    }
                }
/*                Tab {
                    id: tb4
                    anchors.fill: parent
                    title: "Scroll View"
                    Scroll_1{
                    }
                }
                Tab {
                    id: tb5
                    anchors.fill: parent
                    title: "Chooser View"
                    Chooser_1{
                    }
                }
                Tab {
                    id: tb6
                    anchors.fill: parent
                    title: "Chooser View"
                    Choose_2{
                    }
                }
                */
            }
        }
        Rectangle{
            id: cndln
//            anchors.bottom: parent.bottom
            Layout.alignment: Qt.AlignBottom
            Layout.fillWidth: true
//            implicitWidth : parent.width
//            width:200
            height: 20
            color: "yellow"
            Text{
                text: "forever"
            }
        }
    }
}
