//                                       帮助管理
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../Common"
import "../Exercise"

//Item {
//    id: helploader
//    width: 830 *dpx
//    height: 500 *dpy
//    Image {
//        id: loginImage
//        anchors.fill: parent
//        source: "qrc:/Image/Login_bg.jpg"
//    }
Rectangle {
    id: helploader
    anchors.fill: parent
    color: "transparent"
    Item {
        id: backgroundItem
        width: 830 *dpx
        height: 500 *dpy
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
            onClicked: helploader.visible = false
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
                text: qsTr("帮助")
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
        height: 390*dpy
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
            }
            SwitchButton{
                id: shiyong_text
                text: qsTr("使用说明")

            }

        }

    }

}


}
