import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0     //1.5


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
    Rectangle{
        anchors.fill: parent
//        HorizontalHeaderView {
//            id: horizontalHeader
//            anchors.left: tableView.left
//            anchors.top: parent.top
//            anchors.right: tableView.right // Ensure it aligns with the TableView's width
//            syncView: tableView // Synchronize with the TableView
//            clip: true // Clip content if it exceeds bounds
//        }

        TableView {
            id: tableView
            anchors.left: parent.left
            anchors.top: horizontalHeader.bottom // Position below the header
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            model: tableModel // Assign the model to the TableView

            // Define columns for the TableView
            TableViewColumn {
                role: "name"
//                header: "Fruit Name"
                title: "Fruit Name"
                width: parent.width / 3 // Distribute width
            }
            TableViewColumn {
                role: "color"
                header: "Color"
                width: parent.width / 3
            }
            TableViewColumn {
                role: "quantity"
                header: "Quantity"
                width: parent.width / 3
            }
        }
    }
}
