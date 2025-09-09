import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
import QtQuick.Controls 1.5
import QtCharts 2.9

Rectangle{
    implicitHeight: parent.height
    implicitWidth: parent.width
    color: "green"

    Timer{
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            var now = new Date();
//            NewVariable.text = Qt.formatDateTime(now, "hh:mm:ss")
        }
    }

    RowLayout{
        anchors.fill: parent
        Button{
            Layout.alignment: Qt.AlignTop
//            anchors.top: parent.top
            text: "Очистить все"
        }
        Rectangle{
            height: 600
            width: 800
            color: "violet"

        ScrollView{
                anchors.fill: parent
//            Layout.fillHeight: true
//            Layout.fillWidth: true
            Rectangle{
//                Layout.fillHeight: true
//                Layout.fillWidth: true
    //            anchors.fill: parent
                color: "red"
                height: 900
                width: 800
        ColumnLayout{
//            Layout.alignment: Qt.AlignTop
//            Layout.fillWidth: true
//            Layout.fillHeight: true
            anchors.fill: parent
//            anchors.top: parent.top
            Rectangle{
//                property date currentDate: new Date()
//                property date midDate: new Date(currentDate - 1.5 * 60 * 1000)
//                property date prevDate: new Date(currentDate - 3 * 60 * 1000)
//                var currentDate = new Date()
//                var midDate = new Date(currentDate - 1.5 * 60 * 1000)
//                var prevDate = new Date(currentDate - 3 * 60 * 1000)

                implicitWidth: parent.width
                Layout.fillWidth: true
//                width:100
                height: 250
                color: "lightgreen"
                ChartView {
                    title: "Канал 'Целевой газ'"
                    anchors.fill: parent
                    antialiasing: true
                    // Define X-axis
                    legend.visible: false
                    margins.bottom: 0
                    margins.top: 0
                    margins.left: 0
                    margins.right: 0

                    DateTimeAxis{
                        id: xAxis1
//                        min: prevDate //{new Date(); return Date.now()}
//                        max: currentDate
                        format: "dd-MM-yyyy hh:mm"
                    }

                    ValueAxis {
                        id: yAxis1
                        min: 0
                        max: 5
                        titleText: "Сигнал, В"
                    }

                    LineSeries{
                        axisX: xAxis1
                        axisY: yAxis1
                        XYPoint { x: new Date().getTime() - 120000; y: 2 }
                        XYPoint { x: new Date().getTime() - 60000; y: 4 }
                        XYPoint { x: new Date().getTime(); y: 3 }
                    }

                }
            }
            Rectangle{
//                implicitWidth: parent.width
                Layout.fillWidth: true
                height: 250
                color: "lightyellow"
                ChartView {
                    title: "Канал 'Сухой разбавитель'"
                    anchors.fill: parent
                    antialiasing: true
                    // Define X-axis
                    legend.visible: false
                    margins.bottom: 0
                    margins.top: 0
                    margins.left: 0
                    margins.right: 0
                    ValueAxis {
                        id: xAxis2
                        min: 0
                        max: 10
        //                        titleText: "X-Axis Label"
                    }
                    ValueAxis {
                        id: yAxis2
                        min: 0
                        max: 5
                        titleText: "Сигнал, В"
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
            Rectangle{
//                implicitWidth: parent.width
                Layout.fillWidth: true
                height: 250
                color: "lightblue"
                ChartView {
                    title: "Канал 'Влажный разбавитель'"
                    anchors.fill: parent
                    antialiasing: true
                    // Define X-axis
                    legend.visible: false
                    margins.bottom: 0
                    margins.top: 0
                    margins.left: 0
                    margins.right: 0
                    ValueAxis {
                        id: xAxis3
                        min: 0
                        max: 10
        //                        titleText: "X-Axis Label"
                    }
                    ValueAxis {
                        id: yAxis3
                        min: 0
                        max: 5
                        titleText: "Сигнал, В"
                    }
                    LineSeries{
                        axisX: xAxis3
                        axisY: yAxis3

                        XYPoint { x: 1; y: 2 }
                        XYPoint { x: 3; y: 4 }
                        XYPoint { x: 5; y: 3 }
                    }

                }
            }
        }
        }
        }
        }
    }


//    }
//    }
}
