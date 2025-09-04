import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0
import QtQml.Models 2.15 // 2.0

Rectangle{
//        anchors.fill: parent
    color: "lightblue"
    height: 800
    width: 800

//    ListView{
    TableView {
        height: 800
        width: 800

//        ListModel {
/*
        TableModel{
            id: lm1
//            ListElement { type:"info", value: "1"}
            ListElement { type:"info";      value: "1"}
            ListElement { type:"switch";    value: "2"}
            ListElement { type:"swipe";      value: "3"}
            ListElement { type:"info";      value: "4"}
            ListElement { type:"switch";    value: "5"}
            ListElement { type:"swipe";      value: "6"}
        }
*/
        TableModel{
            id: lm1
//            ListElement { type:"info", value: "1"}
            TableModelColumn { display:"info"}
            TableModelColumn { display:"switch"}
            TableModelColumn { display:"swipe"}
            rows:[{ "info":"info",
                    "switch":"info",
                    "swipe":"swipe"},
                  { "info":"info",
                    "switch":"switch",
                    "swipe":"swipe"
                    }]
        }
/*
        TableModel{
            id: lm1
            TableModelColumn { display : "mnumber"}
            TableModelColumn { display: "duration"}
            TableModelColumn { display: "cncntr1"}
            TableModelColumn { display: "cncntr2"}
            TableModelColumn { display: "sumStream"}
            TableModelColumn { display: "humidity"}
            rows:[{
                "mnumber" : "mnumber",
                "duration" : "duration",
                "cncntr1" : "cncntr1",
                "cncntr2" : "cncntr2",
                "sumStream" : "sumStream",
                "humidity" : "humidity"
            }]
        }
*/
        DelegateChooser{
            id: ch1
            role:"display"
            DelegateChoice { roleValue: "info"; /*ItemDelegate {*/ Rectangle { implicitHeight: 30; implicitWidth: 100;
                        border.width: 1; color:"lightyellow"; Text { text: display; anchors.fill: parent } } } //}
            DelegateChoice { roleValue: "switch"; /*ItemDelegate {*/ Rectangle { implicitHeight: 30; implicitWidth: 100;
                        border.width: 1; color:"lightgreen"; Text { text: display; anchors.fill: parent } } } //}
            DelegateChoice { roleValue: "swipe"; /*ItemDelegate {*/ Rectangle { implicitHeight: 30; implicitWidth: 100;
                        border.width: 1; color:"orange"; Text { text: display; anchors.fill: parent } } } //}
        }
        model: lm1
        delegate: ch1
    }
}
