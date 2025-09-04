import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0
import QtQml.Models 2.15 // 2.0

Rectangle{
//        anchors.fill: parent
    color: "lightblue"
    height: 800
    width: 800

    ListView{
        height: 800
        width: 800

        ListModel {
            id: lm1
//            ListElement { type:"info", value: "1"}
            ListElement { type:"info";      value: "1"}
            ListElement { type:"switch";    value: "2"}
            ListElement { type:"swipe";      value: "3"}
            ListElement { type:"info";      value: "4"}
            ListElement { type:"switch";    value: "5"}
            ListElement { type:"swipe";      value: "6"}
        }
        DelegateChooser{
            id: ch1
            role:"type"
            DelegateChoice{ roleValue: "info"; ItemDelegate{ Rectangle{height: 30; width:100; color:"lightyellow"}}}
            DelegateChoice{ roleValue: "switch"; ItemDelegate{ Rectangle{height: 30; width:100; color:"lightgreen"}}}
            DelegateChoice{ roleValue: "swipe"; ItemDelegate{ Rectangle{height: 30; width:100; color:"orange"}}}
        }
        model: lm1
        delegate: ch1
    }
}
