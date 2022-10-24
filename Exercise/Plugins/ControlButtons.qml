import QtQuick 2.15

Rectangle
{
    width:100
    height: 100
    radius: width/2
    x: (parent.width-width)/2
    property alias jianbianColor: color1.color
    property alias icon: tubiao.text
    property alias text: zantingText.text
    gradient: Gradient
    {
        GradientStop
        {
            position: 0.04;
            color: "transparent";
        }
        GradientStop
        {
            id:color1
            position: 1.00;
            // color: "#00baff";
        }
    }
    Column{
        spacing: 5
        anchors.centerIn: parent
        Text {
            id: tubiao
            width: zantingText.contentWidth
            // text: qsTr("\ue623")
            color: "#e7f6ff"
            font.family: "iconfont"
            font.pixelSize: 26*dpx
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        Text {
            id: zantingText
            // text: qsTr("开始")
            font.pixelSize: 16*dpx;
            color: "#ffffff";
            font.family: "Microsoft YaHei"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
