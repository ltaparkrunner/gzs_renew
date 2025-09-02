import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0

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
//        onToQML_smplTbl:
        function onToQML_smplTbl(lc)
        {
            var i
            var imax = lc.length/6
            console.log("onToQML_smplTbl imax: ", imax)
//            lm2.model[0] = lc[6]
            lm2.clear()
            lm2.append({title1:lc[6]})
            lm2.append({title1:lc[7]})
            lm2.append({title1:lc[8]})
            lm2.append({title1:lc[9]})
            lm2.append({title1:lc[10]})
            lm2.append({title1:lc[11]})
//            header2.model[1] = lc[7]
//            header2.model[0] = lc[8]
//            header2.model[1] = lc[9]
//            header2.model[0] = lc[10]
//            header2.model[1] = lc[11]
//            tvc1.title = lc[6];
//            tvc2.title = lc[7];
//            tvc3.title = lc[8];
//            tvc4.title = lc[9];
//            tvc5.title = lc[10];
//            tvc6.title = lc[11];
//            for(i = 2; i<imax; i++){
//                lm1.append({"mnumber":lc[6*i], "duration":lc[6*i+1], "cncntr1":lc[6*i+2],
//                               "cncntr2":lc[6*i+3], "sumStream":lc[6*i+4], "humidity":lc[6*i+5]})
//            }
        }
    }
//    color: "ivory"
    TableModel{
        id: tm21
        TableModelColumn { display: "mnumber"}
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

//    HorizontalHeaderView {
//        id: topheader
//        anchors.left: calibr.left
//        anchors.right: calibr.right
//        anchors.top: parent.top
//        syncView: header
//        clip: true
//    }

    TableView {
        id: calibr2
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: header2.bottom
        clip: true

        model: tm21
          delegate: Rectangle {
              implicitWidth: 100
              implicitHeight: 20
              border.width: 1
              Label {
                  text: display
                  anchors.centerIn: parent
              }
          }
    }

    HorizontalHeaderView {
        id: header2
        anchors.left: calibr2.left
        anchors.right: calibr2.right
        anchors.top: parent.top//topheader.bottom
        syncView: calibr2
        clip: true
//        model: [ "Номер режима",
//            "Длительность подачи газовой смеси", "Концентрация газовой смеси (%, ppm)",
//            "Концентрация газовой смеси (%, ppm)", "Суммарный поток газовой смеси (ml/min)",
//            "Относительная влажность газовой смеси (%)" ]
        model: ListModel{
            id:lm2
            ListElement {title1: "Номер режима"}
            ListElement {title1: "Длительность \nподачи \nгазовой смеси"}
            ListElement {title1: "Концентрация \nгазовой \nсмеси (%, ppm)"}
            ListElement {title1: "Концентрация \nгазовой \nсмеси (%, ppm)"}
            ListElement {title1: "Суммарный \nпоток газовой \nсмеси (ml/min)"}
            ListElement {title1: "Относительная \nвлажность \nгазовой \nсмеси (%)"}
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
//        console.log("inside TableCalib")
    }
}
