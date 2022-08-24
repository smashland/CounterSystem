import QtQuick 2.15
import QtQuick.Controls 2.15

MenuItem {
    property alias name: itemText.text
    implicitWidth: 50*dpx
    implicitHeight: 30*dpy
    background: Rectangle {
        color:"#1d4f88"
        border.color: "#d5e2f5"
        width: 50*dpx
        height: 30*dpy
        Text {
            id:itemText
            anchors.centerIn: parent
            color: "#d5e2f5"
            font.family: "Microsoft YaHei"
            font.pixelSize: 15*dpx
        }
    }
}
