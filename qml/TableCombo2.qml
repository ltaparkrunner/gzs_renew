import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0
import QtQml.Models 2.15
ComboBox {
    id: check_cb
    width:300
    height: 70

    currentIndex: 0

    model: cbListModel
    ListModel {
        id: cbListModel
        ListElement { key: "Option 1"; key2: "Option 6"}
        ListElement { key: "Option 2"; key2: "Option 7" }
        ListElement { key: "Option 3"; key2: "Option 8" }
        ListElement { key: "Option 4"; key2: "Option 9" }
        ListElement { key: "Option 5"; key2: "Option 10" }
    }
    textRole: {"key"; "key2"}

    delegate: ItemDelegate {
        width: check_cb.width
        background: Rectangle {
            color: "lightblue"
        }
        contentItem: Text {
//            text: modelData
            text: model.key + " " + model.key2
            font.pointSize: 16
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    contentItem: Text {
        id: name
//        text: check_cb.displayText
//        text: cbListModel.data(0, "key")
        text: cbListModel.get(check_cb.currentIndex).key + " " + cbListModel.get(check_cb.currentIndex).key2
        font.pointSize: 16
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    onActivated: {
        console.log("Selected Text: ", check_cb.currentText)
        console.log("Selected Index: ", check_cb.currentIndex)
    }
    background: Rectangle{
        color: "green"
    }

}
