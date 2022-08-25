import QtQuick 2.15
import QtQuick.Controls 2.15

MenuItem {
    property alias name: itemText.text
    implicitWidth: contextMenu.width
    implicitHeight: 30*dpy
    background: Rectangle {
        color:"#1d4f88"
        border.color: "#d5e2f5"
        width: contextMenu.width
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
