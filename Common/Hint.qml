//                                  按钮提示信息
import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: hint
    property alias hintX: hint.x
    property alias hintY: hint.y
    property alias title: hintText.text

    width: 45*dpx
    height: 20*dpy
    visible:false
//    border.width: 1
//    border.color: "black"
    color:"white"
    Text{
        id:hintText
        anchors.centerIn: parent
        font.pixelSize: 12*dpx
    }
}
