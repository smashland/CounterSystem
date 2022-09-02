import QtQuick 2.12
import QtQuick.Controls 2.15
import Qt.labs.platform 1.1

Grid {
    columns: 3
    spacing: 3
    Repeater
    {
        model: 9
        Column {
            spacing: 3
            Rectangle {
                width: 230
                height: 145
                border.color: "white"
                color: "transparent"
                Image {
                    anchors.fill: parent
                    source: fileDialog.fileUrl
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        fileDialog.visible = true
                    }
                }
            }
            Rectangle {
                width: 230
                height: 20
                border.color: "white"
                color: "transparent"
                TextInput {
                    anchors.fill: parent
                    font.pixelSize: 14*dpx
                    color: "#d5e2f5"
                    clip: true
                    text: "地图" + index
                    selectByMouse: true
                    selectionColor: "#00aefd"
                    font.family: "Microsoft YaHei"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                }
            }
        }
    }
    FileDialog {
        id: fileDialog
        folder: shortcuts.home
        onAccepted: {
            source: fileDialog.fileUrl
        }
        onRejected: {
            //                    console.log("Canceled")
        }
        Component.onCompleted: visible = flase
    }

}

