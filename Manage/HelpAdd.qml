import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import MyItem 1.0
import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.1
import Qt.labs.qmlmodels 1.0
import "../Common"
import "../Exercise"
import "Plugins"

Rectangle {
    id: helpAdd
    width: 450 *dpx
    height: 370 *dpy
    color: "transparent"
    PopupButton {
        anchors.bottom: parent.bottom
        x: 181*dpx
        background: Rectangle {
            color: "#265aef"
        }
        nameButton: "添加"
        onClicked: {
            fileDialog.open()
        }
    }
    FileDialog {
        id: fileDialog
        folder: shortcuts.home
        title: qsTr("请选择文件")
        nameFilters: [qsTr("帮助文件 (*.chm)"),qsTr("word文件 (*.doc)"),qsTr("word文件 (*.docx)"),qsTr("视频文件 (*.mp4)"),qsTr("视频文件 (*.mkv)"),  qsTr("全部文件 (*.*)")]
        currentFile: document.source
        onAccepted: {
            $app.copyFile(currentFile.toString().replace("file:///", ""));
            listView.model = $app.openHelp()
        }

    }

    MapHelpList{
        id: listView
        width: 450 *dpx
        height: 330 *dpy
        model:$app.openHelp()
        delegate: DelegateRectangle {
            id: wrapper
            height: 38 *dpy

            TextListItem {
                id: fileName
                text: modelData
                anchors.centerIn: parent
                font.pixelSize: 14*dpx
            }
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    console.log("帮助说明"+modelData);
                    mouse.accepted = true
                    wrapper.ListView.view.currentIndex = index
                    $app.openFile(modelData)
                }
            }
            ViewButton {
                width: 22*dpx
                height: 22*dpx
                color: viewColor_shanchu
                anchors.right: parent.right
                anchors.rightMargin: 10*dpx
                y: 8 *dpy
                Text {
                    id:textIcon
                    color: "#ffffff"
                    font.family: "iconfont"
                    font.pixelSize: 16*dpx
                    anchors.centerIn: parent
                    width: textIcon.contentWidth
                    height: textIcon.contentHeight
                    text: "\ue61c"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                       $app.removeHelpFile(modelData)
                       listView.model = $app.openHelp()
                    }
                }
            }
        }

    }

}
