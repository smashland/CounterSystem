//                                                          底部切换条
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"

Item {
    id: footerbar
    property alias btnSet: set_text
    property alias btnScenario: scenario_text
    property alias btnPlayback: playback_text
    property alias btnHelp:help_text
    width: mainWindow.width
    height: 100 *dpy
    Image {
        anchors.fill: parent
        source: "qrc:/Image/Set_up_bg.png"
    }
    ButtonGroup{
        buttons: rowEditBtns.children
    }
    Row {
        id:rowEditBtns
        x: 150*dpx
        y: 0
//        anchors.verticalCenter: parent.verticalCenter
        spacing:  0*dpx
        FooterButton{
            id: set_text
            text: qsTr("设置管理")
            onCheckedChanged: setloader.visible = set_text.checked
        }
        FooterButton{
            id: scenario_text
            text: qsTr("方案管理")
            onCheckedChanged: scenarioLoader.visible = scenario_text.checked
        }
        FooterButton {
            id: playback_text
            text: qsTr("回放管理")
            onCheckedChanged: playbackLoader.visible = playback_text.checked
        }
        FooterButton {
            id: help_text
            text: qsTr("帮助")
            onCheckedChanged: helploader.visible = help_text.checked
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

                Text {
                    anchors.fill: parent
                    text: qsTr("\ue628")
                    color: "#e7f6ff"
                    font.family: "iconfont"
                    font.pixelSize: 22*dpx
                    verticalAlignment: Text.AlignVCenter
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
                footerBar.visible = false
                manoeuvre.visible = true
            }
        }
    }





}
