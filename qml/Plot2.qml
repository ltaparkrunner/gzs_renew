import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
import QtQuick.Controls 1.5

Item{
//    implicitHeight: parent.height
//    implicitWidth: parent.width
    height: 800
    width: 800
//    anchors.fill: parent
//    color: "yellow"
    Image {
        anchors.fill: parent
//        source: "grc:/resources/GAS2.jpg"
        source: "resources/GAS2.jpg"
    }
    Button {
        height: 40
        width: 200
        text: "Продувка газовой магистрали"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 15
        anchors.topMargin: 15
    }
    Rectangle {
        height: 180
        width: 150
        color: "lightblue"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 15
        anchors.bottomMargin: 15
        ColumnLayout{
            Label{
                text: "Тест клапанов"
            }
            CheckBox{
                text: "Клапан 1"
                onClicked: { console.log("Клапан 1 clicked.")}
            }
            CheckBox{
                text: "Клапан 2"
                onClicked: { console.log("Клапан 2 clicked.")}
            }
            CheckBox{
                text: "Клапан 3"
                onClicked: { console.log("Клапан 3 clicked.")}
            }
            CheckBox{
                text: "Клапан 4"
                onClicked: { console.log("Клапан 4 clicked.")}
            }
        }
    }
    Item{
        x: 720
        y: 240
        height: 100
        width: 90
        Label{
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            text: "1"
            font.family: "Helvetica"; font.pointSize: 20; font.bold: true
        }
        Rectangle{
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            height: l11.height + 2
            width: l11.width + 2
            color: "red"
            Label {
                id: l11
                anchors.centerIn: parent
                color: "black"
                text: "CLOSE"
                font.family: "Helvetica"; font.pointSize: 20; font.bold: true
            }
        }
    }
    Item{
        x: Math.round(parent.width * 420/1048)  //420
        y: Math.round(parent.height * 110/1048)     //110
        height: 100
        width: 90
        Label{
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            text: "2"
            font.family: "Helvetica"; font.pointSize: 20; font.bold: true
        }
        Rectangle{
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            height: l12.height + 2
            width: l12.width + 2
            color: "red"
            Label {
                id: l12
                anchors.centerIn: parent
                color: "black"
                text: "CLOSE"
                font.family: "Helvetica"; font.pointSize: 20; font.bold: true
            }
        }
    }
    Item{
        x: 420
        y: 240
        height: 100
        width: 90
        Label{
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            text: "3"
            font.family: "Helvetica"; font.pointSize: 20; font.bold: true
        }
        Rectangle{
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            height: l13.height + 2
            width: l13.width + 2
            color: "red"
            Label {
                id: l13
                anchors.centerIn: parent
                color: "black"
                text: "CLOSE"
                font.family: "Helvetica"; font.pointSize: 20; font.bold: true
            }
        }
    }
    Item{
        x: 420
        y: 370
        height: 100
        width: 90
        Label{
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            text: "4"
            font.family: "Helvetica"; font.pointSize: 20; font.bold: true
        }
        Rectangle{
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            height: l14.height + 2
            width: l14.width + 2
            color: "red"
            Label {
                id: l14
                anchors.centerIn: parent
                color: "black"
                text: "CLOSE"
                font.family: "Helvetica"; font.pointSize: 20; font.bold: true
            }
        }
    }
    Item{
        x: 240
        y: 120
        height: 70
        width: 90
        Label {
            text: "Целевой газ"
            color: "white"
            font.family: "Helvetica"; font.pointSize: 10; font.bold: true
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }
        ProgressBar {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            implicitWidth: 150
            implicitHeight: 20
            value: 0
        }
    }
    Item{
        x: 240
        y: 245
        height: 70
        width: 90
        Label {
            text: "Сухой разбавитель"
            color: "white"
            font.family: "Helvetica"; font.pointSize: 10; font.bold: true
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }
        ProgressBar {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            implicitWidth: 150
            implicitHeight: 20
            value: 0
        }
    }
    Item{
        x: 240
        y: 380
        height: 70
        width: 90
        Label {
            text: "Влажный разбавитель"
            color: "white"
            font.family: "Helvetica"; font.pointSize: 10; font.bold: true
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }
        ProgressBar {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            implicitWidth: 150
            implicitHeight: 20
            value: 0
        }
    }
}
