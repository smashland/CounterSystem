//                                         删除
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"


    Rectangle
    {
        id:scenarioRemove
        width: 458 *dpx
        height: 308 *dpy
        x:(parent.width-width)/2
        y:(parent.height-height)/2
        focus: true
        visible: true
        color: "transparent"
        Image {
            id: name
            anchors.fill: parent
            source: "qrc:/Image/Popup_bg_24.png"
        }

        Row {
            x: (438*dpx-shanchuText.contentWidth)/2
            y: 106 *dpy
            spacing: 14 *dpx
            Image {
                width: 30
                height: 30
                source: "qrc:/Image/icon/tishi.svg"
            }
            Column {
                spacing: 5
                Text {
                    id: shanchuText
                    text: qsTr("此操作将永久删除该方案，")
                    color: "#ffffff"
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                Text {
                    text: qsTr("确定删除吗？")
                    color: "#ffffff"
                    font.pixelSize: 14
                    font.family: "Microsoft YaHei"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
        Row {
            spacing: 15 *dpx
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 60 *dpy
            x: 133*dpx
            PopupButton {
                background: Rectangle {
                    color: "#265aef"
                }

                nameButton: "确定"

            }
            PopupButton {
                background: Rectangle {
                    color: "#1d4f88"
                }
                nameButton: "取消"
            }
        }


    }

