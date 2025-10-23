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
            var i,j,l
            var imax = lc.length/6
            var st
            const ml = 12//15
            var row
            console.log("onToQML_smplTbl imax: ", imax)

            lm2.clear()

            for(i = 6; i < 12; i++) {
                if (lc[i].length > ml){
                    var strlist = lc[i].split(" ")
                    l = strlist.length
                    st = "";
                    row = 1;
//                    strlist.foreach()
//                     console.log("onToQML_smplTbl lc.length: ", l)
                    for(j = 0; j < l; j++){
                        if((st.length + strlist[j].length) > (ml * row) && j > 0){
                            st = st + " \n" + strlist[j]
                            row++
//                            console.log("onToQML_smplTbl (st.lenght + strlist[j].length) > ml * row", )
                        }
                        else{
                            st = st + " " + strlist[j]
                        }
                    }
                    lm2.append({title1: st})
                }
                else lm2.append({title1:lc[i]})
            }
            tm21.clear()
            for(i=2; i<imax; i++){
                tm21.appendRow({"mnumber":lc[6*i], "duration":lc[6*i+1], "cncntr1":lc[6*i+2],
                               "cncntr2":lc[6*i+3], "sumStream":lc[6*i+4], "humidity":lc[6*i+5]})
            }
        }
    }
//    color: "ivory"
    TableModel{
        id: tm21
//        TableModelColumn { display: "mnumber"}
//        TableModelColumn { display: "duration"}
//        TableModelColumn { display: "cncntr1"}
//        TableModelColumn { display: "cncntr2"}
//        TableModelColumn { display: "sumStream"}
//        TableModelColumn { display: "humidity"}
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
//        function column2(){
//            if()

//        }
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
        id: smpl
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: header2.bottom
        clip: true

        model: tm21
          delegate: DelegateChooser {
              DelegateChoice {
                  column: 1
                  delegate: Rectangle {
                      implicitWidth: 100
                      implicitHeight: 30
                      border.width: 1
                      TextField {
                          text: display
                          // google AI regular expression for hh:mm:ss
                          validator: RegularExpressionValidator{regularExpression: /^([0-1][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])$/}
                          anchors.fill:parent
                          Keys.onReturnPressed: {
                                console.log("onToQML_smplTbl TextField Keys.onReturnPressed duration")
                          }
                          onEditingFinished: {
                                console.log("onToQML_smplTbl TextField Keys.onEditingFinished duration")
                          }
                      }
                  }
              }
              DelegateChoice {
                  delegate: Rectangle {
                      implicitWidth: 100
                      implicitHeight: 30
                      border.width: 1
                      TextField {
                          text: display
                          validator: RegularExpressionValidator{regularExpression: /^\d+$/}
                          anchors.fill:parent
                          Keys.onReturnPressed: {
                                console.log("onToQML_smplTbl TextField Keys.onReturnPressed EXCEPT DURATION")
                          }
                          onEditingFinished: {
                                console.log("onToQML_smplTbl TextField Keys.onEditingFinished EXCEPT DURATION")
                          }
                      }
                  }
              }
          }
    }

    HorizontalHeaderView {
        id: header2
        anchors.left: smpl.left
        anchors.right: smpl.right
        anchors.top: parent.top//topheader.bottom
        syncView: smpl
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
