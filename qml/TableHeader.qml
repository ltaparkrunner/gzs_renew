import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("HeaderView")

    Rectangle {
        anchors.fill: parent
//        color: Application.styleHints.appearance === Qt.Light ? palette.mid : palette.midlight
        color: "light green"
        TableModel {
            id: myModel
            TableModelColumn { display: "name" }
            TableModelColumn { display: "color" }

            rows: [
                {
                    name: "cat",
                    color: "black"
                }
            ]
        }
        TableView {
            id: tView
            anchors.left: parent.left
            anchors.top: hHeader.bottom
//            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            clip: true
            model: myModel
            delegate: Rectangle {
                implicitWidth: 100
                implicitHeight: 20
                border.width: 1
//                Label {
                Text {
                    text: display
                    anchors.centerIn: parent
                }
            }
        }
        HorizontalHeaderView {
            id: hHeader
            anchors.left: tView.left
            anchors.right: tView.right
            anchors.top: parent.top
            syncView: tView
            clip: true
//            textRole: "display"

            model: ["name", "color"]
//            delegate: Rectangle {
//                implicitWidth: 100
//                implicitHeight: 20
//                border.width: 1
////                Label {
//                Text{
//                    text: modelData
//                    anchors.centerIn: parent
//                }
//            }
        }

    }
}
