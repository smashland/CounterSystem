//                                                          设置窗口条展开
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"
Item {
    id: killExpand
    width: 1040*dpx
    height: 50 *dpy
    Image {
        anchors.fill: parent
        source: "qrc:/Image/Killing_unfold.png"
    }
    Text {
        x: 10*dpx
        width: 50 *dpx
        height: 50*dpy
        text: qsTr("\ue705")
        color: "#ffb128"
        font.family: "iconfont"
        font.pixelSize: 22*dpx
        verticalAlignment: Text.AlignVCenter
    }



}
