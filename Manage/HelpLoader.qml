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
        }
        TransverseLine {
            x: 80 *dpx
            y: 95*dpy
        }

    Rectangle {
        x: 80*dpx
        y: 110*dpy
        width: 190*dpx
        height: 350*dpy
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
                }
            }
            SwitchButton{
                id: shiyong_text
                text: qsTr("使用说明")
                onClicked: {
                    info.visible=false;
                }

            }

        }

        Text {
            id: info
            x:218*dpx
            y:35*dpy
            visible: false
            font.pixelSize: 24*dpx
            color: "#ffffff"
            text: qsTr("机器码:"+objCheckLic.getMD5MachineInfo()) //
        }
    }
}
    LicItem
    {
        id:objCheckLic;
    }

}
