//                                         选择方案修改方式
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"

Rectangle
{
    id:scePopup
    property alias text: wintext.text
    width: 430 *dpx
    height: 178 *dpy
    focus: true
    visible: true
    color: "transparent"
    Image {
        id: name
        anchors.fill: parent
        source: "qrc:/Image/Message_box.png"
    }
    Row {
        x: 25 *dpx
        y: (scePopup.height - 36 *dpy)/2
        spacing: 10 *dpx
        Text {
            width: 34
            height: 34
            text: qsTr("\ue65c")
            color: "#e74b4b"
            font.family: "iconfont"
            font.pixelSize: 34*dpx
            verticalAlignment: Text.AlignVCenter
        }
        Text {
            id: wintext
            height: 36 *dpy
//            text: qsTr("刷新成功，3S后弹窗自动消失")
            font.pixelSize: 18*dpx;
            color: "red";
            font.family: "Microsoft YaHei"
            font.bold: true
            verticalAlignment: Text.AlignVCenter
        }
    }

}


