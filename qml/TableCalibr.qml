import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0

Rectangle {
    anchors.fill: parent
    Connections{
        target: clbrTbl
//        onToQML_clbrTbl:
        function onToQML_clbrTbl2(lc, n)
        {
            var i
            var imax = lc.length/3
            console.log("imax: ", imax)
            if (n !== tabln) return;
            for(i = 0; i<imax; i++){
                tm1.appendRow({"num":i+1, "percent1":Number(lc[3*i])/2, "mlm1":lc[3*i],
                                        "percent2":Number(lc[3*i+1])/2, "mlm2":lc[3*i+1],
                                        "percent3":Number(lc[3*i+2])/2, "mlm3":lc[3*i+2],
                                "coeff": 0})
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
        id: header
        anchors.left: calibr.left
        anchors.right: calibr.right
        anchors.top: parent.top//topheader.bottom
        syncView: calibr
        clip: true
        model: [ "num",
            "percent1", "mlm1",
            "percent2", "mlm2",
            "percent3", "mlm3",
            "coeff"]
    }

    Component.onCompleted: {
        clbrTbl.fromQML_calibTableCompleted(tabln)
//        console.log("inside TableCalib")
    }
}
