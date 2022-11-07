//                                                          底部切换条
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"
import "Plugins"

Item {
    id: footerbar
    property alias btnSet: set_text
    property alias btnScenario: scenario_text
    property alias btnPlayback: playback_text
    property alias btnHelp:help_text
    width: mainWindow.width
    height: 100 *dpy
    MouseArea {
        anchors.fill: parent
        onWheel: {
            // 屏蔽滚轮事件，防止滚动方案列表时缩放地球
        }
    }
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
            //            onCheckedChanged: setloader.visible = set_text.checked
        }
        FooterButton{
            id: scenario_text
            text: qsTr("方案管理")
            //            onCheckedChanged: scenarioLoader.visible = scenario_text.checked
        }
        FooterButton {
            id: playback_text
            text: qsTr("回放管理")
            //            onCheckedChanged: playbackLoader.visible = playback_text.checked
        }
        FooterButton {
            id: help_text
            text: qsTr("帮助")
            //            onCheckedChanged: helploader.visible = help_text.checked
        }

    }
    ToggleSettings {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -34*dpy
        anchors.right: parent.right
        anchors.rightMargin: -20 *dpx
        MouseArea {
            anchors.fill: parent
            onClicked: {
                footerBar.visible = false
                manoeuvre.visible = true
            }
        }
    }

}
