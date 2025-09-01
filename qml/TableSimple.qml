//import QtQuick 2.0
//import QtQuick.Controls 2.0
//// import TableModel
//// import Qt.labs.qmlmodels 2.0
import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0

import QtQuick.Controls 1.5

Rectangle {
//    implicitWidth: tv.width
    implicitHeight: tv.height
    anchors.left: parent.left
    anchors.right: parent.right
    Connections{
        target: smplTbl
//        onToQML_smplTbl:
        function onToQML_smplTbl(lc)
        {
            var i
            var imax = lc.length/6
            console.log("onToQML_smplTbl imax: ", imax)
            for(i = 0; i<imax; i++){
                lm1.append({"mnumber":lc[6*i], "duration":lc[6*i+1], "cncntr1":lc[6*i+2],
                               "cncntr2":lc[6*i+3], "sumStream":lc[6*i+4], "humidity":lc[6*i+5]})
            }
        }
    }
    color: "ivory"
                TableView {
                    id:tv
                    anchors.fill: parent
                    clip: true

                    TableViewColumn {
                        role: "mnumber"
                        title: "Mode number"
                    }

                    TableViewColumn {
                        role: "duration"
                        title: "Duration"
                    }

                    TableViewColumn {
                        role: "cncntr1"
                        title: "Concentration 1"
                    }

                    TableViewColumn {
                        role: "cncntr2"
                        title: "Concentration 2"
                    }

                    TableViewColumn {
                        role: "sumStream"
                        title: "Full Stream"
                    }

                    TableViewColumn {
                        role: "humidity"
                        title: "Humidity"
                    }

                    model: ListModel {
                        id:lm1

                        ListElement {
                            mnumber: "h1"
                            duration: "down1"
                            cncntr1: "345561"
                            cncntr2: "forev"
                            sumStream: "again"
                            humidity: "humidity"
                        }
                    }
                }
    Component.onCompleted: {
        smplTbl.fromQML_smplTableCompleted()
//        console.log("inside TableCalib")
    }
}
