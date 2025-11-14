import QtQuick 2.15
import QtQuick.Layouts 1.0
import QtCharts 2.0
import QtQuick.Controls 2.15
//import Qt.labs.qmlmodels 2.0

Rectangle{
    id: r1
//    implicitHeight : parent.height
//    implicitWidth : parent.width
    Layout.fillHeight: true
    Layout.fillWidth: true
    color: "green"
    property var locale: Qt.locale()
    property string timeString: "14:30:00"
    property string timeFormat: "hh:mm:ss"


    Connections{
        target: clbrTbl
        function onToQml_clbrPlot(lc) {
//            console.log("QML_onToQml_clbrPlot", lc[0], "  ", lc[1], "  ", lc[2])
            xAxis2.max = new Date(lc[0])
            ls1.append(xAxis2.max, lc[1])
        }
        function onToQml_clbrAxis(lc){
            console.log("onToQml_clbrAxis  ", lc[0], "  ", lc[1])
            xAxis2.min = new Date(lc[0])
            xAxis2.max = new Date(lc[1])
        }
    }
    ColumnLayout{
//        implicitHeight : parent.height
//        implicitWidth : parent.width
//        Layout.fillWidth: true
        anchors.fill: parent
//        Layout.fillHeight: true
//        Layout.fillWidth: true
        RowLayout{
            Layout.fillHeight: true
            Layout.fillWidth: true
//            anchors.fill: parent
//            Layout.fillWidth: true
//            implicitHeight : parent.height
//            implicitWidth : parent.width
            Rectangle{
//                width: 500
//                height: 300
//                implicitWidth: parent.width
//                anchors.fill: parent
                Layout.fillHeight: true
                Layout.fillWidth: true
                height: 250
                color: "lightyellow"

                TableCalibr{
                    id: tc
                    property int tabln: tabn
                }
            }
            ColumnLayout {
//                anchors.centerIn: parent
//                anchor
                spacing: 10
                Button{
                    text: "OK"
                }
//                ExclusiveGroup { id: colorGroup }
                ButtonGroup {
                    buttons: column.children
//                    onButtonsChanged: console.log("RadioB changed ", column.index)
                }
                Column{
                    id: column
                    RadioB{
//                        checked: true
                        text: "1"
                        onClicked: clbrTbl.fromQML_RadioB(tabn, text, "0.0")
                    }
                    RadioB {
                        text: "2"
                        onClicked: clbrTbl.fromQML_RadioB(tabn, text, "0.0")
                    }
                    RadioB {
                        text: "3"

                        onClicked: {
                            var val = tc.getValue(text)
                            clbrTbl.fromQML_RadioB(tabn, text, val)
                        }
                    }
                    RadioB {
                        text: "4"
                        onClicked: clbrTbl.fromQML_RadioB(tabn, text, "0.0")
                    }
                    RadioB {
                        text: "5"
                        onClicked: clbrTbl.fromQML_RadioB(tabn, text, "0.0")
                    }
                    RadioB {
                        text: "6"
                        onClicked: clbrTbl.fromQML_RadioB(tabn, text, "0.0")
                    }
                    RadioB {
                        text: "7"
                        onClicked: clbrTbl.fromQML_RadioB(tabn, text, "0.0")
                    }
                    RadioB {
                        text: "8"
                        onClicked: clbrTbl.fromQML_RadioB(tabn, text, "0.0")
                    }
                    RadioB {
                        text: "9"
                        onClicked: clbrTbl.fromQML_RadioB(tabn, text, "0.0")
                    }
                    RadioB {
                        text: "10"
                        onClicked: clbrTbl.fromQML_RadioB(tabn, text, "0.0")
                    }
                    RadioB {
                        text: "none"
                        onClicked: clbrTbl.fromQML_RadioB(tabn, "0", "0.0")
                    }
                }
            }
        }
        Rectangle{
//                width: 500
//                height: 300
//                implicitWidth: parent.width
//                anchors.fill: parent
            Layout.fillHeight: true
            Layout.fillWidth: true
            height: 250
            color: "lightyellow"
            ChartView {
                title: "Канал 'Сухой разбавитель'"
                anchors.fill: parent
                antialiasing: true
                id: cv1
                // Define X-axis
                DateTimeAxis {
//                ValueAxis{
                    id: xAxis2
                    format: "hh:mm:ss"
                    // min: new Date().getTime() - 12000
                    // max: new Date().getTime()
//                    min: new Date("2023-12-25")
//                    max: new Date(xAxis2.min.addSecs(10))
//                    max: new Date(1970, 1, 1, 19, 30, 7, 0)
//                    titleText: "X-Axis Label"
                }

                // Define Y-axis
                ValueAxis {
                    id: yAxis2
                    min: -1
                    max: 2
                    titleText: "Сигнал, В"
                }
                LineSeries{
                    id: ls1
                    axisX: xAxis2
                    axisY: yAxis2
                    color: "blue"
                    // XYPoint { x: new Date().getTime()-10000; y: 2 }
                    // XYPoint { x: new Date().getTime()-5000; y: 1.5 }
                    // XYPoint { x: new Date().getTime(); y: 1.4 }
                }
                LineSeries{
                    id: ls2
                    axisX: xAxis2
                    axisY: yAxis2
                    color: "green"
                    // XYPoint { x: 1; y: 3 }
                    // XYPoint { x: 3; y: 7 }
                    // XYPoint { x: 5; y: 4 }
                }
                // Component.onCompleted: {
                //     let t3 = new Date()
                //     xAxis2.max = t3
                //     console.log("ChartView is completed t3: ", xAxis2.max, "   ", xAxis2.max.toTimeString(),  "  ", xAxis2.max.toString())
                //     xAxis2.min = new Date(t3.getTime()-1000)
                //     console.log("ChartView is completed xAxis.max: ", xAxis2.min, "   ", xAxis2.min.toTimeString(),  "  ", xAxis2.min.toString())
                // }
            }
        }
    }
}
