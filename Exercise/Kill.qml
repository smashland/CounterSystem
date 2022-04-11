//                                                          设置窗口条
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"
Item {
    id: kill
    width: 200*dpx
    height: 50 *dpy
    Image {
        anchors.fill: parent
        source: "qrc:/Image/Killing_packup.png"
    }
    Text {
        x: 15*dpx
        width: 50 *dpx
        height: 50*dpy
        text: qsTr("\ue707")
        color: "#ffb128"
        font.family: "iconfont"
        font.pixelSize: 22*dpx
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        anchors.fill: parent
        text: qsTr("击杀情况")
        color: "#ffb128"
        font.family: "MicrosoftYaHei-Bold"
        font.pixelSize: 22*dpx
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

}
