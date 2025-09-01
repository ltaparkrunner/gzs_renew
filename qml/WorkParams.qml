import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
import QtQuick.Controls 2.5
import QtQuick.Window 2.0   //1.5//2.15
//import Qt.labs.qmlmodels 2.5

Rectangle{
    id:wp
    color:"lightyellow"
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
                    }
                    Button {
                        id: b2
                        text: qsTr("Стоп")
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
                }
                Text {
                    id: t312
                    text: qsTr("Целевой газ")
                }
                ComboBox {
                //            text: "Выберите COM порт:"
                            currentIndex: 0
                            model: ListModel {
                                id: cbItems
                                ListElement { text: "Synthentic air : 1.00" }
                                ListElement { text: "Nytrogen : 0.30" }
                            }
                            width: 200
                            onCurrentIndexChanged: console.log(cbItems.get(currentIndex).text)
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
                            if (newWindow) {
                                newWindow.show();
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

        Rectangle{
            color: "red"
//            implicitHeight: ts.height
//            implicitHeight: 100
//            Layout.fillHeight: true
            Layout.fillWidth: true

            TableSimple{
                id:ts
            }
        }
    }
}
