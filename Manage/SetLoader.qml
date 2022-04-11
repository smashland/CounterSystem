//                                       设置管理
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../Common"
import "../Exercise"

Rectangle {
    id: setloader
    anchors.fill: parent
    color: "transparent"
    Item {
        id: backgroundItem
        width: 1102 *dpx
        height: 680 *dpy
        anchors.centerIn: parent
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
            onClicked: setloader.visible = false
        }

        PopupTitle {
            name: ("击杀情况")
            icon: "\ue795"
        }
        TransverseLine {
            x: 80 *dpx
            y: 95*dpy
        }

    Rectangle {
        x: 80*dpx
        y: 140*dpy
        width: 190*dpx
        height: 492*dpy
        color: "#0a3365"
        ButtonGroup{
            buttons: columnEditBtns.children
        }
        Column {
            id:columnEditBtns
    //        anchors.verticalCenter: parent.verticalCenter
            spacing:  0*dpx
            SwitchButton{
                id: name_text
                text: qsTr("用户设置")
            }
            SwitchButton{
                id: map_text
                text: qsTr("地图设置")

            }
            SwitchButton {
                id: defen_text
                text: qsTr("得分设置")

            }

        }

    }


}

}
