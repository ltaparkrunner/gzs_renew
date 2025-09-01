//import QtQuick.Controls.Windows
//import QtQuick.Controls.Material

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
//import QtQuick.Controls 1.0
import QtQuick.Controls //2.0     //1.0//2.0
import QtQuick.Dialogs //2.0     //1.2

ApplicationWindow{
    readonly property font myTitleFont: ({
            family: "Helvetica",
            pixelSize: 25,
            bold: false//true
        })
    id: main1
    width: 1260
    height: 940
    visible: true
    title : "Обмен с устройствои"

    readonly property int menuh: 35
    readonly property int spch: 10
    readonly property font myFontMenu: ({
            family: "Helvetica",
            pixelSize: 17,
        })
    // Connections {
    //         target: vmConfigsChat // Указываем целевое соединение
    //     function onOpenFileSucc(text, title){
    //         messageDialog2.text = text
    //         messageDialog2.open()
    //     }
    // }

    menuBar:
       MenuBar{
        font: myFontMenu
          contentHeight: 30
        Menu {
            title: {qsTr("Файл")}
            font: parent.font
            height: menuh * 3 + 14
            MenuItem {
                text: qsTr("Открыть файл")
                font: myFontMenu
                onTriggered: fileDialog.open();
                height: menuh
            }
            MenuItem {
                text: qsTr("Разъединить")
                font: myFontMenu
                onTriggered: Qt.quit();
                height: menuh
            }
            MenuSeparator{}
            MenuItem {
                text: qsTr("Выход")
                font: myFontMenu
                onTriggered: Qt.quit();
                height: menuh
            }
        }

        Menu {
            title: qsTr("О программе")
            height: menuh + 2
            MenuItem {
                text: qsTr("О программе")
                font: myFontMenu
                onTriggered: aboutDialog.open();
                height: menuh
            }
        }
    }

    ColumnLayout{
        spacing: spch
        anchors.fill: parent
        // Rectangle {
        //     Layout.alignment: Qt.AlignCenter
        //     color: "white"
        //     Layout.fillWidth: true
        //     Layout.fillHeight: true
        //     RowLayout{
        //         spacing: 2
        //         anchors.fill: parent

        //         ChatW{
        //             Layout.fillWidth: true
        //             Layout.fillHeight: true
        //         }

        //         ControlP{
        //             Layout.fillHeight: true
        //         }
        //     }
        // }
        // CondLine{
        //     id: bott1
        //     Layout.fillWidth: true
        // }
    }
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
        id: fileDialog
        title: "Please choose a file"
//        folder: "~/wrk/myproj" //shortcuts.home
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
//            Qt.quit()
        }
        onRejected: {
            console.log("Canceled")
//            Qt.quit()
        }
//        Component.onCompleted: visible = true
    }
}
