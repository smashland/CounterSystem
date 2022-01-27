import QtQuick 2.12
import QtGraphicalEffects 1.15
import QtQuick.Controls 2.15
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
                Rectangle {
                    width: 355 *dpx
                    height: 50 *dpy
                    color: Qt.rgba(0/255, 31/255, 94/255, 0.6);
                    border.color: "#00baff"
                    Image {
                        id: lrImage
                            y: 13*dpy
                            x: 20*dpx
                        width:  24*dpx
                        height:  24*dpx
                        source: "qrc:/Image/code_icon.png"
                    }
                    TextField {
                        id: lrText
                        anchors.fill: parent
                        color: Qt.rgba(255/255, 255/255, 255/255, 0.8);
                        font.pixelSize: 16*dpx
                        placeholderText: "请输入授权码"
                        font.family: "Microsoft YaHei"
                        clip: true
                        verticalAlignment: Text.AlignVCenter
                        leftPadding:  52*dpx
                        activeFocusOnPress:true
                        //        font.capitalization:Font.AllUppercase
                        background: Rectangle {
                            color: "transparent"
                        }
                    }
                }
                Rectangle {
                    width: 355 *dpx
                    height: 50 *dpy
                    color: Qt.rgba(0/255, 31/255, 94/255, 0.6);
                    border.color: "#00baff"
                    Image {
                        y: 13*dpy
                        x: 20*dpx
                        width:  24*dpx
                        height:  24*dpx
                        source: "qrc:/Image/port_icon.png"
                    }
                    TextField {
                        anchors.fill: parent
                        color: Qt.rgba(255/255, 255/255, 255/255, 0.8);
                        font.pixelSize: 16*dpx
                        font.family: "Microsoft YaHei"
                        clip: true
                        verticalAlignment: Text.AlignVCenter
                        leftPadding:  52*dpx
                        placeholderText: "请选择相应的串口"
                        activeFocusOnPress:true
                        //        font.capitalization:Font.AllUppercase
                        background: Rectangle {
                            color: "transparent"
                        }
                    }
                }
            }

            Rectangle {
                id: loginButton
                x: 110 *dpx
                y: 82 *dpy + shouquan.contentHeight + 80 *dpy + columnTextField.height
                width:  355*dpx
                height:  44*dpy
                LinearGradient {
                    anchors.fill: loginButton
                    source: loginButton
                    start: Qt.point(0, 0)
                    end: Qt.point(0, loginButton.height)
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "#d4f4ff"}
                        GradientStop { position: 1.0; color: "#2b9afa"}
                    }
                }
                Text {
                    anchors.fill:parent
                    font.pixelSize: 20*dpx;
                    color: "#003868";
                    font.family: "Microsoft YaHei"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "登录"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        popupRectWin.visible = true
                    }
                }
            }
        }

    }
