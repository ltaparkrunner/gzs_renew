import QtQuick 2.15
import QtQuick.Layouts 1.0
import QtCharts 2.0

import QtQuick.Controls 2.15     //2.3     //1.0//
import QtQuick.Dialogs 1.2

ApplicationWindow{
    id: main1
    width: 1050
    height: 750
    visible: true
    title : "Обмен с устройствои"

    readonly property int menuh: 35
    readonly property int spch: 10

    Connections {
        target: master // Указываем целевое соединение

//        onToQML_comList:
        function onToQML_comList(lc)
        {
            mn1.removeItem(mni_1)
            for(var i = 0; i < lc.length; i++){
                let nmni = mn1.addItem(lc[0])
                let nmn13 = Qt.createQmlObject("
                    import QtQuick 2.15
                    import QtQuick.Controls 2.15

                    MenuItem {
                        text: qsTr(\"Dynamic Item\")
                        onTriggered: {
                                console.log(\"Dynamic Item Triggered\")
                                master.eqpRqst_fromQML(text)
                        }
                    }
                    ",
                    mn1
                    )
                nmn13.text = lc[i]
                mn1.addItem(nmn13)
            }
        }
//        function onOpenFileSucc(text, title){

//            messageDialog2.text = text
//            messageDialog2.open()
//        }
    }
    Component {
        id: dynI
        MenuItem{
            text: "Dynamic Item"
            onTriggered: console.log("Dynamic Item Triggered")
        }
    }
    menuBar:
       MenuBar{
        id:menuB

        Menu {
            title: {qsTr("Файл")}
            MenuItem {
                text: "Загрузить конфигурацию"
                onTriggered: openFileDialog.open();
            }
            MenuItem {
                text: "Сохранить конфигурацию"
                onTriggered: saveFileDialog.open();
            }
//            MenuItem {
//                text: qsTr("Открыть файл")
//                onTriggered: master.openefile_fromQML("");
//            }
//            MenuItem {
//                text: qsTr("Установить соединение со станцией")
//                onTriggered: master.startTest_fromQML();
//            }
//            MenuItem {
//                text: qsTr("Остановить тест")
//                onTriggered: master.stopTest_fromQML();
//            }
            MenuSeparator{}
            MenuItem {
                text: qsTr("Выход")
                onTriggered: Qt.quit();
            }
        }
        Menu {
            title: {qsTr("Соединение")}
            Menu {
                id: mn1
                title: "Установка"
                MenuItem {
                    id: mni_1
                    text: "Нет доступных COM портов"
//                    onTriggered:
                }
//                function addDynamicItem(){
//                    let nmni2 = dynI.createObject(mn1)
//                    mn1.addItem(nmni2)
//                }
            }
        }
        Menu {
            id: about
            title: qsTr("О программе")
            MenuItem {
                id: aboutItem
                checkable: true
//                highlighted: true
//                iconName: my1
//                iconSource: ""
//                text: qsTr("О программе")

                text: "О программе"
                onTriggered: aboutDialog.open();
            }
        }
    }
//    Binding {
//        target: MyCppObject
//        property: "myText"
//        value: myLabel.text
//    }
//    Label{
//        id: myLabel
//        text: "myCppObject.myText: " + MyCppObject.myText
//        anchors.centerIn: parent
//    }

    Gview2{
        anchors.fill: parent
    }

//    ColumnLayout{
//        spacing: spch
//        anchors.fill: parent
//    }
//    TextWindow{
//        id:tw
//        anchors.leftMargin: 10
//    }

    MessageDialog{
        id: aboutDialog
        title: qsTr("О программе \"Chart Window\"")
        text: qsTr( "\"Chart Window\" \n \
        (c) ОАО \"Авангард\"\n \
   Санкт-Петербург, Кондратьевский пр., д.72,\n\
                   \n\
      Разработчики: \n\
        Игнатьев В.С. \n\
        Мордвинцев А.Л.")
    }

    FileDialog {
        id: openFileDialog
        title: "Please choose a file"
        onAccepted: {
            console.log("You chose: " + openFileDialog.fileUrls)
            master.openefile_fromQML(openFileDialog.fileUrls)
        }
        onRejected: {
            console.log("Canceled")
//            master.startf_fromQML()
        }
    }
/*
    FileDialog {
        id: saveFileDialog
        title: "Please choose a file"
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
            master.openefile_fromQML(fileDialog.fileUrls)
        }
        onRejected: {
            console.log("Canceled")
//            master.startf_fromQML()
        }
    }
*/
}
