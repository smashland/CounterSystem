import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    y: 115*dpy
    anchors.right: parent.right
    anchors.rightMargin: 80*dpx
    width:  380*dpx
    height:  34*dpy
    color: "#082e5c"
    radius: 2
    border.color: "#32b8ff"

    TextInput {
        id: scenarioTextInput
        width: 380*dpx
        x: 20*dpx
        height: 34*dpy
        color: "#dcecff"
        activeFocusOnPress: true
        clip: true
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 14*dpx
    }

    Button {
        id: search
        y: 2 *dpy
        anchors.right: parent.right
        anchors.rightMargin: 10*dpx
        width:   24*dpy
        height:  24*dpy
        Text {
            id: iconText
            width: 24*dpx
            height: 24*dpx
            text: qsTr("\ue6f3")
            color: "#ffffff"
            font.family: "iconfont"
            font.pixelSize: 22*dpx
            verticalAlignment: Text.AlignVCenter
        }
        background: Rectangle {
            color: "transparent"
        }
    }

}
