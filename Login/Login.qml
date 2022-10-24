import QtQuick 2.12
import QtGraphicalEffects 1.15
import QtQuick.Controls 2.15
import MyItem 1.0
//Item {
//    id: login
Column {
    id: loginRect
    //        x: (mainWindow.width-loginRect.width)/2
    //        y: (mainWindow.height-loginRect.height)/2
    spacing: 50 *dpx
    property alias name: control.currentText

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
            LoginImage {
                LoginTextField {
                    id: lrText
                    placeholderText: qsTr("请输入授权码")
                    leftPadding:  52*dpx
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
            LoginImage {

                LoginTextField {

                    LoginComboBox
                    {
                        id: control
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
                onClicked:
                {
                    $app.settings.setComName(control.currentText);
                    $app.startConnect();
                    $licCheck.saveLicense(lrText.text);
                    $licCheck.checkLicense()

                }
            }
        }
    }

    Timer
    {
        id:timer
        function setTimeout(cb, delayTime) {
            timer.interval = delayTime;
            timer.repeat = false;
            timer.triggered.connect(cb);
            timer.triggered.connect(function release () {
                timer.triggered.disconnect(cb); // This is important
                timer.triggered.disconnect(release); // This is important as well
            });
            timer.start();
        }

    }

}
