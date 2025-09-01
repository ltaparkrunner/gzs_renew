import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.5

Window {
    width: 400
    height: 300
    visible: true
    title: "QML Table with Column Titles"

    Column {
        anchors.fill: parent

        HorizontalHeaderView {
            id: headerView
            syncView: tableView // Syncs the header with the TableView
            model: myTableModel // Uses the same model as the TableView
            delegate: Rectangle {
                implicitWidth: 100 // Adjust as needed
                implicitHeight: 30 // Adjust as needed
                border.width: 1
                border.color: "lightgray"
                Text {
                    text: modelData // Displays the header data from the model
                    anchors.centerIn: parent
                    font.bold: true
                }
            }
        }

        TableView {
            id: tableView
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: parent.height - headerView.height // Adjust height to accommodate header
            columnSpacing: 1
            rowSpacing: 1
            clip: true

            model: TableModel {
                id: myTableModel
                TableModelColumn { display: "Name" }
                TableModelColumn { display: "Age" }

                rows: [
                    { "Name": "Alice", "Age": 30 },
                    { "Name": "Bob", "Age": 25 }
                ]
            }

            delegate: Rectangle {
                implicitWidth: 100 // Adjust as needed
                implicitHeight: 30 // Adjust as needed
                border.width: 1
                border.color: "lightgray"
                Text {
                    text: display
                    anchors.centerIn: parent
                }
            }
        }
    }
}
