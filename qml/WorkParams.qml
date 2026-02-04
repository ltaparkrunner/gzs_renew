import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0
import QtQml.Models 2.15
import QtQuick.Window 2.0   //1.5//2.15
//import Qt.labs.qmlmodels 2.5

Rectangle{
    id:wp
    color:"lightyellow"
    Connections{
        target: master
    }
    Connections {
        target: crTbl
//        function onToQML_crTbl(lf, lclr)
        function onToQML_crTbl(lf)
        {
            console.log("onToQML_crTbl lf[1]: ", lf[1])
            t38.text = lf[0]
            t39.text = lf[1]
            t310.text = lf[2]
            ti34.text = lf[3] // bln_cncntr ballon concentration
        }
    }
    Connections {
        target: sldr
        function onToQML_setPos(p){
            sd1.value = p
        }
        function onToQML_setMax(m){
            sd1.to = m
            rw1.spacing = Math.trunc(sd1.width/(m-1))-12
        }
    }

    ColumnLayout{
//        anchors.fill: parent
//        anchors.left: parent.left
//        anchors.right: parent.right
        width: parent.width
        RowLayout{
            ColumnLayout{
//                anchors.top: parent.top
                Layout.alignment: Qt.AlignTop
                Text {
                    id: t1
                    text: qsTr("Обратный отсчет")
                }
                RowLayout{
                    ColumnLayout{
                        Text {
                            id: t2
                            text: qsTr("Текущий режим :")
                        }
                        Text {
                            id: t4
                            text: qsTr("Цикл :")
                        }

                    }
                    ColumnLayout{
                        Text {
                            id: t3
                            text: qsTr("0:00:30")
                        }
                        Text {
                            id: t5
                            text: qsTr("0:00:30")
                        }
                    }


                }
                CheckBox{
                    text: "Циклическая работа"
                }
                RowLayout{
                    Button {
                        id: b1
                        text: qsTr("Старт")
                        onClicked: master.fromQML_btnStart()
                    }
                    Button {
                        id: b2
                        text: qsTr("Стоп")
                        onClicked: master.fromQML_btnStop()
                    }
                }
            }
            ColumnLayout{
//                anchors.top: parent.top
                Layout.alignment: Qt.AlignTop
                Text {
                    id: t21
                    text: qsTr("Расход [мл/мин]")
                }
                RowLayout{
                    ColumnLayout{
                        Text {
                            id: t22
                            text: qsTr("Сухая смесь :")
                        }
                        Text {
                            id: t23
                            text: qsTr("Целевой газ")
                        }
                        Text {
                            id: t24
                            text: qsTr("Газ разбавитель")
                        }
                        Text {
                            id: t25
                            text: qsTr("Влажная смесь")
                        }
                        Text {
                            id: t26
                            text: qsTr("Поправочный коэффициент")
                        }

                    }
                    ColumnLayout{
                        Text {
                            id: t6
                            text: qsTr("")
                        }
                        Text {
                            id: t7
                            text: qsTr("0.000")
                        }
                        Text {
                            id: t8
                            text: qsTr("0.000")
                        }
                        Text {
                            id: t9
                            text: qsTr("200.000")
                        }
                        Text {
                            id: t10
                            text: qsTr("1.000")
                        }
                    }
                }
            }
            ColumnLayout{
//                anchors.top: parent.top
                Layout.alignment: Qt.AlignTop
                Text {
                    id: t31
                    text: qsTr("Максимальный расход по каналам [мл/мин]")
                }
                RowLayout{
                    ColumnLayout{
                        Text {
                            id: t32
                            text: qsTr("Сухая смесь :")
                        }
                        Text {
                            id: t33
                            text: qsTr("Целевой газ")
                        }
                        Text {
                            id: t34
                            text: qsTr("Газ разбавитель")
                        }
                        Text {
                            id: t35
                            text: qsTr("Влажная смесь")
                        }
                        Text {
                            id: t36
                            text: qsTr("Поправочный коэффициент")
                        }

                    }
                    ColumnLayout{
                        Text {
                            id: t37
                            text: qsTr("")
                        }
                        Text {
                            id: t38
                            text: qsTr("0.000")
                        }
                        Text {
                            id: t39
                            text: qsTr("0.000")
                        }
                        Text {
                            id: t310
                            text: qsTr("200.000")
                        }
                        Text {
                            id: t311
                            text: qsTr("1.000")
                        }
                    }
                    Component.onCompleted: {
                        crTbl.fromQML_crCompleted()
                    }
                }
                Text {
                    id: t312
                    text: qsTr("Целевой газ")
                }
                TableCombo{
                    id:tc32
                }
                Text {
                    id: t313
                    text: qsTr("Концентрация в баллоне[%]")
                }
                Rectangle{
                    color: "lightgreen"
                    implicitHeight: ti34.height
                    implicitWidth:  ti34.width
                    TextInput {
                        id: ti34
    //                    padding: 4.3
                        color: "red"
                        text: "100"
                    }
                }
            }
            ColumnLayout{
//                anchors.top: parent.top
                Layout.alignment: Qt.AlignTop
                Text {
                    id: t41
                    text: qsTr("Коэффициент регуляторов")
                }
                Button {
                    id: b41
                    text: qsTr("Калибровка")
                    onClicked: {
                        var component = Qt.createComponent("CalibrMaster.qml");
                        if (component.status === Component.Ready) {
                            var newWindow = component.createObject(wp); // 'root' is the parent for the new object
//                            newWindow = component.createObject(wp); // 'root' is the parent for the new object
                            if (newWindow) {
                                newWindow.show();
                                master.calibOpened_fromQML()
                            } else {
                                console.error("Failed to create new window object.");
                            }
                        } else {
                            console.error("Failed to load ChildWindow.qml:", component.errorString());
                        }
                    }
                }
                Text {
                    id: t42
                    text: qsTr("ЦЕЛЕВОЙ ГАЗ")
                }
                Rectangle{
                    color: "lightgreen"
                    implicitHeight: ti34.height
                    implicitWidth:  ti34.width
                    TextInput {
                        id: ti43
    //                    padding: 4.3
                        color: "red"
                        text: "???"
                    }
                }
                Text {
                    id: t44
                    text: qsTr("СУХОЙ РАЗБАВИТЕЛЬ")
                }
                Rectangle{
                    color: "lightgreen"
                    implicitHeight: ti34.height
                    implicitWidth:  ti34.width
                    TextInput {
                        id: ti45
    //                    padding: 4.3
                        color: "red"
                        text: "???"
                    }
                }
                Text {
                    id: t46
                    text: qsTr("ВЛАЖНЫЙ РАЗБАВИТЕЛЬ")
                }
                Rectangle{
                    color: "lightgreen"
                    implicitHeight: ti34.height
                    implicitWidth:  ti34.width
                    TextInput {
                        id: ti47
    //                    padding: 4.3
                        color: "red"
                        text: "???"
                    }
                }
            }
        }
        Text{
            text: "forever2"
        }
        // Repeater to create the labels

        Row{
            id: rw1
            spacing: 1//{(Math.trunc(sd1.width/(sd1.from-sd1.to))-12) }       //330
            Repeater{
                model: sd1.stepSize > 0 ? 1+(sd1.to - sd1.from)/sd1.stepSize : 0
                delegate: Text{
                    property real labelValue:sd1.from + index * sd1.stepSize
                    text: labelValue.toFixed()

                    font.pixelSize: 12
                    color: "black"
                    // the label's position
    //                anchors.top: sd1.bottom
    //                anchors.topMargin: 5
                    Layout.topMargin: 5
                }
            }
        }

        // qtquickcontrols-customize
        Slider{
            id:sd1
            Layout.fillWidth: true
            from: 1
            to: 2
            value:1
            stepSize: 1
            handle: Rectangle {
                x: sd1.leftPadding + sd1.visualPosition * (sd1.availableWidth - width)
                y: sd1.topPadding + sd1.availableHeight / 2 - height / 2
                implicitWidth: 13
                implicitHeight: 13
                radius: 6

                color: sd1.pressed ? "#f0f0f0" : "#f6f6f6"
                border.color: "#bdbebf"
            }

            orientation: Qt.Horizontal
            onValueChanged: {
//                console.log("Slider new value:", value)
                params.fromQML_sliderPosChanged(value)
            }
            Component.onCompleted: {
                sldr.fromQML_sldrCompleted()
            }
        }

        Rectangle{
            color: "red"
//            implicitHeight: ts.height
//            implicitHeight: 100
//            Layout.fillHeight: true
            Layout.fillWidth: true

            TableSimple{
                id:ts
            }
            // Simple_background{
            //     id:ts
            // }
        }
    }
}
