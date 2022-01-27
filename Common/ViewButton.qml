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
        property var viewImage : ""
        Row {
            anchors.centerIn: parent
            spacing: 8*dpx
            Image {
                y:4*dpy
                width: 16*dpx
                height: 16 *dpx
                source: viewImage
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


