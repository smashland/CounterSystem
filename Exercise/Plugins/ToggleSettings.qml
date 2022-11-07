//                                               切换设置
import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: switchSet
    width: 140*dpx
    height: 68 *dpy
    color: Qt.rgba(36/255, 41/255, 57/255, 0.6);
    radius: 20*dpy

    Rectangle {
        x: 10*dpx
        y: 7*dpy
        color: "transparent"
        width: 20*dpx
        height: 20*dpx

        Text {
            anchors.fill: parent
            text: qsTr("\ue628")
            color: "#e7f6ff"
            font.family: "iconfont"
            font.pixelSize: 22*dpx
            verticalAlignment: Text.AlignVCenter
        }
    }
    Rectangle {
         y: 7*dpy
        x: 35*dpx
        color: "transparent"
        Text {
            text: qsTr("切换设置")
            font.pixelSize: 16*dpx;
            color: "#ffffff";
            font.family: "Microsoft YaHei"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            manoeuvre.visible = false
            footerBar.visible = true
        }
    }
}
