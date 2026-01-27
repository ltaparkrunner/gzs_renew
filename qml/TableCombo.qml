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
//                lm1.append({"designation":lc[3*i], "formula":lc[3*i+1], "proportion":lc[3*i+2]})
                lm1.append({designation:lc[3*i], formula:lc[3*i+1], proportion:lc[3*i+2]})
            }
//            lm1.append({designation:lc[0].to_string(), formula:lc[1], proportion:lc[2]})
//            lm1.append({designation:"Fresh Air", formula:"O2 + N2", proportion:"20/79"})
        }
    }
    color: "snow"
//    TableView {
    ComboBox{
        id:tv1
        anchors.fill: parent
        clip: true

        // TableViewColumn {
        //     role: "designation"
        //     title: "Designation"
        // }

        // TableViewColumn {
        //     role: "formula"
        //     title: "Formula"
        // }

        // TableViewColumn {
        //     role: "proportion"
        //     title: "Proportion"
        // }

        model: ListModel {
            id: lm1
            ListElement {
                designation: "Forever"
                formula: "Yo"
                proportion: "ung"
            }
        }
        // ListView {

        // }

        // component MyDelegate : Text{
        //     required property string designation
        //     required property string formula
        //     required property string proportion
        //     text: "designation" + " " + "formula" + " " + "proportion"
        // }
        Component {
            id: gazDelegate
            Text {
                required property string designation
                required property string formula
                required property string proportion

                    text: " Gaz: " + designation + " " + formula + proportion
                }
        }


        ListView {
            anchors.fill: parent
            model: lm1
            delegate: gazDelegate
//            delegate: MyDelegate
        }
    }
    // Text{
    //     text: "Table Combo"
    // }

    Component.onCompleted: {
        cmbTbl.fromQML_cmbTableCompleted()
    }
}

