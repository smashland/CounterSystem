//                                         选择方案修改方式
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"


Rectangle
{
    id:scenarioPopup
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
    PopupTitle {
        name: ("删除")
    }
//    TransverseLine {
//        x: 80 *dpx
//        y: 95*dpy
//    }

    Column {
        x: (458*dpx - control3.width)/2
        y: 106 *dpy
        spacing: 14 *dpx
        RadioButton {
            id:control3
            checked: true
            text: qsTr("跳转方案管理页面修改")
            indicator: Rectangle {
                implicitWidth: 18
                implicitHeight: 18
                y: parent.height / 2 - height / 2
                radius: 9
                border.color: control3.down ? "#ffffff" : "#26abef"

                Rectangle {
                    width: 12
                    height: 12
                    radius: 6
                    anchors.centerIn: parent
                    color: control3.down ? "#ffffff" : "#1d4f88"
                    visible: control3.checked
                }
            }

            contentItem: Text {
                text: control3.text
                opacity: enabled ? 1.0 : 0.3
                color: "#ffffff"
                font.pixelSize: 17*dpx;
                verticalAlignment: Text.AlignVCenter
                leftPadding: 20*dpx
            }
        }
        RadioButton {
            id: control4
            text: qsTr("跳转修改界面修改")
            indicator: Rectangle {
                implicitWidth: 18
                implicitHeight: 18
                y: parent.height / 2 - height / 2
                radius: 9
                border.color: control4.down ? "#ffffff" : "#26abef"

                Rectangle {
                    width: 12
                    height: 12
                    radius: 6
                    anchors.centerIn: parent
                    color: control4.down ? "#ffffff" : "#1d4f88"
                    visible: control4.checked
                }
            }

            contentItem: Text {
                text: control4.text
                opacity: enabled ? 1.0 : 0.3
                color: "#ffffff"
                font.pixelSize: 17*dpx;
                verticalAlignment: Text.AlignVCenter
                leftPadding: 20*dpx
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

