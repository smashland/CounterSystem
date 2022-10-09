import QtQuick 2.12
import QtQuick.Controls 2.15
import "../../Common"
import "../../Exercise"

Rectangle {
    id: backgroundItem
    color: "transparent"
    property alias rectWidth: backgroundItem.width
    property alias rectHeight: backgroundItem.height
    property alias rectImage: loginImage.source
    anchors.centerIn: parent
    MouseArea {
        anchors.fill: parent
        onWheel: {
            // 屏蔽滚轮事件，防止滚动方案列表时缩放地球
        }
    }
    Image {
        id: loginImage
        anchors.fill: parent
        //            source: "qrc:/Image/Popup_bg_20.png"
    }
}
