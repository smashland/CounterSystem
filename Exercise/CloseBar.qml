//                                                          设置窗口条
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"
Item {
    id: closebar
    width: mainWindow.width
    height: 60 *dpy
    MouseArea {
        anchors.fill: parent
        onWheel: {
            // 屏蔽滚轮事件，防止滚动方案列表时缩放地球
        }
    }
    Image {
        anchors.fill: parent
        source: "qrc:/Image/Case_bg.png"
    }
    NavImage {
        anchors.top: parent.top
        anchors.topMargin: 20 *dpy
        anchors.right: parent.right
        anchors.rightMargin: 30 *dpx
    }
}
