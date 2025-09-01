import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.5


Window
{
    width: 600
    height: 500
    visible: true

    ListModel {
        id: myModel
        ListElement {
            column1: "A1"
            column2: "A2"
            column3: "A3"
        }
        ListElement {
            column1: "B1"
            column2: "B2"
            column3: "B3"
        }
        ListElement {
            column1: "C1"
            column2: "C2"
            column3: "C3"
        }
    }

    TableView {
        id: myTable
        anchors.fill: parent
        anchors.margins: 5
        TableViewColumn {
            role: "column1"
            title: "Column1"
            width: myTable.width / 3
            horizontalAlignment: Text.AlignHCenter
        }
        TableViewColumn {
            role: "column2"
            title: "Column2"
            width: myTable.width / 3
            horizontalAlignment: Text.AlignHCenter
        }
        TableViewColumn {
            role: "column3"
            title: "Column3"
            width: myTable.width / 3
            horizontalAlignment: Text.AlignHCenter
        }
        model: myModel
        itemDelegate: Item {
            Row {
                id: row
                anchors.fill: parent
                Text {
                    width: row.width/2
                    text: styleData.value
                    horizontalAlignment: Text.AlignHCenter
                }
                Text {
                    width: row.width/2
                    text: "drop here"
                    color: "red"
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
    }
}
