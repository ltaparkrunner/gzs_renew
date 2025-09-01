import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
import QtQuick.Controls 1.5

Rectangle{
//    id: r1
    implicitHeight : parent.height
    implicitWidth : parent.width
    color: "green"
    ColumnLayout{
//        implicitHeight : parent.height
//        implicitWidth : parent.width
//        Layout.fillWidth: true
        anchors.fill: parent
        RowLayout{
            anchors.fill: parent
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
                    property int pr: rp
                }
            }
            ColumnLayout {
//                anchors.centerIn: parent
//                anchor
                spacing: 10
                Button{
                    text: "OK"
                }
                ExclusiveGroup { id: colorGroup }

                RadioButton {
                    text: "Red"
                    exclusiveGroup: colorGroup
                    checked: true // Initially checked
                }

                RadioButton {
                    text: "Green"
                    exclusiveGroup: colorGroup
                }

                RadioButton {
                    text: "Blue"
                    exclusiveGroup: colorGroup
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
