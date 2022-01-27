//                                               底部播放条

import QtQuick 2.12
import QtQuick.Controls 2.15

Item {
    id: manoeuvre
    width: mainWindow.width
    height: 136 *dpy
    Image {
        anchors.fill: parent
        source: "qrc:/Image/Start_bg.png"
    }

    Text {
        id: yanxiTime
        x: 80*dpx
        y: (136 *dpy + 50 *dpy - yanxiTime.contentHeight)/2
        text: qsTr("演习时间：")
        font.pixelSize: 20*dpx;
        color: "#ffffff";
        font.family: "MicrosoftYaHei";
    }

    Button {
        id: jieshuyanxi
        x: 80*dpx + yanxiTime.contentWidth
        y: 75 *dpy
        width: jieshuyanxiText.contentWidth + 60*dpx
        height: 36*dpy
        text: qsTr("结束演习")
        contentItem: Text {
            id: jieshuyanxiText
            text: jieshuyanxi.text
            font.pixelSize: 16*dpx;
            color: "#ffffff";
            font.family: "MicrosoftYaHei";
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        background: Rectangle {
            radius: 18*dpy
            color: "#dbbb5a"
        }
    }

    Button {
        x: (parent.width - 26*dpy)/2
        y: 26 *dpy
        background: Rectangle {
            color: "transparent"
            Image {
                id: zantingImage
                width: 26 *dpy
                height: 26 *dpy
                source: "qrc:/Image/icon/zanting.svg"
            }
            Text {
                id: zantingText
                y: 36 *dpy
                text: qsTr("暂停")
                font.pixelSize: 14*dpx;
                color: "#ffffff";
                font.family: "MicrosoftYaHei";
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
    Rectangle {
        id: switchSet
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -34*dpy
        anchors.right: parent.right
        anchors.rightMargin: -20 *dpx
        width: 140*dpx
        height: 68 *dpy
        color: Qt.rgba(36/255, 41/255, 57/255, 0.6);
        radius: 20*dpy


            Rectangle {
                x: 10*dpx
                y: 7*dpy
                color: "transparent"
                width: 20*dpx
                height: 20*dpx
                Image {
                    anchors.fill:parent
                    source: "qrc:/Image/icon/qiehuan.svg"
                }
            }
            Rectangle {
                 y: 7*dpy
                x: 35*dpx
                color: "transparent"
                Text {
                    text: qsTr("切换设置")
                    font.pixelSize: 16*dpx;
                    color: "#ffffff";
                    font.family: "Microsoft YaHei"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                manoeuvre.visible = false
                footerBar.visible = true
            }
        }
    }


}
