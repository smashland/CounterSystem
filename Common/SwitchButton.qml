import QtQuick 2.0
import QtQuick.Controls 2.15

Button {
    id: switchButton
    width: 190*dpx
    height: 100*dpy
    checkable:true
    background:Rectangle{
        anchors.fill: parent
        color:"transparent"
        Image {
            anchors.bottom: parent.bottom
            source: switchButton.checked ?"qrc:/Image/Popup_selected.png":""
        }
    }
    contentItem: Text {
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: switchButton.text
        font.pixelSize: 24*dpx
        color: "#ffffff"
        font.family: "Microsoft YaHei"
    }
}
