//                                         选择方案修改方式
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"

Rectangle
{
    id:playbackRefresh
    width: 430 *dpx
    height: 178 *dpy
    x:(parent.width-width)/2
    y:(parent.height-height)/2
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
        y: (playbackRefresh.height - 36 *dpy)/2
        spacing: 10 *dpx
        Text {
            width: 34
            height: 34
            text: qsTr("\ue8ad")
            color: "red"
            font.family: "iconfont"
            font.pixelSize: 34*dpx
            verticalAlignment: Text.AlignVCenter
        }
        Text {
            id: wintext
            height: 36 *dpy
            text: qsTr("刷新成功，3S后弹窗自动消失")
            font.pixelSize: 18*dpx;
            color: "#e74b4b";
            font.family: "Microsoft YaHei";
            verticalAlignment: Text.AlignVCenter
        }
    }


}


