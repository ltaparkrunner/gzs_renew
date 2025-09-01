import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.5

Window
{

//    HorizontalHeaderView {
//        id: horizontalHeader
//        anchors.left: tableView.left
//        anchors.top: parent.top
//        syncView: tableView
//        clip: true
//    }
TableView {
    id: tableView
    width: 400
    height: 300
    model: ListModel {
        ListElement { name: "John Doe"; age: 30; city: "New York" }
        ListElement { name: "Jane Smith"; age: 25; city: "London" }
    }

    TableViewColumn {
        role: "name"
//        header: "Name"
        title: "Name"
        width: 150
    }

    TableViewColumn {
        role: "details" // This role will combine age and city
//        header: "Details"
        title: "Details"
        width: 200
        delegate: Item {
            Text {
                text: model.age + " years old"
                anchors.top: parent.top
                anchors.left: parent.left
            }
            Text {
                text: "Lives in " + model.city
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: 80 // Adjust spacing
            }
        }
    }
}
}
