import QtQuick 2.0
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0
import QtQml.Models 2.15


Rectangle {
    width: 120
    height:50
    Connections{
        target: cmbTbl
//        onToQML_cmbTbl:
        function onToQML_cmbTbl(lc)
        {
            var i
            var imax = lc.length/3
            console.log("imax: ", imax)
            console.log("onToQML_cmbTbl imax: ", imax)
            for(i = 0; i<imax; i++){
                lm1.append({designation:lc[3*i], formula:lc[3*i+1], proportion:lc[3*i+2]})
            }
//            ci1.text = lm1.get(0).designation + " " + lm1.get(0).formula + " " + lm1.get(0).proportion
        }
    }
    color: "snow"
    ComboBox{
        id:cmbb1
//        anchors.fill: parent
        width: 300
        clip: true
        currentIndex: 0

        model: ListModel {
            id: lm1
            ListElement { designation: "Synthentic air : 1.00"
                            formula: "10"
                            proportion: "98"}
        }
        textRole: {"designation"; "formula"; "proportion"}

        delegate: ItemDelegate {
            width: cmbb1.width
            background: Rectangle {
                color: "lightblue"
            }
            contentItem: Text {
                text: model.designation + " " + model.formula + " " + model.proportion
                font.pointSize: 12
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        contentItem: Text {
            id: ci1
            text: lm1.get(cmbb1.currentIndex).designation + " " + lm1.get(cmbb1.currentIndex).formula + " " + lm1.get(cmbb1.currentIndex).proportion //: " "
            font.pointSize: 11
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        onCurrentIndexChanged: console.log("ComboBox onCurrentIndexChanged: ", lm1.get(cmbb1.currentIndex).designation)
    }

    Component.onCompleted: {
        cmbTbl.fromQML_cmbTableCompleted()
    }
}

