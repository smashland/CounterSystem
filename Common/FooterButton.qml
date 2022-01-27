import QtQuick 2.0
import QtQuick.Controls 2.15

Button {
    id: footerButton
    width: 405*dpx
    height: 100*dpy
    checkable:true
    background:Rectangle{
        anchors.fill: parent
        color:"transparent"
        Image {
            anchors.bottom: parent.bottom
            source: footerButton.checked ?"qrc:/Image/Nav_selected.png":""
        }
    }
    contentItem: Text {
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: footerButton.text
        font.pixelSize: 24*dpx
        color: "#b0e9ff"
        font.family: "Microsoft YaHei"
    }
}
