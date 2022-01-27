import QtQuick 2.0
import QtQuick.Controls 2.15

Button{
    id: popupButton
    width: 88*dpx
    height: 36 *dpy
    property color buttonTrue: "#265aef"
    property color buttonFalse: "#1d4f88"
    property alias nameButton: popupText.text


    Text {
        id: popupText
        height: 36 *dpy
        width: 88*dpx
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
//        text: ""
        font.pixelSize: 16*dpx
        color: "#ffffff"
        font.family: "Microsoft YaHei"
    }
}






