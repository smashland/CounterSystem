import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle{
    id: viewButton
    width: viewText.contentWidth + 50 *dpx
    height: 32 *dpy
    property color viewColor_xinjian : "#369488"
    property color viewColor_daoru : "#4671a6"
    property color viewColor_shuaxin : "#27397c"
    property color viewColor_shanchu : "#ba5c5c"
    property color viewColor_xuanzhongshanchu : "#a2a2a2"
    property alias name: viewText.text
    property alias viewImage : viewIcon.text
    Row {
        anchors.centerIn: parent
        spacing: 8*dpx

        Text {
            id: viewIcon
            color: "#ffffff"
            font.family: "iconfont"
            font.pixelSize: 22*dpx
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: viewText
            width: viewText.contentWidth
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            //                text: ""
            font.pixelSize: 14*dpx
            color: "#ffffff"
            font.family: "Microsoft YaHei"
        }
    }
}


