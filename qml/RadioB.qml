import QtQuick 2.15
import QtQuick.Layouts 1.0
import QtCharts 2.0
import QtQuick.Controls 2.15

RadioButton {
//    id: b1
//    text: "Red"
//    checked: true // Initially checked
    indicator: Rectangle {
        implicitWidth: 14
        implicitHeight: 14
        x: parent.leftPadding
        y: parent.height / 2 - height / 2
        radius: 7
        border.color: parent.down ? "#17a81a" : "#21be2b"

        Rectangle {
            width: 6
            height: 6
            x: 4
            y: 4
            radius: 3
            color: parent.parent.down ? "#17a81a" : "#21be2b"
            visible: parent.parent.checked
        }
    }

    contentItem: Text {
        text: parent.text
        font: parent.font
        opacity: enabled ? 1.0 : 0.3
        color: parent.down ? "#17a81a" : "#21be2b"
        leftPadding: parent.indicator.width + parent.spacing
    }
}
