import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0
import QtQml.Models 2.15

//import QtQuick 2.0
import QtQuick.Layouts 1.0
//import QtCharts 2.0

//import QtQuick.Controls 1.5

Rectangle {
//    implicitWidth: tv.width
//    implicitHeight: tv.height
//    anchors.left: parent.left
//    anchors.right: parent.right
//    Layout.fillHeight: true
//    Layout.fillWidth: true
    height: 200
    width: 800
    color: "green"

    Connections{
        target: smplTbl
        function onToQML_smplTbl2(ln, ls){
            console.log("onToQML_smplTbl2(lc)")
//            tm21.clear()
            tm21.appendRow({"mnumber":"forever", "color1":"lightblue", "duration":"young", "color2":"lightblue"}) //, "bgColor":"lightgreen",  "bgColor2":"lightblue"})//, "hum_cl":"lightgreen"})
            tm21.appendRow({"mnumber":"forever", "color1":"lightblue", "duration":"young", "color2":"lightblue"}) //, "bgColor":"lightgreen", "bgColor2":"lightblue"})//, "hum_cl":"lightgreen"})
        }
    }
    Connections{
        target: params
    }

    TableModel{
        id: tm21
        TableModelColumn { display: "mnumber"; background: "color1"}
        TableModelColumn { display: "duration"; background: "color2"}
//        TableModelColumn { background:  "bgColor"}
//        TableModelColumn { display:  "bgColor"}
//        TableModelColumn { background:  "bgColor2"}
//        TableModelColumn { background:  function(modelIndex){return "white"}}
        rows:[{
                "mnumber" : "mnumber", "color1":"lightgreen",
                "duration" : "duration", "color2":"red"
//                "bgColor": "lightblue",
//                "bgColor2": "green"
            },
            {
                "mnumber" : "mnumber", "color1":"lightgreen",
                "duration" : "duration",  "color2":"blue"
//                "bgColor": "lightblue",
//                "bgColor2": "blue"
            }]
    }

    TableView {
        id: smpl
        height: 200
        width: 800

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: header2.bottom
//        clip: true

        model: tm21
        delegate: DelegateChooser {
            role: "display"// "background"
            DelegateChoice {

                roleValue: "mnumber"
                delegate: Rectangle{
                    implicitWidth: 100
                    implicitHeight: 30
                    border.width: 1
                    // TextField {
                    //     text: display
                    //     readOnly: true
                    //     anchors.fill:parent
                    // }
                    color: background         //"yellow"//model.background
                }
            }
            // DelegateChoice {
            //     roleValue: "bgColor"
            //     delegate: Rectangle{
            //         implicitWidth: 100
            //         implicitHeight: 30
            //         border.width: 1
            //     }
            // }
            // DelegateChoice {
            //     roleValue: "bgColor2"
            //     delegate: Rectangle{
            //         implicitWidth: 100
            //         implicitHeight: 30
            //         border.width: 1
            //         // TextField {
            //         //     text: display
            //         //     readOnly: true
            //         //     anchors.fill:parent
            //         // }
            //         color: "lightgreen"//model.background
            //     }
            // }
            DelegateChoice {
                roleValue: "duration"
                delegate: Rectangle{
                    implicitWidth: 100
                    implicitHeight: 30
                    border.width: 1
                    // color: { var indx = tm21.index(row, 3)
                    //     return tm21.data(indx, "bgColor")
                    // }
                    color: background
                }
            }
            // DelegateChoice {
            //     roleValue: "bgColor"
            //     delegate: Rectangle{
            //         implicitWidth: 100
            //         implicitHeight: 30
            //         border.width: 1
            //         color: "lightblue"//model.background
            //     }
            // }
            // DelegateChooser {
            //             role: "background"
            // DelegateChoice {
            //     delegate: Rectangle{
            //         implicitWidth: 100
            //         implicitHeight: 30
            //         border.width: 1
            //         color: "lightblue"
            //     }
            // }
        }
        // DelegateChooser{
        //     role: "background"
        //     DelegateChoice {
        //         roleValue: "bgColor"
        //         delegate: Rectangle{
        //             implicitWidth: 100
        //             implicitHeight: 30
        //             border.width: 1
        //             color: "lightgreen"//model.background
        //         }
        //     }
        // }

        // delegate:Rectangle{
        //     implicitWidth: 100
        //     implicitHeight: 30
        //     color: "yellow"
        // }
    }

    HorizontalHeaderView {
        id: header2
        anchors.left: smpl.left
        anchors.right: smpl.right
        anchors.top: parent.top//topheader.bottom
        syncView: smpl
        clip: true

        model: ListModel{
            id:lm2
            ListElement {title1: "Номер режима"}
            ListElement {title1: "Длительность \nподачи \nгазовой смеси"}
        }

        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 80
            border.width: 1
//            Label {
            Text {
                text: title1
                anchors.centerIn: parent
            }
        }
    }
    Component.onCompleted: {
        smplTbl.fromQML_smplTableCompleted()
    }
}
