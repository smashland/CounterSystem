//                                         登录失败弹窗
import QtQuick 2.12
import QtQuick.Controls 2.15

Popup {
    id: popupRectDef
    width: 1175 *dpx
    height: 750 *dpy
    x:(mainWindow.width-popupRectDef.width)/2
    y:(mainWindow.height-popupRectDef.height)/2
    background: Rectangle {
        color: Qt.rgba(12/255, 22/255, 50/255, 0.5);
    }

    Rectangle
    {
        id:popupDef
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
            y: (popupDef.height - 36 *dpy)/2
            spacing: 10 *dpx
            Image {
                width: 36 *dpx
                height: 36 *dpx
                source: "qrc:/Image/icon/shibai.svg"
            }
            Text {
                id: wintext
                text: qsTr("连接失败，1s后弹窗消失，进入系统页面")
                height: 36 *dpx
                font.pixelSize: 18*dpx;
                color: "#e74b4b";
                font.family: "Microsoft YaHei";
                verticalAlignment: Text.AlignVCenter
            }
        }

    }


}

