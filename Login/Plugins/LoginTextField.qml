import QtQuick 2.15
import QtQuick.Controls 2.15
TextField {
    anchors.fill: parent
    color: Qt.rgba(255/255, 255/255, 255/255, 0.8);
    font.pixelSize: 16*dpx
    font.family: "Microsoft YaHei"
    clip: true
    verticalAlignment: Text.AlignVCenter
    leftPadding:  52*dpx
//    readOnly:true
    activeFocusOnPress:true
    background: Rectangle {
        color: "transparent"
    }
}
