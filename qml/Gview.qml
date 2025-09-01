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

        Text{
            id: uppText
            //x: 10
    //        y: 10
            text: 'Выберите COM порт:'
        }
        ComboBox {
//            text: "Выберите COM порт:"
            currentIndex: 0
//            currentText: 'Выберите COM порт:'
//            displayText : "Выберите COM порт:"
            model: ListModel {
                id: cbItems
                ListElement { text: "Не существует"; color: "yellow"}
            }
            width: 200
            onCurrentIndexChanged: console.log(cbItems.get(currentIndex).text + ", " + cbItems.get(currentIndex).color)
        }
        Button{
            id : connectButt
            text: "Открыть COM порт"
            onClicked: {
    //            controlIp.connectButt(ip_2.ip_t, ip_2.port_t)
                cbItems.append({ text: "Cucumber", color: "light Green" })
            }

        }
        Button{
            id : sendMessButt
            text: "Read params"
            onClicked: {
//                controlIp.reqParamsButt()
//                controlIp.sendMsgButt()
            }
        }
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
                    title: "Combo Table"
                    TableCombo{
                    }
                }
                Tab {
                    id: tb2
                    title: "Table.cfg"
                    TableSimple{
                    }
                }
                Tab {
                    id: tb3
                    title: "Calibr Table"
                    TableCalibr{
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
