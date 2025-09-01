import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
import QtQuick.Controls 1.5
import QtCharts 2.1

Rectangle{
    implicitHeight: parent.height
    implicitWidth: parent.width
    color: "green"
    RowLayout{
        anchors.fill: parent
        Button{
            Layout.alignment: Qt.AlignTop
//            anchors.top: parent.top
            text: "Очистить все"
        }
        ColumnLayout{
            Layout.alignment: Qt.AlignTop
//            anchors.top: parent.top
            Rectangle{
//                implicitWidth: parent.width
                Layout.fillWidth: true
//                width:100
                height: 250
                color: "lightgreen"
                ChartView {
                    title: "Канал 'Целевой газ'"
                    anchors.fill: parent
                    antialiasing: true
                }
            }
            Rectangle{
//                implicitWidth: parent.width
                Layout.fillWidth: true
                height: 250
                color: "lightyellow"
                ChartView {
//                    title: "Канал 'Сухой разбавитель'"
                    anchors.fill: parent
                    antialiasing: true
                    // Define X-axis
                    legend.visible: false
                    margins.bottom: 0
                    margins.top: 0
                    margins.left: 0
                    margins.right: 0
                    ValueAxis {
                        id: xAxis
                        min: 0
                        max: 10
//                        titleText: "X-Axis Label"
                    }

                    // Define Y-axis
                    ValueAxis {
                        id: yAxis
                        min: 0
                        max: 5
//                        titleText: "Y-Axis Label"
                    }

                    LineSeries{
                        axisX: xAxis
                        axisY: yAxis

                        XYPoint { x: 1; y: 2 }
                        XYPoint { x: 3; y: 4 }
                        XYPoint { x: 5; y: 3 }
                    }
                }
            }
            Rectangle{
//                implicitWidth: parent.width
                Layout.fillWidth: true
                height: 250
                color: "lightblue"
                ChartView {
                    title: "Канал 'Влажный разбавитель'"
                    anchors.fill: parent
                    antialiasing: true
                }
            }
        }
    }
}
