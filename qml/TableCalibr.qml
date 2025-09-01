import QtQuick 2.0
import QtQuick.Controls 1.5
Rectangle {
//    property var rp: parent.parent.parent.parent
    anchors.fill: parent
    Connections{
        target: clbrTbl
        onToQML_clbrTbl:
        {
            var i
            var imax = lc.length/3
            console.log("imax: ", imax)
            for(i = 0; i<imax; i++){
                lm1.append({"one":lc[3*i], "two":lc[3*i+1], "three":lc[3*i+2]})
            }
        }
    }
//    color: "floralwhite"
    TableView {
        anchors.fill: parent
        clip: true

        TableViewColumn {
            role: "one"
            title: "One"
        }

        TableViewColumn {
            role: "numOfRow"
            title: "N"
        }

        TableViewColumn {
            role: "spending"
            title: "Three"
        }

        model: ListModel {
            id: lm1
            ListElement {
                one: "h1"
                two: "down1"
                three: "345561"
            }
            ListElement {
                one: "h2"
                two: "down2"
                three: "345562"
            }
            ListElement {
                one: "h3"
                two: "down3"
                three: "345563"
            }

        }
    }
    Component.onCompleted: {
        if(pr === 1) {
            clbrTbl.fromQML_calibTableCompleted("id1")
            console.log("inside TableCalib 1")
        }
        if(pr === 2) {
            clbrTbl.fromQML_calibTableCompleted("id2")
            console.log("inside TableCalib 2")
        }
        if(pr === 3) {
            clbrTbl.fromQML_calibTableCompleted("id3")
            console.log("inside TableCalib 3")
        }
    }
}
