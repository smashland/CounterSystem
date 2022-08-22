import QtQuick 2.12
 import QtGraphicalEffects 1.15

//Item {
//    id: navImage

//}

Row {
    spacing: 20 *dpx
    Rectangle {
        width: 18 *dpx
        height: 18 *dpx
        color: "transparent"

        Image
        {
            anchors.fill: parent
            source: "qrc:/Image/code_icon.png"
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                $app.openVideo();
            }
        }
    }
    Rectangle {
        width: 18 *dpx
        height: 18 *dpx
        color: "transparent"

        Text {
            id:minIcon
            anchors.fill: parent
            text: qsTr("\ue6fc")
            color: "#e7f6ff"
            font.family: "iconfont"
            font.pixelSize: 22*dpx
            verticalAlignment: Text.AlignVCenter
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                mainWindow.showMinimized()
            }
            onEntered: {
                minHint.visible = true
            }
            onExited: {
                minHint.visible = false
            }
        }
        Hint
        {
            id:minHint
            hintX: minIcon.x
            hintY: minIcon.y+minIcon.contentHeight+10
            title: "最小化"
            visible: false
        }
    }
    Rectangle {
        width: 18 *dpx
        height: 18 *dpx
        color: "transparent"

        Text {
            id:maxIcon
            anchors.fill: parent
            text: qsTr("\ue702")
            color: "#e7f6ff"
            font.family: "iconfont"
            font.pixelSize: 22*dpx
            verticalAlignment: Text.AlignVCenter
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    maxHint.visible = true
                }
                onExited: {
                    maxHint.visible = false
                }
            }
        }
        Hint
        {
            id:maxHint
            hintX: maxIcon.x
            hintY: maxIcon.y+maxIcon.contentHeight+10
            title: "最大化"
            visible: false
        }
    }
    Rectangle {
        width: 18 *dpx
        height: 18 *dpx
        color: "transparent"

        Text {
            id: closeIcon
            anchors.fill: parent
            text: qsTr("\ue61c")
            color: "#e7f6ff"
            font.family: "iconfont"
            font.pixelSize: 22*dpx
            verticalAlignment: Text.AlignVCenter
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                $app.exitApp();
                Qt.quit()
            }
            onEntered: {
                closeHint.visible = true
            }
            onExited: {
                closeHint.visible = false
            }
        }
        Hint
        {
            id:closeHint
            hintX: closeIcon.x
            hintY: closeIcon.y+closeIcon.contentHeight+10
            title: "关闭"
            visible: false
        }
    }
}
