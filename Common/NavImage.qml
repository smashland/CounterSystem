//                                     顶部条
import QtQuick 2.12
import QtGraphicalEffects 1.15

Row {
    spacing: 20 *dpx
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
        id: zuidahua
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
                id: mousearea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    maxHint.visible = true
                }
                onExited: {
                    maxHint.visible = false
                }
                onClicked: {
                    zuidahuaFun()
                }
            }
        }
        Hint
        {
            id:maxHint
            hintX: maxIcon.x
            hintY: maxIcon.y+maxIcon.contentHeight+10
            title: "还原"
            visible: false
        }
    }
    Rectangle {
        id: huanyuan
        width: 18 *dpx
        height: 18 *dpx
        color: "transparent"
        visible: false
        Text {
            id:huanyuanIcon
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
                    huanyuanHint.visible = true
                }
                onExited: {
                    huanyuanHint.visible = false
                }

                onClicked: {
                    huanyuanFun()
                }
            }
        }
        Hint
        {
            id:huanyuanHint
            hintX: maxIcon.x
            hintY: maxIcon.y+maxIcon.contentHeight+10
            title: "最大化"
            visible: false
        }
    }
    function zuidahuaFun()
    {
        zuidahua.visible = false
        huanyuan.visible = true
        resizeItem.visible = true
    }
    function huanyuanFun()
    {
        zuidahua.visible = true
        huanyuan.visible = false
        resizeItem.visible = false
        mainWindow.showFullScreen()
//        mainWindow.width = sWidth
//        mainWindow.height = sHeight
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
//                $app.exitApp();
//                Qt.quit()
                removeDialog_quit.visible = true
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
