//                                                          顶部播放条
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"
Item {
    id: progressbar
    width: mainWindow.width
    height: 100 *dpy
    Image {
        anchors.fill: parent
        source: "qrc:/Image/Case_bg.png"
    }
    Item {
        anchors.right: parent.right
        anchors.rightMargin: 80 *dpx
        y: progressbar.height
        width: 168 *dpx
        height: 34 *dpy
        Image {
            anchors.fill: parent
            source: "qrc:/Image/Infor_onoff.png"
        }
        Text {
            anchors.fill: parent
            text: qsTr("信息收起")
            font.pixelSize: 16*dpx
            color: "#ffffff"
            font.family: "MicrosoftYaHei Bold"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
    Text {
        x: 80 *dpx
        height: 100 *dpy
        text: qsTr("方案名称：")
        font.pixelSize: 24*dpx;
        color: "#ffffff";
        font.bold: true
        font.family: "MicrosoftYaHei Bold"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
    Column {
        x: (parent.width - playBar.width)/2
        y: (parent.height - 32*dpy - yanxiText.height)/2
        Rectangle {
            id: playBar
            width: 554 *dpx
            height: 32 *dpx
            color: "transparent"
            y: 16 *dpy
            Text {
               id: shangyige
               color: "#ffffff"
               text: "\ue712"
               font.family: "iconfont"
               font.pixelSize: 32*dpx
               verticalAlignment: Text.AlignVCenter
            }
            Text {
               id: bofang
               x: 36 *dpx
               z: 2
               color: "green"
               text: "\ue609"
               font.family: "iconfont"
               font.pixelSize: 32*dpx
               verticalAlignment: Text.AlignVCenter
            }
            ProgressBar {
                id: jindutiao
                width: 400 *dpx
                height: 8 *dpy
                x: 52 *dpx
                y:15 *dpy
                background: Rectangle {
                    implicitWidth: jindutiao.width
                    implicitHeight: jindutiao.height
                    color: "#ffffff"

                }
                contentItem: Item {
                    Rectangle {
                        width: jindutiao.visualPosition * jindutiao.width
                        height: jindutiao.height
                        color: "#66e690"
                    }
                }
            }
            Text {
               id: xiayieg
               color: "#ffffff"
               text: "\ue711"
               x: 462 *dpx
               font.family: "iconfont"
               font.pixelSize: 32*dpx
               verticalAlignment: Text.AlignVCenter
            }
            Text {
               id: shanchu
               color: "#ffffff"
               text: "\ueaf2"
               x: 508 *dpx
               font.family: "iconfont"
               font.pixelSize: 32*dpx
               verticalAlignment: Text.AlignVCenter
            }


        }
        Text {
            id: yanxiText
            x: (jindutiao.width - yanxiText.contentWidth)/2
            text: qsTr("演习时长：")
            font.pixelSize: 20*dpx;
            color: "#ffffff";
            font.family: "MicrosoftYaHei Bold"
        }

    }


}
