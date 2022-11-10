import QtQuick 2.12
import QtGraphicalEffects 1.15
import QtQuick.Controls 2.15
import MyItem 1.0
import "Plugins"
//Item {
//    id: login
Column {
    id: loginRect
    //        x: (mainWindow.width-loginRect.width)/2
    //        y: (mainWindow.height-loginRect.height)/2
    spacing: 50 *dpx

    Rectangle {
        id: loginText
        color: "transparent"
        width: 575 *dpx
        height: 64 *dpy
        Image {
            source: "qrc:/Image/Text_title.png"
        }
    }
    Rectangle {
        id: loginImg
        width: 575 *dpx
        height: 442 *dpy
        color: "transparent"
        Image {
            anchors.fill: parent
            source: "qrc:/Image/Login_box.png"
        }
        Text {
            id: shouquan
            x: (loginImg.width - shouquan.contentWidth)/2
            y: 82*dpy
            text: qsTr("授权登录")
            font.pixelSize: 24*dpx
            font.family: "Microsoft YaHei"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log($app.settings.conType)
                }
            }
        }
        LinearGradient {
            anchors.fill: shouquan
            source: shouquan
            start: Qt.point(0, 0)
            end: Qt.point(0, shouquan.contentHeight)
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#5eeaff" }
                GradientStop { position: 1.0; color: "#0faafb" }
            }
        }

        //========================================================授权码输入
        Column {
            id: columnTextField
            spacing: 20*dpy
            x: 110 *dpx
            y: 82 *dpy + shouquan.contentHeight + 40 *dpy
            LoginImage {
                LoginTextField {
                    id: lrText
                    placeholderText: qsTr("请输入授权码")
                    leftPadding:  52*dpx
                    readOnly:false
                    Component.onCompleted:
                    {
                        if($licCheck.isFileExist())
                        {
                            lrText.text = qsTr($licCheck.read());
                        }
                    }
                    selectByMouse: true
                    selectionColor: "#0187d6"
                }
            }
            LoginComboBox
            {
                id: control
                visible: false
            }

            LoginWifi {
                id: loginWifi
                visible: false
            }
            Component.onCompleted:
            {
                if(1 === $app.settings.conType)
                {
                    control.visible = true
                }
                else
                {
                    loginWifi.visible = true
                }
            }

        }
    }
}
