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
/*
                ChartView {
                    title: "Канал 'Сухой разбавитель'"
                    anchors.fill: parent
                    antialiasing: true
                    // Define X-axis
                    ValueAxis {
                        id: xAxis
                        min: 0
                        max: 10
                        titleText: "X-Axis Label"
                    }

                    // Define Y-axis
                    ValueAxis {
                        id: yAxis
                        min: 0
                        max: 5
                        titleText: "Y-Axis Label"
                    }
                    LineSeries{
                        axisX: xAxis
                        axisY: yAxis

                        XYPoint { x: 1; y: 2 }
                        XYPoint { x: 3; y: 4 }
                        XYPoint { x: 5; y: 3 }
                    }
                }
*/
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
                }
                Column{
                    id: column
                    RadioB{
                        checked: true
                        text: "Red"
                    }
                    RadioB {
                        text: "Green"
                    }

                    RadioB {
                        text: "Blue"
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
                // Define X-axis
                ValueAxis {
                    id: xAxis2
                    min: 0
                    max: 10
                    titleText: "X-Axis Label"
                }

                // Define Y-axis
                ValueAxis {
                    id: yAxis2
                    min: 0
                    max: 5
                    titleText: "Y-Axis Label"
                }
                LineSeries{
                    axisX: xAxis2
                    axisY: yAxis2

                    XYPoint { x: 1; y: 2 }
                    XYPoint { x: 3; y: 4 }
                    XYPoint { x: 5; y: 3 }
                }
            }
        }
    }
}
