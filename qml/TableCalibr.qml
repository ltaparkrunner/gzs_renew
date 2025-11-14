import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0
import QtQuick.Layouts 1.0

Rectangle {
    anchors.fill: parent
    Connections{
        target: clbrTbl
//        onToQML_clbrTbl:
        function onToQML_clbrTbl2(lc, n)
        {
            var i
            var imax = lc.length/7
//            console.log("imax: ", imax)
            if (n !== tabln) return;
            tm1.clear()
            for(i = 0; i<imax; i++){
                tm1.appendRow({"num":i+1, "percent1":Number(lc[7*i]), "mlm1":lc[7*i+1],
                                        "percent2":Number(lc[7*i+2]), "mlm2":lc[7*i+3],
                                        "percent3":Number(lc[7*i+4]), "mlm3":lc[7*i+5],
                                "coeff": lc[7*i+6]})
//                console.log("from inside QML onToQML_clbrTbl")
            }
        }
    }
    color: "floralwhite"
    TableModel{
        id: tm1
        TableModelColumn { display: "num"}
        TableModelColumn { display: "percent1"}
        TableModelColumn { display: "mlm1"}
        TableModelColumn { display: "percent2"}
        TableModelColumn { display: "mlm2"}
        TableModelColumn { display: "percent3"}
        TableModelColumn { display: "mlm3"}
        TableModelColumn { display: "coeff"}
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
        id: calibr
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: header.bottom
        clip: true

        model: tm1
        delegate: DelegateChooser {
            DelegateChoice {
                delegate: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 30
                    border.width: 1
                    TextField {
                        text: display
                        anchors.fill:parent
                        //anchors.centerIn: parent
                        onEditingFinished: {
//                          console.log("clbrTbl onEditingFinished tabn: ", tabn, "  row: ", row, "  column: ", column)
                            clbrTbl.fromQML_calibTableManualEditingFinished(tabn, row, column)
                        }
                    }
                }
            }
        }
    }
/*
    HorizontalHeaderView {
        id: header_top
        anchors.left: calibr.left
        anchors.right: calibr.right
        anchors.top: parent.top//topheader.bottom
        syncView: header
        clip: true

        model: [ " № ",
            "%2", "мл/мин2",
            "%2", "мл/мин2",
            "%2", "мл/мин2",
            "коэффициент2"]
    }
*/
    HorizontalHeaderView {
        id: header
        anchors.left: calibr.left
        anchors.right: calibr.right
        anchors.top: parent.top//topheader.bottom
        syncView: calibr
        clip: true

        TableModel{
            id: hhv
            TableModelColumn { display: " "}
            TableModelColumn { display: "%"}
            TableModelColumn { display: "мл/мин"}
            TableModelColumn { display: "%"}
            TableModelColumn { display: "мл/мин"}
            TableModelColumn { display: "%"}
            TableModelColumn { display: "мл/мин"}
            TableModelColumn { display: "коеффициент"}
        }
/*
        model: [ "  ",
            "%", "мл/мин",
            "%", "мл/мин",
            "%", "мл/мин",
            "коэффициент"]
*/
/*
        model: [ "№",
            "Заданный расход %", "Заданный расход мл/мин",
            "percent2", "mlm2",
            "percent3", "mlm3",
            "coeff"]
*/
        model: hhv
            delegate: DelegateChooser {
                DelegateChoice {
                    column:1
                    delegate: Item {
                        width: 0    //100
                        implicitHeight: 80
                            TextField {
                                text: "hello world"
                                anchors.fill:parent
                            }
                    }
                }
                DelegateChoice {
                    delegate: Item {
                        implicitWidth: 100
                        implicitHeight: 80
//                        border.width: 0
//                        border.width: 1
                        // ColumnLayout{
                        //     anchors.fill: parent
                        // Rectangle{
                        //     Layout.fillHeight: true
                        //     Layout.fillWidth: true
                            TextField {

//                                padding: 0
                                // Layout.fillHeight: true
                                // Layout.fillWidth: true
                                text: (column === 2) ? "forever" : "never"
                                anchors.fill:parent
                                //anchors.centerIn: parent
         //                      onEditingFinished: {
         //                          clbrTbl.fromQML_calibTableManualEditingFinished(tabn, row, column)
         //                     }
                            }
//                        }

                        // Rectangle{
                        //     Layout.fillHeight: true
                        //     Layout.fillWidth: true
                            // TextField {
                            //     padding: 0
                            //     Layout.fillHeight: true
                            //     Layout.fillWidth: true
                            //     text: (column === 2) ? "forever" : "never"
//                                anchors.fill:parent
                                //anchors.centerIn: parent
         //                      onEditingFinished: {
         //                          clbrTbl.fromQML_calibTableManualEditingFinished(tabn, row, column)
         //                     }
//                            }
//                        }

//                        }
                    }
                }

        }
    }


    Component.onCompleted: {
        clbrTbl.fromQML_calibTableCompleted(tabln)
//        console.log("inside TableCalib")
    }
    function getValue(num){
        var n = Number(num) - 1
//        tm1.getRow()
        var row = tm1.getRow(n)
        return row.mlm1
    }
}
