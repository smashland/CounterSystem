//                                         删除
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"


Rectangle
{
    id:scenarioRemove
    width: 458 *dpx
    height: 308 *dpy
    x:(parent.width-width)/2
    y:(parent.height-height)/2
    focus: true
    visible: true
    color: "transparent"
    Image {
        id: name
        anchors.fill: parent
        source: "qrc:/Image/Popup_bg_24.png"
    }
    PopupTitle {
        name: ("删除")
    }
    TransverseLine {
        x: 80 *dpx
        y: 95*dpy
    }
    CloseButton {
        anchors.right: scenarioRemove.right
        anchors.rightMargin: 60 *dpx
        anchors.top: scenarioRemove.top
        anchors.topMargin: 60 *dpy
        onClicked: scenarioRemove.visible = false
    }

    Row {
        x: (438*dpx-shanchuText.contentWidth)/2
        y: 126 *dpy
        spacing: 14 *dpx
        Text {
            width: 44
            height: 44
            text: qsTr("\ue65C")
            color: "yellow"
            font.family: "iconfont"
            font.pixelSize: 44*dpx
            verticalAlignment: Text.AlignVCenter
        }
        Column {
            spacing: 5
            Text {
                id: shanchuText
                text: qsTr("此操作将永久删除该方案，")
                color: "#ffffff"
                font.pixelSize: 16
                font.family: "Microsoft YaHei"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                text: qsTr("确定删除吗？")
                color: "#ffffff"
                font.pixelSize: 14
                font.family: "Microsoft YaHei"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
    Row {
        spacing: 15 *dpx
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 60 *dpy
        x: 133*dpx
        PopupButton {
            background: Rectangle {
                color: "#265aef"
            }

            nameButton: "确定"

        }
        PopupButton {
            background: Rectangle {
                color: "#1d4f88"
            }
            nameButton: "取消"
        }
    }


}

