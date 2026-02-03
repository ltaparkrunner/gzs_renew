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
    property var clrAr:[]
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
                    for(j = 0; j < l; j++){
                        if((st.length + strlist[j].length) > (ml * row) && j > 0){
                            st = st + " \n" + strlist[j]
                            row++
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
                tm21.appendRow({"mnumber":lc[6*i], duration:lc[6*i+1], cncntr1:lc[6*i+2],
                               cncntr2:lc[6*i+3], "sumStream":lc[6*i+4], "humidity":lc[6*i+5]})//, "dur_cl":"lightblue"})//, "hum_cl":"lightgreen"})
//                tm21[1]["mnumber"].
            }
        }
        function onToQML_smplTbl2(ln, ls)
        {
            var i,j,l
            var imax = (ln.length-6)/11
            var st
            const ml = 12//15
            var row
            console.log("onToQML_smplTbl2 imax: ", imax, "  ln.length: ", ln.length)

            lm2.clear()

            for(i = 0; i < 6; i++) {
                if (ls[i].length > ml){
                    var strlist = ls[i].split(" ")
                    l = strlist.length
                    st = "";
                    row = 1;
                    for(j = 0; j < l; j++){
                        if((st.length + strlist[j].length) > (ml * row) && j > 0){
                            st = st + " \n" + strlist[j]
                            row++
                        }
                        else{
                            st = st + " " + strlist[j]
                        }
                    }
                    lm2.append({title1: st})
                }
                else lm2.append({title1:ls[i]})
            }

            tm21.clear()
//            var k = 0
            for(i=0; i<imax; i++){
                tm21.appendRow({"mnumber":ln[11*i+6], duration:ls[i+6], cncntr1:ln[11*i+9],
                               cncntr2:ln[11*i+11], "sumStream":ln[11*i+13], "humidity":ln[11*i+15]})//, "dur_cl":"lightblue"}) //, "hum_cl":"lightgreen"})
                clrAr.push(ln[11*i+7])
//                k=k+1

                for(j=0; j<5; j++) {
                    clrAr.push(ln[11*i+j*2+8])
//                    k = k+1
                }
            }
        }
        function onToQML_smplTbl3(num, rw, cl){
            var indx = tm21.index(rw, cl)
            tm21.setData(indx, "display", num)
        }
        function onToQML_smplTbl4(s, rw, cl){
            var indx = tm21.index(rw, cl)
            tm21.setData(indx, "display", s)
        }
        function onToQML_smplTbl5(ln, ls, row){
            console.log("onToQML_smplTbl5 : ln.length", ln.length, "  ls.length: ", ls.length, "  row: ", row)
            tm21.setRow(row, {"mnumber":ln[0], duration:ls, cncntr1:ln[1], cncntr2:ln[2], "sumStream":ln[3], "humidity":ln[4]})//, "dur_cl":"lightred"}) //, "hum_cl":"lightviolet"})
            console.log("ln.slice: ", ln.slice(5), "clrAr.length: ", clrAr.length, "clrAr:", clrAr)

//            clrAr.slice(row*6) = ln.slice(5)
            for(var i=0; i<6; i++) clrAr[row*6+i] = ln[5+i]
            console.log("clrAr:", clrAr)
        }
        function onToQML_smplTblRowColors(ln, row){
//            for(var i=0; i<6; i++) clrAr[row*6+i] = ln[i]
            console.log("onToQML_smplTblRowColors(ln, row): ", row)
            var indx = tm21.index(row, 7)
//            tm21.setData(indx, "background", "orange")
//            console.log("clrAr:", clrAr)
        }
    }
    Connections{
        target: params
    }
//    color: "ivory"
    TableModel{
        id: tm21
        TableModelColumn { display : "mnumber"}
        TableModelColumn { display: "duration"}
        TableModelColumn { display: "cncntr1"}
        TableModelColumn { display: "cncntr2"}
        TableModelColumn { display: "sumStream"}
        TableModelColumn { display: "humidity"}
        TableModelColumn { background:  "bgColor"}
//         TableModelColumn { background:  function(modelIndex){return "white"}}
        rows:[{
            mnumber : "mnumber",
            duration : "duration",
            cncntr1 : "cncntr1",
            cncntr2 : "cncntr2",
            sumStream : "sumStream",
            humidity : "humidity",
            "bgColor": "lightgreen"
        }]
    }

    TableView {
        id: smpl
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: header2.bottom
//        clip: true

        model: tm21
          delegate: DelegateChooser {
//              id:dcd
              DelegateChoice {
                  roleValue: "bgColor"
              }

              DelegateChoice {
                  column: 0
                  delegate: Rectangle {
                      implicitWidth: 100
                      implicitHeight: 30
                      border.width: 1
//                      color: "blue"
                      // ComboBox{
                      //     width:200
                      //     model:["Banana", "Apple", "Coconut"]
                      //     onCurrentIndexChanged: {
                      //         console.log("Selected item: ", currentText)
                      //     }
                      // }
                      TextField {
                          text: display
                          readOnly: true
                          anchors.fill:parent
                      }
//                    ContextMenu.menu:
                    Menu{
                        id: contextMenu
                        MenuItem{
                            text: "Cut"
                            onTriggered: {
                                console.log("Context menu Cut, row ", row)
                            }
                        }
                        MenuItem{
                            text:"Удалить строку"
                            onTriggered: {
                                console.log("Context menu Удалить строку, row ", row)
                            }
                        }
                    }

                    MouseArea{
                       anchors.fill: parent
                       acceptedButtons: Qt.LeftButton | Qt.RightButton
                       onClicked: {
                            if(mouse.button === Qt.RightButton){
                                contextMenu.x = mouse.x
                                contextMenu.y = mouse.y
                                contextMenu.popup()
                            }
                       }
                    }
                  }
              }
              DelegateChoice {
                    column: smpl.columns - 1
//                    visible: false
                    roleValue: "dur_cl"
                    delegate: Item{
                        visible: false
                        implicitWidth: 100
                        implicitHeight: 30
                    }
              }

              DelegateChoice {
                  column: smpl.columns - 2//smpl.columns - 1
                  row: smpl.rows - 1
                  delegate: Rectangle {
                      implicitWidth: 100
                      implicitHeight: 30
                      border.width: 1
                      color: "green"
                      TextField {
//                          color: activeFocusControl?"lightblue":""
                          text: display
                          // google AI regular expression for hh:mm:ss
                          //validator: RegularExpressionValidator{regularExpression: /^([0-1][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])$/}
                          anchors.fill:parent
                            background: Rectangle{
                                color:clrAr[1]===0?"white":clrAr[1]===1?"lightgreen":clrAr[1]===2?"lightblue":"yellow"
                            }

                          Keys.onReturnPressed: {
                            console.log("onToQML_smplTbl TextField Keys.onReturnPressed column 5")
                            console.log("The last row: ", smpl.rows)
                            let strbuf = [];
                            let rws = tm21.rowCount
                            let i
                            for(i=0; i<rws; i++) {
                                strbuf.push(tm21.getRow(i))
                            }

                            tm21.clear()
                            for(i=0; i<rws; i++) {
                                tm21.appendRow(strbuf[i])
                            }
                            strbuf[rws-1].mnumber = (rws+1).toString()
                            tm21.appendRow(strbuf[rws-1])
                            let lrow = [];
                            lrow.push(strbuf[rws-1].duration)
                            lrow.push(strbuf[rws-1].cncntr1)
                            lrow.push(strbuf[rws-1].cncntr2)
                            lrow.push(strbuf[rws-1].sumStream)
                            lrow.push(strbuf[rws-1].humidity)
//                            smplTbl.fromQML_smplTableRowAdded(lrow, row, column)
                            params.fromQML_smplTableRowAdded(lrow, row, column)
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
                          //validator: RegularExpressionValidator{regularExpression: /^\d+$/}
                          anchors.fill:parent
                          background: Rectangle{
                              id:bg1
//                              property var cl: clrAr[row*smpl.columns + column]
//                              color:cl===0?"white":cl===1?"lightgreen":cl===2?"lightblue":"yellow"
//                              color: background
                          }
                          Keys.onReturnPressed: {
                            console.log("onToQML_smplTbl TextField Keys.onEditingFinished duration")
                          }
                          onEditingFinished: {
                              var succ
                              let x = tm21.getRow(row)
                              switch(column){
                                case 1: x.duration = text; break;
                                case 2: x.cncntr1 = text; break;
                                case 3: x.cncntr2 = text; break;
                                case 4: x.sumStream = text; break;
                                case 5: x.humidity = text; break;
                              }
                              tm21.setRow(row, x)
                              let lrow = [];
                              lrow.push(x.duration)
                              lrow.push(x.cncntr1)
                              lrow.push(x.cncntr2)
                              lrow.push(x.sumStream)
                              lrow.push(x.humidity)
//                              smplTbl.fromQML_smplTableEditFinished(lrow, row, column)
                              params.fromQML_smplTableEditFinished(lrow, row, column)
                           }
                          onActiveFocusChanged: {
//                            console.log("TextField onFocusChanged:  row: ", row, "  column: ", column)
                              if(activeFocus) {
//                                  bg1.color="lightblue"
                                  params.fromQML_getFocus(row, column)
                              }
//                              else bg1.color="white"
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
    }
}
