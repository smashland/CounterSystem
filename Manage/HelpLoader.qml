//                                       帮助管理
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import MyItem 1.0
import "../Common"
import "../Exercise"

Rectangle {
    id: helploader
    anchors.fill: parent
    color: "transparent"

    Item {
        id: backgroundItem
        width: 830 *dpx
        height: 500 *dpy
        anchors.centerIn: parent
        MouseArea {
            anchors.fill: parent
            onWheel: {
                // 屏蔽滚轮事件，防止滚动方案列表时缩放地球
            }
        }
        Image {
            id: loginImage
            anchors.fill: parent
            source: "qrc:/Image/Popup_bg_20.png"
        }
        CloseButton {
            anchors.right: backgroundItem.right
            anchors.rightMargin: 60 *dpx
            anchors.top: backgroundItem.top
            anchors.topMargin: 60 *dpy
            onClicked: footerBar.btnHelp.checked = false
        }
        PopupTitle {
            name: ("帮助")
            icon: "\ue619"
            x: 54*dpx
            y: 40*dpy
        }

        Rectangle {
            x: 80*dpx
            y: 90*dpy
            width: 190*dpx
            height: 370*dpy
            color: "#0a3365"
            ButtonGroup{
                buttons: columnEditBtns.children
            }
            Column {
                id:columnEditBtns
                //        anchors.verticalCenter: parent.verticalCenter
                spacing:  0*dpx
                SwitchButton{
                    id: shouquan_text
                    text: qsTr("授权配置")
                    onClicked: {
                        info.visible=true;
                        helpAdd.visible = false
                    }
                }
                SwitchButton{
                    id: shiyong_text
                    text: qsTr("使用说明")
                    onClicked: {
                        info.visible=false;
                        helpAdd.visible = true
                    }

                }

            }

            Row{
                id: info
                x:218*dpx
                y:35*dpy
                visible: false

                Text {
                    id: jiqima
                    width: jiqima.contentWidth
                    height: 34 *dpy
                    color: "#ffffff"
                    text: "机器码："
                    font.pixelSize: 17*dpx;
                    font.family: "Microsoft YaHei";
                    verticalAlignment: Text.AlignVCenter
                }

                Rectangle {
                    width: 400*dpx
                    height: 34 *dpy
                    color: "#1d4f88"
                    border.color: "#3b6daa"
                    Text {
                        x: 10 *dpx
                        width: 380*dpx
                        height: 34 *dpy
                        text: $licCheck.getMD5MachineInfo()
                        font.pixelSize: 17*dpx
                        color: "#ffffff"
                        clip: true
                        font.family: "Microsoft YaHei"
                        verticalAlignment: Text.AlignVCenter

                    }
                }
            }

            HelpAdd {
                id: helpAdd
                x:218*dpx
//                y:35*dpy
                visible: false
            }

        }
    }
}
