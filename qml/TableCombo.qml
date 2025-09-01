import QtQuick 2.0
import QtQuick.Controls 1.5

Rectangle {
    Connections{
        target: cmbTbl
        onToQML_cmbTbl:
        {
            var i
            var imax = lc.length/3
            console.log("imax: ", imax)
            for(i = 0; i<imax; i++){
                lm1.append({"designation":lc[3*i], "formula":lc[3*i+1], "proportion":lc[3*i+2]})
            }
        }
    }
    color: "snow"
    TableView {
        id:tv1
        anchors.fill: parent
        clip: true

        TableViewColumn {
            role: "designation"
            title: "Designation"
        }

        TableViewColumn {
            role: "formula"
            title: "Formula"
        }

        TableViewColumn {
            role: "proportion"
            title: "Proportion"
        }

        model: ListModel {
            id: lm1
        }
    }
}

