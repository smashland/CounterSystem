import QtQuick 2.15

Rectangle
{
    width:100
    height: 100
    radius: width/2
    x: (parent.width-width)/2
    gradient: Gradient
    {
        GradientStop
        {
            position: 0.04;
            color: "transparent";
        }
        GradientStop
        {
            position: 1.00;
            color: "#59eba5";
        }
    }
    Column{
        spacing: 5
        anchors.centerIn: parent
        Text {
            width: zantingText.contentWidth
            text: qsTr("\ue638")
            color: "#e7f6ff"
            font.family: "iconfont"
            font.pixelSize: 26*dpx
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        Text {
            id: zantingText
            text: qsTr("结束")
            font.pixelSize: 16*dpx;
            color: "#ffffff";
            font.family: "Microsoft YaHei"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
