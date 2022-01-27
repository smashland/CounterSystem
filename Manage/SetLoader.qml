//                                       设置管理
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../Common"
import "../Exercise"

//Item {
//    id: setloader
//    width: 830 *dpx
//    height: 500 *dpy
//    Image {
//        id: loginImage
//        anchors.fill: parent
//        source: "qrc:/Image/Login_bg.jpg"
//    }
Rectangle {
    id: setloader
    anchors.fill: parent
    color: "transparent"
    Item {
        id: backgroundItem
        width: 1002 *dpx
        height: 680 *dpy
        anchors.centerIn: parent
        Image {
            id: loginImage
            anchors.fill: parent
            source: "qrc:/Image/Popup_bg_20.png"
        }
        CloseButton {
            anchors.right: backgroundItem.right
            anchors.rightMargin: 50 *dpx
            anchors.top: backgroundItem.top
            anchors.topMargin: 50 *dpy
            onClicked: setloader.visible = false
        }

    Row {
        x: 24 *dpx
        y: 24 *dpx
        spacing: 10*dpx
        Rectangle {
            color: "transparent"
            width: 16*dpx
            height: 16*dpx
            Image {
                anchors.fill:parent
                source: "file"
            }
        }
        Rectangle {

            color: "transparent"
            Text {
                text: qsTr("击杀情况")
                font.pixelSize: 24*dpx;
                color: "#ffffff";
                font.family: "MicrosoftYaHei-Bold"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    Rectangle {
        x: 30*dpx
        y: 110*dpy
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
